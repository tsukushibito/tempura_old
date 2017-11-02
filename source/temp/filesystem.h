/**
 * @file filesystem.h
 * @brief
 * @author tsukushibito
 * @version 0.0.1
 * @date 2017-10-21
 */
#pragma once
#ifndef GUARD_18b0258162c542b6b80974a63fa51f09
#define GUARD_18b0258162c542b6b80974a63fa51f09

#ifdef TEMP_USE_BOOST
#include <boost/filesystem.hpp>
#else
#include <filesystem>
#endif

namespace temp {
namespace filesystem {
#ifdef TEMP_USE_BOOST
using Path = boost::filesystem::path;
using namespace boost::filesystem;
#else
using Path = std::filesystem::path;
using namespace std::filesystem;
#endif
}
}

#endif  // GUARD_18b0258162c542b6b80974a63fa51f09
