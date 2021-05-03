#pragma once

#include <algorithm>
#include <vector>
#include <optional>
#include <string_view>

template<typename V> struct node_t
{
    static_assert(std::is_integral_v<V>, "trie value type must be integral");
    static constexpr V invalid_val = static_cast<V>(-1);
    using val_type = V;

    char key_;
    std::vector<node_t> children_;
    val_type val_ ;
    node_t(){}
    node_t(char k) : key_{k}, val_ {invalid_val}
    {}
};

template<typename V> std::optional<V> find(node_t<V> const* node, std::string_view key)
{
    for(auto c : key)
    {
        auto nn = std::find_if(node->children_.begin(), node->children_.end(), [c](auto const& nn){ return nn.key_ == c;});
        if( nn == node->children_.end())
            return std::nullopt;
        node = &*nn;
    }
    return node->val_;
}

template<typename V> void insert(node_t<V>* node, std::string_view key, V val)
{
    for(auto c : key)
    {
        auto nn = std::find_if(node->children_.begin(), node->children_.end(), [c](auto const& nn){ return nn.key_ == c;});
        node = (nn == node->children_.end()) ? &node->children_.emplace_back(c) : &*nn;
    }
    node->val_ = val;
}
