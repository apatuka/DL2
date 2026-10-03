#include "game/army_pool.h"
#include <algorithm>
#include <array>
#include <memory>
#include <new>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>

namespace dl2::simulation {
namespace {
bool fail(save::Error& error,const char* message,save::ErrorCode code=save::ErrorCode::InvalidState) {
    error={code,0,std::string("Army pool: ")+message}; return false;
}
template<class Action> bool guarded(Action action,save::Error& error) {
    try { return action(); }
    catch (const std::bad_alloc&) { return fail(error,"allocation failed",save::ErrorCode::Limit); }
    catch (const std::length_error&) { return fail(error,"container limit exceeded",save::ErrorCode::Limit); }
    catch (const std::exception& e) { error={save::ErrorCode::InvalidState,0,e.what()}; return false; }
}
// Also validates the two deliberate intermediate states of lifecycle callers:
// ignore one newly inserted/not-yet-allocated or retired/not-yet-erased record.
// Ignoring it does NOT permit a pool cell to contain that ID.
bool check(const save::Document& d,const save::ArmyPoolState& pool,uint32_t ignoredRecord,save::Error& error) {
    if (pool.liveIds.size()!=size_t(kMaxArmies) || pool.freeSlots.size()>size_t(kMaxArmies))
        return fail(error,"metadata must describe exactly560 cells");
    if (d.armies.size()>size_t(kMaxArmies)) return fail(error,"more than560 live records",save::ErrorCode::Limit);
    std::unordered_map<uint16_t,const Army*> records;
    records.reserve(d.armies.size()); size_t ignored=0;
    for (const auto& a:d.armies) {
        if (!a.id) return fail(error,"a live record has zero ID");
        if (a.id==ignoredRecord) { ++ignored; continue; }
        if (!records.emplace(a.id,&a).second) return fail(error,"live records have duplicate IDs");
    }
    if (ignoredRecord && ignored!=1) return fail(error,"pending allocation/retirement requires exactly one matching live record");
    std::unordered_set<uint16_t> occupied;
    occupied.reserve(records.size());
    for (const auto id:pool.liveIds) if (id) {
        if (!records.contains(id)) return fail(error,"pool cell does not resolve its current live record");
        if (!occupied.insert(id).second) return fail(error,"one live ID occupies multiple physical cells");
    }
    if (occupied.size()!=records.size()) return fail(error,"live records and physical cells are not a bijection");
    std::array<bool,kMaxArmies> free{};
    for (const auto slot:pool.freeSlots) {
        if (!slot || slot>uint32_t(kMaxArmies)) return fail(error,"free-list slot is outside1..560");
        if (free[slot-1]) return fail(error,"free-list contains a duplicate cell");
        if (pool.liveIds[slot-1]) return fail(error,"free-list contains an occupied cell");
        free[slot-1]=true;
    }
    for (size_t index=0;index<pool.liveIds.size();++index)
        if ((pool.liveIds[index]==0)!=free[index]) return fail(error,"free-list does not partition all cleared cells");
    for (const auto& jobs:pool.jobSlots) for (const auto& members:jobs) for (const auto slot:members)
        if (slot>uint32_t(kMaxArmies)) return fail(error,"task-force binding is outside nullable pool slots0..560");
    return true;
}
uint32_t findSlot(const save::ArmyPoolState& pool,uint32_t id) {
    if (!id || id>UINT16_MAX) return 0;
    const auto it=std::find(pool.liveIds.begin(),pool.liveIds.end(),uint16_t(id));
    return it==pool.liveIds.end()?0:uint32_t(it-pool.liveIds.begin()+1);
}
void pruneJob(save::Document& d,int player,int jobIndex,TaskForcePruneReport& report) {
    auto& job=d.jobs[size_t(player)][size_t(jobIndex)];
    auto& slots=d.armyPool->jobSlots[size_t(player)][size_t(jobIndex)];
    for (size_t member=0;member<16;++member) {
        const uint32_t slot=slots[member];
        if (!slot) continue; // Native pointer test: even a nonzero ID survives.
        const uint16_t currentId=d.armyPool->liveIds[slot-1];
        // DeleteArmy memset0x5c leaves owner0 in a cleared nonnull pool cell.
        const auto* occupant=currentId?d.armyById(currentId):nullptr;
        const int8_t currentOwner=occupant?occupant->owner:int8_t(0);
        const uint16_t expectedId=job.armyIds[member];
        if (currentId==expectedId && currentOwner==job.owner) continue;
        report.cleared.push_back({player,jobIndex,int(member),slot,expectedId,currentId,job.owner,currentOwner,
                                 currentId!=expectedId?TaskForcePruneReason::IdMismatch:TaskForcePruneReason::OwnerMismatch});
        // orig:0040aef0/0040aef2. Clear the bound pointer and saved WORD ID;
        // Army.job, other references, pool allocation and lifetimes are intact.
        slots[member]=0; job.armies[member].raw=0; job.armyIds[member]=0;
    }
}
bool prune(const save::Document& source,int player,int jobIndex,save::Document& destination,
           TaskForcePruneReport& report,save::Error& error) {
    return guarded([&] {
        if (!save::validate(source,error)) return false;
        if (source.header.isMap) return fail(error,"task-force cleanup requires a game document");
        auto candidate=std::make_unique<save::Document>(source);
        if (!ensureArmyPool(*candidate,error)) return false;
        TaskForcePruneReport result;
        const int firstPlayer=player<0?0:player,lastPlayer=player<0?kMaxPlayers:player+1;
        for (int p=firstPlayer;p<lastPlayer;++p) {
            const int firstJob=jobIndex<0?0:jobIndex,lastJob=jobIndex<0?kJobsPerPlayer:jobIndex+1;
            for (int j=firstJob;j<lastJob;++j) pruneJob(*candidate,p,j,result);
        }
        if (!save::validate(*candidate,error)) return false;
        destination=std::move(*candidate); report=std::move(result); error={}; return true;
    },error);
}
} // namespace

bool ensureArmyPool(save::Document& d,save::Error& error) {
    return guarded([&] {
        if (d.armyPool) return validateArmyPool(d,error);
        if (d.header.isMap) return fail(error,"cannot project an army pool from an editor map");
        if (d.armies.size()>size_t(kMaxArmies)) return fail(error,"initial live count exceeds560",save::ErrorCode::Limit);
        save::ArmyPoolState next;
        next.liveIds.resize(kMaxArmies);
        std::unordered_map<uint16_t,uint32_t> bindings;
        bindings.reserve(d.armies.size());
        for (size_t index=0;index<d.armies.size();++index) {
            const uint16_t id=d.armies[index].id;
            if (!id || !bindings.emplace(id,uint32_t(index+1)).second)
                return fail(error,"initial live record has zero/duplicate ID");
            next.liveIds[index]=id;
        }
        //00445710 visits every physical slot in increasing order and pushes
        // type0 slots to the head, reversing their allocation order after LOAD.
        for (uint32_t slot=uint32_t(d.armies.size()+1);slot<=uint32_t(kMaxArmies);++slot)
            next.freeSlots.push_back(slot);
        for (size_t p=0;p<kMaxPlayers;++p) for (size_t j=0;j<kJobsPerPlayer;++j)
            for (size_t member=0;member<16;++member) {
                const uint16_t id=d.jobs[p][j].armyIds[member];
                if (!id) continue;
                const auto found=bindings.find(id);
                if (found==bindings.end()) return fail(error,"initial job ID cannot be resolved to a live pool cell");
                next.jobSlots[p][j][member]=found->second;
            }
        if (!check(d,next,0,error)) return false;
        d.armyPool=std::move(next); error={}; return true;
    },error);
}

bool allocateArmyPoolSlot(save::Document& d,uint32_t id,save::Error& error) {
    return guarded([&] {
        if (!d.armyPool) return fail(error,"initialize pool BEFORE inserting a live record");
        if (!id || id>UINT16_MAX) return fail(error,"allocation ID is outside1..65535");
        if (!check(d,*d.armyPool,id,error)) return false;
        if (d.armyPool->freeSlots.size()<2)
            return fail(error,"allocation must preserve one native free cell",save::ErrorCode::Limit);
        auto next=*d.armyPool;
        const uint32_t slot=next.freeSlots.back(); next.freeSlots.pop_back();
        next.liveIds[slot-1]=uint16_t(id);
        if (!check(d,next,0,error)) return false;
        d.armyPool=std::move(next); error={}; return true;
    },error);
}

bool retireArmyPoolSlot(save::Document& d,uint32_t id,save::Error& error) {
    return guarded([&] {
        if (!d.armyPool) return fail(error,"initialize pool BEFORE retiring a live record");
        if (!id || id>UINT16_MAX) return fail(error,"retirement ID is outside1..65535");
        if (!check(d,*d.armyPool,0,error)) return false;
        if (d.armyPool->freeSlots.empty())
            return fail(error,"retirement would dereference a null native free head in a completely full pool");
        const uint32_t slot=findSlot(*d.armyPool,id);
        if (!slot) return fail(error,"retired ID does not occupy a live pool cell");
        auto next=*d.armyPool;
        next.liveIds[slot-1]=0; next.freeSlots.push_back(slot);
        if (!check(d,next,id,error)) return false;
        d.armyPool=std::move(next); error={}; return true;
    },error);
}

bool validateArmyPool(const save::Document& d,save::Error& error) {
    return guarded([&] {
        if (d.armyPool) {
            if (d.header.isMap) return fail(error,"editor map has an owned army pool");
            if (!check(d,*d.armyPool,0,error)) return false;
        }
        error={}; return true;
    },error);
}

bool validateArchivalArmyBindings(const save::Document& d,save::Error& error) {
    return guarded([&] {
        if (!validateArmyPool(d,error)) return false;
        if (d.armyPool) for (size_t p=0;p<kMaxPlayers;++p) for (size_t j=0;j<kJobsPerPlayer;++j)
            for (size_t member=0;member<16;++member) {
                const uint32_t slot=d.armyPool->jobSlots[p][j][member];
                const uint16_t expected=d.jobs[p][j].armyIds[member];
                if (!slot) {
                    if (expected) return fail(error,"null task-force binding with a nonzero ID is not archival");
                } else {
                    const uint16_t current=d.armyPool->liveIds[slot-1];
                    if (!current || current!=expected)
                        return fail(error,"cleared/reused task-force binding must reach original cleanup before encoding");
                }
            }
        error={}; return true;
    },error);
}

uint32_t armyPoolSlot(const save::Document& d,uint32_t id) {
    return d.armyPool?findSlot(*d.armyPool,id):0;
}
const Army* taskForceTarget(const save::Document& d,int player,int jobIndex,int member) {
    if (!d.armyPool || player<0 || player>=kMaxPlayers || jobIndex<0 || jobIndex>=kJobsPerPlayer || member<0 || member>=16)
        return nullptr;
    const uint32_t slot=d.armyPool->jobSlots[size_t(player)][size_t(jobIndex)][size_t(member)];
    if (!slot || slot>d.armyPool->liveIds.size()) return nullptr;
    const uint16_t id=d.armyPool->liveIds[slot-1];
    return id?d.armyById(id):nullptr;
}

bool pruneTaskForceArmies(const save::Document& source,int player,int jobIndex,save::Document& destination,
                          TaskForcePruneReport& report,save::Error& error) {
    if (player<0 || player>=kMaxPlayers || jobIndex<0 || jobIndex>=kJobsPerPlayer)
        return fail(error,"cleanup requires player0..6 and job index0..49");
    return prune(source,player,jobIndex,destination,report,error);
}
bool prunePlayerTaskForceArmies(const save::Document& source,int player,save::Document& destination,
                                TaskForcePruneReport& report,save::Error& error) {
    if (player<0 || player>=kMaxPlayers) return fail(error,"cleanup player is outside0..6");
    return prune(source,player,-1,destination,report,error);
}
bool pruneAllTaskForceArmies(const save::Document& source,save::Document& destination,
                             TaskForcePruneReport& report,save::Error& error) {
    return prune(source,-1,-1,destination,report,error);
}
} // namespace dl2::simulation
