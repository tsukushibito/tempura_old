/**
 * @file container.h
 * @brief
 * @author tsukushibito
 * @version 0.0.1
 * @date 2016-02-23
 */
#pragma once
#ifndef GUARD_bb39a89bd1a049529b850a7996876f13
#define GUARD_bb39a89bd1a049529b850a7996876f13

#include <string>
#include <vector>
#include <array>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <deque>
#include <sstream>

namespace temp {

#ifdef TEMP_USE_STL_ALLOCATOR
// std::string
using String =
    std::basic_string< char, std::char_traits< char >, allocator::AllocatorForSTL< char > >;
using StringStream =
    std::basic_stringstream< String::value_type, String::traits_type, String::allocator_type >;

// std::vector<T>
template < typename T >
using Vector = std::vector< T, allocator::AllocatorForSTL< T > >;

// std::deque<T>
template < typename T >
using Deque = std::deque< T, allocator::AllocatorForSTL< T > >;

// std::map<Key, Type>
template < typename Key, typename Type, typename Compare = std::less< Key > >
using Map =
    std::map< Key, Type, Compare, allocator::AllocatorForSTL< std::pair< const Key, Type > > >;

// std::unordered_map<Key, Type>
template < typename Key, typename Type, typename Hash = std::hash< Key >,
           typename Pred = std::equal_to< Key > >
using HashMap = std::unordered_map< Key, Type, Hash, Pred,
                                    allocator::AllocatorForSTL< std::pair< const Key, Type > > >;

#else
// std::string
using String = std::string;
using StringStream = std::stringstream;

// std::vector<T>
template < typename T >
using Vector = std::vector< T >;

// std::deque<T>
template < typename T >
using Deque = std::deque< T >;

// std::map<Key, Type>
template < typename Key, typename Type, typename Compare = std::less< Key > >
using Map = std::map< Key, Type, Compare >;

// std::unordered_map<Key, Type>
template < typename Key, typename Type, typename Hash = std::hash< Key >,
           typename Pred = std::equal_to< Key > >
using HashMap = std::unordered_map< Key, Type, Hash, Pred >;

#endif
}

#endif // GUARD_bb39a89bd1a049529b850a7996876f13
