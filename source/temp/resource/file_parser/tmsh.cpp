#include <cstring>

#include "temp/resource/file_parser/tmsh.h"
#include "temp/system/logger.h"

namespace temp {
namespace resource {
namespace tmsh {

const Char* kTmshSignature       = "TMSH";
const Char* kTmshVertexSignature = "TVRT";
const Char* kTmshIndexSignature  = "TIDX";

Tmsh::Tmsh(const ByteData& data) : byte_data_(data) {
    if (byte_data_.size() < sizeof(TmshHeader)) {
        valid_ = false;
        return;
    }

    Size index = 0;

    // ファイルヘッダ読み込み
    TmshHeader* header = reinterpret_cast<TmshHeader*>(&byte_data_[index]);

    // シグネチャチェック
    String sig(header->signature, 4);
    if (sig != kTmshSignature) {
        system::Logger::error("Not TMSH data!");
    }

    header_ = header;

    // 頂点データ読み込み
    index += sizeof(TmshHeader);
    for (UInt32 i = 0; i < header_->vertex_chunk_count; ++i) {
        // ヘッダ読み込み
        auto vertex_data = reinterpret_cast<VertexData*>(&byte_data_[index]);

        // シグネチャチェック
        sig = String(vertex_data->header.signature, 4);
        if (sig != kTmshVertexSignature) {
            system::Logger::error("Not TMSH vertex data!");
            return;
        }

        // ヘッダ読み込み
        String attr = vertex_data->header.attribute;
        if (vertex_data_table_.find(attr) != vertex_data_table_.end()) {
            system::Logger::error("{0} is duplicate attribute.", attr.c_str());
            return;
        }
        vertex_data_table_[attr] = vertex_data;
        vertex_data_table_[attr]->byte_data
            = &byte_data_[index + sizeof(TmshVertexHeader)];

        // データサイズ分、インデックスをすすめる
        index += vertex_data->header.data_size;
    }

    // インデックスデータ読み込み
    {
        auto index_data = reinterpret_cast<IndexData*>(&byte_data_[index]);

        // シグネチャチェック
        sig = String(index_data->header.signature, 4);
        if (sig != kTmshIndexSignature) {
            system::Logger::error("Not TMSH index data!");
            return;
        }

        // ヘッダ読み込み
        index_data_            = index_data;
        index_data_->byte_data = &byte_data_[index + sizeof(TmshIndexHeader)];

        // データサイズ分、インデックスをすすめる
        index += index_data->header.data_size;
    }

    valid_ = true;
}


Tmsh::Tmsh(const Mesh::VertexBufferTable& vertex_buffer_table,
           const Mesh::IndexBufferSPtr&   index_buffer) {

    // バッファデータからヘッダを含めたサイズを求める
    Size header_size = sizeof(TmshHeader);

    Size vertex_data_size = 0;
    for (auto&& key_value : vertex_buffer_table) {
        auto&& vb = key_value.second;
        vertex_data_size += sizeof(TmshVertexHeader);
        vertex_data_size += vb->data().size();
    }

    Size index_data_size
        = sizeof(TmshIndexHeader) + index_buffer->data().size();

    auto&& data_size = header_size + vertex_data_size + index_data_size;

    // 必要なサイズのバッファを確保
    byte_data_.resize(data_size);


    // バッファに必要なデータを書き込む
    Size index = 0; // 書き込み先バイトインデックス

    // ファイルヘッダ
    auto header = reinterpret_cast<TmshHeader*>(&byte_data_[index]);
    memcpy(header->signature, kTmshSignature, kSignatureLength);
    header->version            = kVersion;
    header->vertex_chunk_count = static_cast<UInt32>(vertex_buffer_table.size());
    header->data_size          = static_cast<UInt32>(data_size);

    index += sizeof(TmshHeader);


    // 頂点データ書き込み
    for (auto&& key_value : vertex_buffer_table) {
        auto&& vb      = key_value.second;
        auto&& vb_desc = vb->desc();
        // ヘッダ
        auto   vertex_header
            = reinterpret_cast<TmshVertexHeader*>(&byte_data_[index]);
        memcpy(vertex_header->signature, kTmshVertexSignature,
               kSignatureLength);
        auto attrStr = graphics::vertexAttributeString(vb_desc.attribute);
        memcpy(vertex_header->attribute, attrStr.c_str(), attrStr.size());
        vertex_header->format = vb_desc.format;
        vertex_header->vertex_count
            = static_cast<UInt32>(vb_desc.size / graphics::vertexBufferFormatSize(vb_desc.format));
        vertex_header->data_size = static_cast<UInt32>(vb_desc.size);

        index += sizeof(TmshVertexHeader);

        // 頂点データ
        memcpy(&byte_data_[index], &vb->data()[0], vb_desc.size);

        index += vb_desc.size;
    }


    // インデックスデータ書き込み
    auto&& ib_desc      = index_buffer->desc();
    // ヘッダ
    auto&& index_header = reinterpret_cast<TmshIndexHeader*>(&byte_data_[index]);
    memcpy(index_header->signature, kTmshIndexSignature, kSignatureLength);
    index_header->format         = ib_desc.format;
    index_header->primitive_type = ib_desc.primitive_type;
    index_header->index_count
        = static_cast<UInt32>(ib_desc.size / graphics::indexBufferFormatSize(ib_desc.format));
    index_header->data_size = static_cast<UInt32>(ib_desc.size);

    index += sizeof(TmshIndexHeader);
    
    // インデックスデータ
    memcpy(&byte_data_[index], &index_buffer->data()[0], ib_desc.size);
}
}
}
}
