#pragma once
#include "temp/core/define.h"

#ifdef TEMP_USE_BOOST
#include <boost/filesystem.hpp>
namespace temp {
namespace filesystem = ::boost::filesystem;
}
#else
#include <filesystem>
namespace temp {
#if defined(TEMP_PLATFORM_WINDOWS)
namespace filesystem = ::std::experimental::filesystem;
#else
namespace filesystem = ::std::filesystem;
#endif
}
#endif
