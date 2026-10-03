#include "game/entity_orders.h"
#include "game/data_tables.h"
#include <algorithm>
#include <bit>
#include <cstring>
#include <memory>
#include <new>
#include <stdexcept>
#include <string>

namespace dl2::simulation {
namespace {
bool fail(save::Error& error,const char* message) {
    error={save::ErrorCode::InvalidState,0,std::string("Entity order: ")+message}; return false;
}
bool authority(const save::Document& d,int actor,save::Error& error) {
    if (d.header.isMap) return fail(error,"requires a game document, not an editor map");
    if (actor<0 || actor>=kMaxPlayers || actor!=d.options.localPlayer)
        return fail(error,"actor must be the local player");
    const auto& p=d.players[size_t(actor)];
    if (p.type!=1 || p.index!=actor)
        return fail(error,"actor must be a local human with its matching physical player index");
    return true;
}
bool contextValid(const save::Document& d,const BuildingRemovalContext& context,save::Error& error) {
    if (context.pendingShrines.entries.size()>kPendingShrineCapacity) {
        error={save::ErrorCode::Limit,0,"Entity order pending shrine queue exceeds ten entries"}; return false;
    }
    for (const auto& entry:context.pendingShrines.entries)
        if (entry.playerSlot<0 || entry.playerSlot>=kMaxPlayers || !d.territoryByIndex(entry.territory))
            return fail(error,"pending shrine context contains an invalid player slot or territory");
    return true;
}
std::array<uint8_t,6> seaBytes(const Territory& t) {
    std::array<uint8_t,6> result{};
    std::copy_n(t.unk_8b0+(0x994-0x8b0),6,result.begin()); return result;
}
uint8_t& seaByte(Territory& t,size_t index) { return t.unk_8b0[0x994-0x8b0+index]; }

// orig: FUN_0044134c. ANY nonzero relation word, not a particular pact bit;
// unlike004412d4 it has no numPlayers or negative-index guards. A neutral
// territory passes owner=-1: this reads Player+0x276 (last minister's final
// four data bytes), still inside that Player, NOT a fabricated zero relation.
bool related(const save::Document& d,int player,int other) {
    if (!d.options.allowAlliances) return false;
    if (other==-1) {
        const auto* bytes=d.players[size_t(player)].ministers[5].unk_12+0x44;
        return bytes[0]!=0 || bytes[1]!=0 || bytes[2]!=0 || bytes[3]!=0;
    }
    return d.players[size_t(player)].relations[size_t(other)]!=0;
}
// orig: SeaManipulationFlagTerritories0046eebc, param4==0 only.
bool flagSeaTerritory(save::Document& d,uint32_t territory,int buildingType,int owner,save::Error& error) {
    auto& t=d.territories[size_t(territory-1)].data;
    //004faf8d is UnitDef+0x11 (movement DOMAIN), not stored/canonical class.
    const int blockedDomain=buildingType==43?2:3;
    bool unblocked=true;
    for (const uint32_t head:{t.armies.raw,t.foreignArmies.raw}) {
        uint32_t id=head; size_t visited=0;
        while (unblocked && id) {
            if (++visited>d.armies.size()) return fail(error,"marine flag army list is cyclic");
            const auto* a=d.armyById(id);
            if (!a) return fail(error,"marine flag army list contains an unresolved ID");
            if ((data::kUnitTypes[a->type].domain==blockedDomain || (a->type==27 && blockedDomain==2)) &&
                (a->owner==owner || related(d,owner,a->owner))) unblocked=false;
            id=a->next.raw;
        }
    }
    if (buildingType==43) {
        if (t.terrain==0 && unblocked) {
            seaByte(t,1)=uint8_t(std::min(int(std::bit_cast<int8_t>(seaByte(t,1)))+25,50));
            seaByte(t,4)|=uint8_t(1u<<owner);
        }
    } else if (buildingType==44) {
        if (unblocked) {
            seaByte(t,2)=uint8_t(std::min(int(std::bit_cast<int8_t>(seaByte(t,2)))+25,50));
            seaByte(t,4)|=uint8_t(1u<<owner);
        }
        if (t.owner==owner || related(d,owner,t.owner)) {
            seaByte(t,0)=uint8_t(std::min(int(std::bit_cast<int8_t>(seaByte(t,0)))+40,50));
            for (int player=0;player<kMaxPlayers;++player)
                if (!related(d,owner,player) && player!=owner) seaByte(t,3)|=uint8_t(1u<<player);
        }
        // The only RNG branch requires param4!=0, so no random draw here.
    }
    return true;
}
// orig: FUN_0046f0e0(0). Clears every real territory, then territory/site order.
bool rebuildSeaFlags(save::Document& d,std::vector<SeaManipulationChange>& changes,save::Error& error) {
    for (const auto& record:d.territories)
        if (record.data.owner < -1 || record.data.owner>=kMaxPlayers)
            return fail(error,"marine territory owner is outside -1..6");
    std::vector<std::array<uint8_t,6>> before; before.reserve(d.territories.size());
    for (auto& record:d.territories) {
        before.push_back(seaBytes(record.data));
        for (size_t i=0;i<6;++i) seaByte(record.data,i)=0;
    }
    for (size_t index=0;index<d.territories.size();++index) {
        const auto& t=d.territories[index].data;
        if (t.owner==-1) continue;
        for (const auto& site:t.sites) {
            const auto* b=d.buildingById(site.building.raw);
            if (!b || b->turnsLeft>0 || !(b->flags&4u) || data::kBuildingTypes[b->type].category!=16) continue;
            const int type=b->type,owner=t.owner;
            if (!flagSeaTerritory(d,uint32_t(index+1),type,owner,error)) return false;
            for (size_t word=0;word<7;++word) {
                const uint16_t mask=t.adjacency[word];
                for (unsigned bit=0;bit<16;++bit) if (mask&(uint16_t(1u)<<bit)) {
                    const auto adjacent=uint32_t(word*16+bit);
                    // Document owns no sentinel row or inactive table rows;
                    // reject an actual read there rather than invent its bytes.
                    if (!adjacent || adjacent>d.territories.size())
                        return fail(error,"marine adjacency references an unrepresented territory");
                    const auto& neighbor=d.territories[size_t(adjacent-1)].data;
                    if (neighbor.numTiles && !(neighbor.flags&0x100u) &&
                        !flagSeaTerritory(d,adjacent,type,owner,error)) return false;
                }
            }
        }
    }
    for (size_t index=0;index<d.territories.size();++index) {
        auto after=seaBytes(d.territories[index].data);
        if (before[index]!=after) changes.push_back({uint32_t(index+1),before[index],after});
    }
    return true;
}
// orig: FUN_0045aed4. Resolve occupied footprint/socket, rather than just the
// site's anchor ID. Each platform child lookup runs AFTER the prior demolition.
bool resolveSite(const save::Document& d,uint32_t territory,int site,uint32_t& id,save::Error& error) {
    if (site<0 || site>=36) return fail(error,"platform socket lookup is outside the 6x6 grid");
    const auto& t=d.territories[size_t(territory-1)].data;
    const uint16_t flags=t.sites[site].terrainFlags;
    const bool socket=(flags&0xf00u)==0x100u;
    int offset=0;
    switch (flags&0xf000u) {
    case 0x1000: offset=socket?12:0; break;
    case 0x2000: offset=socket?-2:-1; break;
    case 0x3000:
        offset=socket?22:0;
        if (!socket && !t.sites[site].building.raw) offset=6;
        break;
    case 0x4000: offset=socket?8:5; break;
    case 0x5000: offset=socket?10:0; break;
    default: id=0; return true;
    }
    const int anchor=site+offset;
    if (anchor<0 || anchor>=36) return fail(error,"platform footprint resolves outside the 6x6 grid");
    id=t.sites[anchor].building.raw;
    if (id && !d.buildingById(id)) return fail(error,"platform footprint references an unresolved building");
    return true;
}
} // namespace

bool orderDisbandUnit(const save::Document& source,const DisbandUnitOrderRequest& request,
                      save::Document& destination,ArmyLifecycleReport& report,save::Error& error) {
    try {
        if (!save::validate(source,error) || !authority(source,request.actor,error)) return false;
        const auto* a=source.armyById(request.armyId);
        if (!a) return fail(error,"selected unit does not exist");
        if (a->owner!=request.actor) return fail(error,"selected unit is not owned by the local actor");
        return removeArmy(source,{request.armyId,ArmyRemovalKind::DisbandUnit,false},destination,report,error);
    } catch (const std::bad_alloc&) { error={save::ErrorCode::Limit,0,"Entity order allocation failed"}; return false; }
      catch (const std::length_error&) { error={save::ErrorCode::Limit,0,"Entity order exceeds container limits"}; return false; }
}

bool orderDemolishBuilding(const save::Document& source,const DemolishBuildingOrderRequest& request,
                          const BuildingRemovalContext& context,save::Document& destination,
                          DemolishBuildingOrderReport& report,save::Error& error) {
    try {
        if (!save::validate(source,error) || !authority(source,request.actor,error) || !contextValid(source,context,error)) return false;
        const auto* selected=source.buildingById(request.buildingId);
        if (!selected) return fail(error,"selected building does not exist");
        const uint32_t territory=uint32_t(selected->territory);
        const auto& t=source.territories[size_t(territory-1)].data;
        if (t.visibility[size_t(request.actor)]!=4 || t.owner!=request.actor)
            return fail(error,"selected territory must be actor-owned and have native visibility level4");
        DemolishBuildingOrderReport result;
        result.requestedId=request.buildingId; result.primaryId=request.buildingId; result.territory=territory;
        result.contextAfter=context;
        int platformSite=-1;
        if (selected->type==38 || selected->type==39) {
            //0044d1a4 uses stored category20, NOT canonical type38.
            for (int site=0;site<36;++site) {
                const auto* b=source.buildingById(t.sites[site].building.raw);
                if (b && b->category==20) { platformSite=site; break; }
            }
            if (platformSite<0) return fail(error,"selected sea building has no category20 platform");
            if (selected->type==39) {
                result.primaryId=t.sites[platformSite].building.raw;
                result.platformRedirected=true;
            }
        }
        auto candidate=std::make_unique<save::Document>(source);
        auto demolish=[&](uint32_t id) {
            BuildingLifecycleReport removal;
            if (!removeBuilding(*candidate,{id,BuildingRemovalKind::DemolishBuilding,t.owner},
                                result.contextAfter,*candidate,removal,error)) return false;
            if (!removal.contextAfter) return fail(error,"demolition omitted its explicit continuation");
            result.contextAfter=*removal.contextAfter;
            result.removedIds.insert(result.removedIds.end(),removal.removedIds.begin(),removal.removedIds.end());
            result.removals.push_back(std::move(removal)); return true;
        };
        const auto* primary=candidate->buildingById(result.primaryId);
        if (primary->type==38) {
            for (int offset:{-22,-8,-12,2,-10}) {
                uint32_t id=0;
                if (!resolveSite(*candidate,territory,platformSite+offset,id,error)) return false;
                const auto* child=candidate->buildingById(id);
                if (child && child->type!=38 && !demolish(id)) return false;
            }
        }
        if (!demolish(result.primaryId) || !rebuildSeaFlags(*candidate,result.seaChanges,error)) return false;
        result.seaFlagsRebuilt=true;
        if (!save::validate(*candidate,error)) return false;
        destination=std::move(*candidate); report=std::move(result); error={}; return true;
    } catch (const std::bad_alloc&) { error={save::ErrorCode::Limit,0,"Entity order allocation failed"}; return false; }
      catch (const std::length_error&) { error={save::ErrorCode::Limit,0,"Entity order exceeds container limits"}; return false; }
}
} // namespace dl2::simulation
