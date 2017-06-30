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


Tmsh::Tmsh(const Mesh::VertexBufferTable& vertex_buffer_table, const Mesh::IndexBufferSPtr& index_buffer) {
}

}
}
}
