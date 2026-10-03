// Shared owned leaves; no globals, UI, RNG or changes to the document.
#pragma once
#include "game/save_document.h"
#include <span>
#include <vector>

namespace dl2::simulation::research_detail {
//00450150/00450000/0044fe1c: explicit live goal mask, not inferred from SAV.
bool campaignAllowed(const save::Document&,uint32_t flags,int race,int technology,
                     bool& result,save::Error&);
//00483a30. Queue entries are compared as values, not used as indices. Literal
// zero prerequisites, duplicate matches and available-mask early return matter.
bool canQueue(const save::Document&,int player,std::span<const uint32_t> queue,
              int technology,uint32_t campaignFlags,bool& result,save::Error&);
//00483b84 removes FIRST matching value while traversing original node identity.
// Appends removal values to removed. Both mutable outputs are atomic on failure.
bool pruneQueue(const save::Document&,int player,uint32_t campaignFlags,
                std::vector<uint32_t>& queue,std::vector<uint32_t>& removed,save::Error&);
} // namespace dl2::simulation::research_detail
