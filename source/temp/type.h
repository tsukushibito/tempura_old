/**
 * @file type.h
 * @brief type defines
 * @author tsukushibito
 * @version 0.0.1
 * @date 2016-02-20
 */
#pragma once
#ifndef GUARD_6b1252d3036740fdad7d9e1dd5fe06c9
#define GUARD_6b1252d3036740fdad7d9e1dd5fe06c9

#include <cstdint>
#include <memory>
#include <utility>

#define TEMP_DEFINE_ALIAS(name, target)  \
template<typename... Args>      \
inline auto name(Args&&... args) -> decltype(target(std::forward<Args>(args)...))   \
{ return target(std::forward<Args>(args)...);   }


namespace temp {

using Int8 = std::int8_t;
using Int16 = std::int16_t;
using Int32 = std::int32_t;
using Int64 = std::int64_t;

using UInt8 = std::uint8_t;
using UInt16 = std::uint16_t;
using UInt32 = std::uint32_t;
using UInt64 = std::uint64_t;

using Float32 = float;
using Float64 = double;

using Bool = bool;
using Char = char;
using Size = size_t;

class Uncopyable {
protected:
    Uncopyable() = default;
    ~Uncopyable() = default;

private:
    Uncopyable(const Uncopyable &) = delete;
    Uncopyable &operator=(const Uncopyable &) = delete;
};

template < typename T >
class Singleton : Uncopyable {
protected:
    Singleton() = default;
    virtual ~Singleton() = default;

public:
    static T &getInstance() {
        static T instance;
        return instance;
    }
};

template < typename T >
class SmartPointerObject : Uncopyable {
public:
    using UPtr = std::unique_ptr< T >;
    using SPtr = std::shared_ptr< T >;
    using WPtr = std::weak_ptr< T >;

protected:
    SmartPointerObject() {}
};

template < typename T >
class Optional {
public:
    Optional()
        : is_engaged_(false)
        , value_() {}

    explicit Optional(const T &value)
        : is_engaged_(true)
        , value_(value) {}

    Optional &operator=(const T &value) {
        value_ = value;
        is_engaged_ = true;
        return *this;
    }

    // bool型への暗黙変換
    operator bool() const { return is_engaged_; }

    // 内部オブジェクトへのアクセッサ
    T const &operator*() const { return value_; }
    T &operator*() { return value_; }

private:
    bool is_engaged_;
    T value_;
};

} // namespace temp
#endif // GUARD_6b1252d3036740fdad7d9e1dd5fe06c9
