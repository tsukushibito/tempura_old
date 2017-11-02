/**
 * @file texture.cpp
 * @brief
 * @author tsukushibito
 * @version 0.0.1
 * @date 2017-04-21
 */
#include "temp/resource_old/texture.h"

namespace temp {
namespace resource_old {

namespace {

const Int32 kVersion         = 1;
const Int32 kSignatureLength = 4;
const Char* kTextureSignature   = "TTEX";
}

temp::graphics_::Device::SPtr Texture::s_graphics_device;

const temp::String Texture::kTypeName = "Texture";

void Texture::initialize(const system::ThreadPool::SPtr& loading_thread,
                         const graphics_::DeviceSPtr&     device) {
    Super::initialize(loading_thread);
    s_graphics_device = device;
}

void Texture::terminate() {
    Super::terminate();
    s_graphics_device = nullptr;
}

Texture::Texture(const system::Path& path) : Super(path) {}

void Texture::deserialize(std::ifstream& ifs) {

    // using temp::system::Logger;

    Char signature[kSignatureLength];
    ifs.read(signature, kSignatureLength);
    if (memcmp(signature, kTextureSignature, kSignatureLength) != 0) {
        // Logger::error("[Texture::deserialize] illegal texture signature. path:{0}",
        //               path_.absolute().c_str());
        return;
    }

    Int32 version;
    ifs.read(reinterpret_cast<char*>(&version), sizeof(version));
    if (version != kVersion) {
        // バージョン違いのときの処理
    }

    temp::graphics_::TextureDesc desc;
    ifs.read(reinterpret_cast<char*>(&desc.format),
             sizeof(desc.format));
    ifs.read(reinterpret_cast<char*>(&desc.width),
             sizeof(desc.width));
    ifs.read(reinterpret_cast<char*>(&desc.height),
             sizeof(desc.height));
    ifs.read(reinterpret_cast<char*>(&desc.mipLevel),
             sizeof(desc.mipLevel));

    /*
    TextureFormat format;
    Size          width;
    Size          height;
    Int32         mipLevel;
    */
}

void Texture::serialize(std::ofstream& ofs) {
}
    
}
}
