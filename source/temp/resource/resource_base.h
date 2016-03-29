/**
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

#include "temp/system/thread_pool.h"
#include "temp/system/file_system.h"

#include "temp/graphics/device.h"

namespace temp {
namespace resource {

template < typename T >
class ResourceBase : public SmartPointerObject< T > {
public:
    using SmartPtrType = SmartPointerObject< T >;
    using UPtr = typename SmartPtrType::UPtr;
    using SPtr = typename SmartPtrType::SPtr;
    using WPtr = typename SmartPtrType::WPtr;

    /**
     * @brief loading state
     */
    enum class State {
        NotLoaded,
        Loading,
        Loaded,
        Unloading,
        Max,
    };

private:
    using ResourceTable = std::unordered_map< Size, WPtr >;
    using ResourceTableUPtr = std::unique_ptr< ResourceTable >;

protected:
    explicit ResourceBase(const system::Path &path);

    ~ResourceBase();

public:
    static SPtr create(const String &path);

    static SPtr create(const system::Path &path);

    static void initialize(const system::ThreadPool::SPtr &load_thread, const graphics::Device::SPtr &graphics_device);

    static void terminate();

    State getState() const;

    const system::Path &getPath() const;

    const Size getHash() const;

    void load();

    std::future<void> asyncLoad();

    void unload();

protected:
    String &getBuffer();

    static graphics::Device::SPtr getGraphicsDevcie();
    static system::ThreadPool::SPtr getLoadThread();

private:
    void loadImpl(bool is_async = true);

    void login(); // ロード用スレッドで実行される

protected:

    static system::ThreadPool::SPtr s_load_thread;
    static graphics::Device::SPtr s_graphics_device;
    static ResourceTableUPtr s_resource_table;
    static std::mutex s_table_mutex;

    const system::Path path_;
    const Size hash_;

    mutable std::mutex mutex_;
    State state_;
    String buffer_;
};

}
}

#include "resource_base_detail.h"

#endif // GUARD_7b165123cb9d40ba8f9fbe15833384b3
