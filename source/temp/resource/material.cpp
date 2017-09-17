/**
 * @file material.cpp
 * @brief
 * @author tsukushibito
 * @version 0.0.1
 * @date 2017-09-05
 */

#include "temp/resource/material.h"

namespace temp {
namespace resource {

const temp::String Material::kTypeName = "Material";

void Material::initialize(const system::ThreadPool::SPtr& loading_thread) {
    Super::initialize(loading_thread);
}

void Material::terminate() {}

Material::Material(const system::Path& path) : Super(path) {}

void deserialize(std::ifstream& ifs) {}

void serialize(std::ofstream& ofs) {}
}
}
