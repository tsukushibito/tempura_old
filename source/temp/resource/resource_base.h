﻿/**
 * @file resource_base.h
 * @brief resource base class
 * @author tsukushibito
 * @version 0.0.1
 * @date 2016-02-23
 */
#pragma once
#ifndef GUARD_7b165123cb9d40ba8f9fbe15833384b3
#define GUARD_7b165123cb9d40ba8f9fbe15833384b3

#include "temp/define.h"
#include "temp/type.h"

#include "temp/system/file_system.h"
#include "temp/system/thread_pool.h"

#include "temp/graphics_old/device.h"

namespace temp {
namespace resource {

template <typename Type>
class ResourceBase : public SmartPointerObject<Type> {
public:
    using Super = SmartPointerObject<Type>;
    /**
     * @brief loading state
     */
    enum class State {
        NotLoaded,
        Loading,
        Loaded,
        Unloading,
    };

private:
    using ResourceTable     = std::unordered_map<Size, typename Super::WPtr>;
    using ResourceTableUPtr = std::unique_ptr<ResourceTable>;

protected:
    explicit ResourceBase(const system::Path& path);

    ~ResourceBase();

public:
    static typename Super::SPtr create(const system::Path& path);
    
    static void terminate();

    State state() const;

    const system::Path& path() const;

    const Size hash() const;

    void load();

    std::future<void> asyncLoad();

    void unload();

protected:
    Vector<UInt8>& buffer();

private:
    void loadImpl(bool is_async = true);

    void login();  // ロード用スレッドで実行される

protected:
    static ResourceTable s_resource_table;
    static std::mutex    s_table_mutex;

    const system::Path path_;
    const Size         hash_;

    mutable std::mutex mutex_;
    State              state_;
    Vector<UInt8>      buffer_;
};
}
}

#include "resource_base_detail.h"

#endif  // GUARD_7b165123cb9d40ba8f9fbe15833384b3
