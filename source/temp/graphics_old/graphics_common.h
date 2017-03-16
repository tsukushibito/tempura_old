/**
 * @file graphics_common.h
 * @brief graphics common
 * @author tsukushibito
 * @version 0.0.1
 * @date 2016-02-28
 */
#pragma once
#ifndef GUARD_841e52ffb1844f19a25f12e5556d4cc1
#define GUARD_841e52ffb1844f19a25f12e5556d4cc1

#include "temp/type.h"

namespace temp {
namespace graphics_old {

struct NativeHandle {
    union {
        void *pointer;
        Int32 value;
    };
};

static const Size kImplSize = 10 * sizeof(void *);

// Buffer class for fast pimpl idiom
class FastPImpl {
public:
    FastPImpl() { memset(impl_buffer_, 0, sizeof(impl_buffer_)); }

protected:
    Int8 impl_buffer_[kImplSize];
};

enum class InputElementFormat {
    Float32,
    Int16,
    Int32,
};

struct InputElementDesc {
    String name;
    UInt32 slot;
    InputElementFormat format;
    UInt32 count;
    UInt32 offset;
};

enum class BlendMode {
    None,
    AlphaBlending,
    Add,
    Subtract,
    Multiply,
    Screen,
};

enum class DepthStencileFunc {
    Never,
    Less,
    LessEqual,
    Equal,
    GreaterEqual,
    Greater,
    NotEqual,
    Always,
};

enum class FillMode {
    Line,
    Fill,
};

enum class CullingMode {
    CullingNone,
    CullingFront,
    CullingBack,
};

enum class FrontFace {
    ClockWise,
    CounterClockWise,
};

struct RasterizerDesc {
    FillMode fill_mode;
    CullingMode cull_mode;
    FrontFace front_face;
};


} // namespace graphics
} // namespace temp

#endif // GUARD_841e52ffb1844f19a25f12e5556d4cc1
