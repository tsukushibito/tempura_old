#pragma once

#ifdef TEMP_USE_BOOST
#include <boost/filesystem.hpp>
namespace temp {
namespace filesystem = ::boost::filesystem;
}
#else
#include <filesystem>
namespace temp {
namespace filesystem = ::std::filesystem;
}
#endif
