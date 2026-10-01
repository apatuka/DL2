// Non-owning read-only projections of canonical static tables. Not save layouts.
#pragma once
#include <cstddef>

namespace dl2::data {
template<class Row, std::size_t Count, auto Member> struct MemberTableView {
    const Row (&rows)[Count];
    constexpr decltype(auto) operator[](std::size_t index) const { return (rows[index].*Member); }
    constexpr std::size_t size() const { return Count; }
};
} // namespace dl2::data
