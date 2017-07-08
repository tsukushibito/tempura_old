#ifndef TMEP_GUARD
#define TEMP_GUARD

namespace temp {
namespace resource {

struct VertexData {
	graphics::VertexAttribute attribute;
	graphics::VertexBufferFormat format;
	ByteData byte_data;
};
using VertexDataTable = HashMap<graphics::VertexAttribute, VertexData, graphics::VertexAttributeHash>;

struct IndexData {
	graphics::IndexBufferFormat format;
	graphics::PrimitiveType primitive_type;
	ByteData byte_data;
};

}
}

#endif