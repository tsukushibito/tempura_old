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
// #include "Graphics/GraphicsDevice.h"

namespace temp {
namespace resource {
template < typename T >
class ResourceBase : public SmartPointerObject< ResourceBase< T > > {
public:
    using SmartPtrType = SmartPointerObject< ResourceBase< T > >;
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

    static void initialize(const system::ThreadPool::SPtr &load_thread/*, const graphics::GraphicsDevice::SPtr &spGraphicsDevice*/);

    static void terminate();

    State getState() const;

    const system::Path &getPath() const;

    const Size getHash() const;

    void load();

    void asyncLoad();

    void unload();

protected:
    String &getBuffer();

    // static graphics::GraphicsDevice::SPtr getGraphicsDevcie();
    static system::ThreadPool::SPtr getLoadThread();

private:
    void loadImpl(bool is_async = true);

    void login(); // ロード用スレッドで実行される

    void logout(); // どのスレッドで実行されるか不定

protected:
    virtual void loginImpl();
    virtual void logoutImpl();

    // depend on platform
    // static void initializeSpecificPlatform();
    // static void terminateSpecificPlatform();

    static system::ThreadPool::SPtr s_load_thread;
    // static graphics::GraphicsDevice::SPtr s_spGraphicsDevice;
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
#ifdef TEMP_GRAPHICS_OPENGL
#ifdef TEMP_PLATFORM_WINDOWS
// #include "OpenGL/Windows/ResourceBaseDetailOpenGLWindows.h"
#elif defined TEMP_PLATFORM_MAC
// #include "OpenGL/Mac/ResourceBaseDetailOpenGLMac.h"
#endif
#else
#endif

#endif // GUARD_7b165123cb9d40ba8f9fbe15833384b3
