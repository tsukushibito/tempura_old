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

#include "temp/container.h"
#include "temp/type.h"

#include "temp/graphics/graphics.h"

#include "temp/resource/mesh.h"

namespace temp {
namespace resource {
namespace tmsh {

const Int32 kVersion               = 1;
const Int32 kSignatureLength       = 4;
const Int32 kVertexAttributeLength = 16;

struct TmshHeader {
    Char   signature[kSignatureLength];
    UInt32 version;
    UInt32 vertex_chunk_count;
    UInt32 data_size;
};

struct TmshVertexHeader {
    Char                         signature[kSignatureLength];
    Char                         attribute[kVertexAttributeLength];
    graphics::VertexBufferFormat format;
    UInt32                       vertex_count;
    UInt32                       data_size;
};

struct TmshIndexHeader {
    Char                        signature[kSignatureLength];
    graphics::IndexBufferFormat format;
    graphics::PrimitiveType     primitive_type;
    UInt32                      index_count;
    UInt32                      data_size;
};

struct TmshVertexData {
	TmshVertexHeader header;
	Int8*            byte_data;
};
using VertexAttributeString = String;
using TmshVertexDataTable = HashMap<VertexAttributeString, TmshVertexData*>;

struct TmshIndexData {
	TmshIndexHeader header;
	Int8*           byte_data;
};

class Tmsh {
public:

    explicit Tmsh(const ByteData& data);
    explicit Tmsh(const Mesh::VertexBufferTable& vertex_buffer_table,
                  const Mesh::IndexBufferSPtr&   index_buffer);

    const Bool valid() const { return valid_; }

    const ByteData&        byteData() const { return byte_data_; }
    const TmshHeader&      header() const { return *header_; }
    const TmshVertexDataTable& vertexDataTable() const {
        return vertex_data_table_;
    }
    const TmshIndexData& indexData() const { return *index_data_; }

private:
    Bool				valid_ = false;
    ByteData        	byte_data_;
    TmshHeader*     	header_ = nullptr;
    TmshVertexDataTable vertex_data_table_;
    TmshIndexData*      index_data_ = nullptr;
};
}
}
}

#endif  // GUARD_4090ac7e2f914c8b9240c11fef4d2d1e
