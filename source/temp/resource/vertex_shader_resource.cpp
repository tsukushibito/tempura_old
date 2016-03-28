/**
 * @file vertex_shader_resource.cpp
 * @brief vertex shader resource
 * @author tsukushibito
 * @version 0.0.1
 * @date 2016-03-28
 */

#include "temp/resource/vertex_shader_resource.h"

namespace temp {
namespace resource {

VertexShader::VertexShader(const system::Path &path) : ResourceBase<VertexShader>(path) {
}

void VertexShader::loginImpl() {
	// auto future = s_load_thread->pushJob([this](){
	// 	vertex_shader_ = s_graphics_device->createVertexShaderFromSource(buffer_);
	// });

	// future.wait();
	vertex_shader_ = s_graphics_device->createVertexShaderFromSource(buffer_);
}

void VertexShader::logoutImpl() {
	// デストラクタが呼ばれた後に呼ばれてしまうので、何も処理できない。
	// todo:修正
}

}
}
