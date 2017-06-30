#include <cstring>

#include "temp/resource/file_parser/tmsh.h"
#include "temp/system/logger.h"

namespace temp {
namespace resource {
namespace tmsh {

const Char* kTmshSignature       = "TMSH";
const Char* kTmshVertexSignature = "TVRT";
const Char* kTmshIndexSignature  = "TIDX";

TmshHeader& TmshHeader::operator=(const TmshHeader& rhs) {
    std::strncpy(signature, rhs.signature, kSignatureLength);
    version            = rhs.version;
    vertex_chunk_count = rhs.vertex_chunk_count;
    data_size          = rhs.data_size;

    return *this;
}

TmshVertexHeader& TmshVertexHeader::operator=(const TmshVertexHeader& rhs) {
    std::strncpy(signature, rhs.signature, kSignatureLength);
    std::strncpy(attribute, rhs.attribute, kVertexAttributeLength);
    format       = rhs.format;
    vertex_count = rhs.vertex_count;
    data_size    = rhs.data_size;

    return *this;
}

TmshIndexHeader& TmshIndexHeader::operator=(const TmshIndexHeader& rhs) {
    std::strncpy(signature, rhs.signature, kSignatureLength);
    format         = rhs.format;
    primitive_type = rhs.primitive_type;
    index_count    = rhs.index_count;
    data_size      = rhs.data_size;

    return *this;
}

Tmsh::Tmsh(const ByteData& data) : byte_data_(data) {
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
    for (Int32 i = 0; i < header_->vertex_chunk_count; ++i) {
        // ヘッダ読み込み
        auto vertex_data = reinterpret_cast<VertexData*>(&byte_data_[index]);

        // シグネチャチェック
        String sig(vertex_data->header.signature, 4);
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
        String sig(index_data->header.signature, 4);
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
}
}
}
