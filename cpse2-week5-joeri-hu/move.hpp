#ifndef MOVE_HPP
#define MOVE_HPP

#include <map>
#include <utility>
#include <iterator>
#include "mark.hpp"

struct move : public std::pair<mark::pos, mark::type> {
    auto get_pos() const -> first_type {
        return first;
    }
    auto get_type() const -> second_type {
        return second;
    }
};

class move_table : private std::map<mark::pos, mark::type> {
private:
    struct move_iter : public const_iterator {
        auto get_pos() const -> value_type::first_type {
            return (*this)->first;
        }
        auto get_type() const -> value_type::second_type {
            return (*this)->second;
        }
    };
public:
    move_table() = default;
    auto insert(move const& entry) -> move_iter {
        return move_iter{map::insert(entry).first};
    }
    auto find(key_type const& key) const -> move_iter {
        return move_iter{map::find(key)};
    }
    using const_iterator = move_iter;
    using value_type = move;
    using map::key_type;
    using map::size_type;
    using map::size;
    using map::count;
    using map::at;
    using map::begin;
    using map::cbegin;
    using map::end;
    using map::cend;
    using map::erase;
    using map::clear;
};

#endif
