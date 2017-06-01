/**
 * @file tmsh.h
 * @brief 
 * @author tsukushibito
 * @version 0.0.1
 * @date 2017-06-01
 */
#pragma once
#ifndef GUARD_4090ac7e2f914c8b9240c11fef4d2d1e
#define GUARD_4090ac7e2f914c8b9240c11fef4d2d1e

#include "temp/type.h"

namespace temp {
namespace resource {
namespace file_parser {

struct TmshHeader {
    Char   signature[4];
    UInt32 version;
};

struct TmshVertexHeader {
    Char   signature[4];
    UInt32 format;
    UInt32 vertex_count;
};

struct TmshIndexHeader {
    Char   signature[4];
    UInt32 format;
    UInt32 index_count;
};

}
}
}

#endif // GUARD_4090ac7e2f914c8b9240c11fef4d2d1e
