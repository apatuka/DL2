// Filesystem access to the physical save codec; does not activate gameplay.
#pragma once

#include "game/save_document.h"

#include <filesystem>
#include <string_view>

namespace dl2::save {

// Inputs are read-only and capped at 16 MiB. Failure leaves destination intact;
// codec errors retain their original code/offset, and success clears error.
bool readDocument(const std::filesystem::path& path, Document& destination, Error& error);

// archiveBase omits .HDX/.HDD. Entry names are exact, case-sensitive byte strings,
// not filesystem paths. Both archive files have the same 16 MiB resource cap.
bool readScenario(const std::filesystem::path& archiveBase, std::string_view entry,
                  Document& destination, Error& error);

// Encode, stage a complete sibling file, and publish with an exclusive hard link.
// Never overwrites an existing destination, including the original input file.
// Requires filesystem hard-link support; fails safely without an overwrite fallback.
// Atomic publication does not guarantee durability across a sudden power loss.
bool writeDocumentCopy(const std::filesystem::path& destination,
                       const Document& document, Error& error);

} // namespace dl2::save
