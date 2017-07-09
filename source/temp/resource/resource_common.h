/**
 * @file resource_common.h
 * @brief 
 * @author tsukushibito
 * @version 0.0.1
 * @date 2017-07-09
 */
#pragma once
#ifndef GUARD_b9182cb820a84ff5967c57e597f641e1
#define GUARD_b9182cb820a84ff5967c57e597f641e1

#include "temp/graphics/graphics.h"

namespace temp {
namespace resource {

struct VertexData {
    graphics::VertexAttribute    attribute;
    graphics::VertexBufferFormat format;
    ByteData                     byte_data;
};
using VertexDataTable = HashMap<graphics::VertexAttribute, VertexData,
                                graphics::VertexAttributeHash>;

struct IndexData {
    graphics::IndexBufferFormat format;
    graphics::PrimitiveType     primitive_type;
    ByteData                    byte_data;
};
}
}
#endif // GUARD_b9182cb820a84ff5967c57e597f641e1
