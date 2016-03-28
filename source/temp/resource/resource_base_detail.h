/**
 * @file resource_base_detail.h
 * @brief resource base class detail
 * @author tsukushibito
 * @version 0.0.1
 * @date 2016-02-23
 */
#include <fstream>
#include "temp/temp_assert.h"
#include "temp/system/logger.h"

namespace temp {
namespace resource {

template < typename T >
ResourceBase< T >::ResourceBase(const system::Path &path)
    : path_(path)
    , hash_(path.getHash())
    , state_(State::NotLoaded) {}

template < typename T >
ResourceBase< T >::~ResourceBase() {
    // リソース解放
    unload();

    std::unique_lock< std::mutex > lock(s_table_mutex);
    TEMP_ASSERT(s_resource_table->find(hash_) != s_resource_table->end()
                && "Not exist in the table. Management is out of resources.");

    // 管理テーブルから削除
    s_resource_table->erase(hash_);

    temp::system::ConsoleLogger::trace("[resource] Deleted : path = {0} : hash = {1}", path_.getRelative().c_str(), hash_);
}

template < typename T >
typename ResourceBase< T >::SPtr ResourceBase< T >::create(const String &path) {
    return create(system::Path(path));
}

template < typename T >
typename ResourceBase< T >::SPtr ResourceBase< T >::create(const system::Path &path) {
    std::unique_lock< std::mutex > lock(s_table_mutex);

    // 管理テーブルに既に存在しているパスであれば、それを返す
    Size hash = path.getHash();
    if (s_resource_table->find(hash) != s_resource_table->end()) {
        return std::move((*s_resource_table)[hash].lock());
    }

    // リソース作成
    struct Creator : public T {
        explicit Creator(const system::Path &path)
            : T(path) {}
    };
    auto p = std::make_shared< Creator >(path);
    (*s_resource_table)[hash] = p;
    temp::system::ConsoleLogger::trace("[resource] Created : path = {0} : hash = {1}", path.getRelative().c_str(), hash);
    return std::move(p);
}

template < typename T >
void ResourceBase< T >::initialize(const system::ThreadPool::SPtr &load_thread,
        const graphics::Device::SPtr &graphics_device) {
    s_resource_table.reset(new ResourceTable);
    s_load_thread = load_thread;
    s_graphics_device = graphics_device;

    // initializeSpecificPlatform();
}

template < typename T >
void ResourceBase< T >::terminate() {
    // terminateSpecificPlatform();

    s_graphics_device = nullptr;
    s_load_thread = nullptr;
    TEMP_ASSERT(s_resource_table->empty() && "Exists not released resource.");
    s_resource_table.release();
}

template < typename T >
typename ResourceBase< T >::State ResourceBase< T >::getState() const {
    std::unique_lock< std::mutex > lock(mutex_);
    return state_;
}

template < typename T >
const system::Path &ResourceBase< T >::getPath() const {
    return path_;
}

template < typename T >
const Size ResourceBase< T >::getHash() const {
    return hash_;
}

template < typename T >
void ResourceBase< T >::load() {
    std::unique_lock< std::mutex > lock(mutex_);
    if (state_ != State::NotLoaded) return;
    loadImpl(false);
    state_ = State::Loaded;
}

template < typename T >
std::future<void> ResourceBase< T >::asyncLoad() {
    std::unique_lock< std::mutex > lock(mutex_);
    if (state_ != State::NotLoaded) return std::future<void>();
    state_ = State::Loading;

    return s_load_thread->pushJob(std::bind(&T::loadImpl, this, true));
}

template < typename T >
void ResourceBase< T >::unload() {
    std::unique_lock< std::mutex > lock(mutex_);
    if (state_ == State::NotLoaded || state_ == State::Unloading) return;
    temp::system::ConsoleLogger::trace("[resource] unloading : path = {0} : hash = {1}", path_.getRelative().c_str(), hash_);
    state_ = State::Unloading;

    String().swap(buffer_); // メモリ解放

    state_ = State::NotLoaded;
}

template < typename T >
String &ResourceBase< T >::getBuffer() {
    return buffer_;
}

template < typename T >
graphics::Device::SPtr ResourceBase< T >::getGraphicsDevcie() {
    return s_graphics_device;
}

template < typename T >
system::ThreadPool::SPtr ResourceBase< T >::getLoadThread() {
    return s_load_thread;
}

template < typename T >
void ResourceBase< T >::loadImpl(bool isAsync) {
    using namespace std;
    temp::system::ConsoleLogger::trace("[resource] loading({2}) : path = {0} : hash = {1}", path_.getRelative().c_str(), hash_, isAsync ? "async" : "sync");
    // 同期、非同期で排他処理の有無を分ける必要があるので、処理を一旦ラムダに持たせる
    auto load_ = [this](){

        ifstream ifs(path_.getAbsolute().c_str());

        istreambuf_iterator< char > begin(ifs);
        istreambuf_iterator< char > end;
        buffer_.assign(begin, end);

        ifs.close();

        login();

        state_ = State::Loaded;
    };

    if (isAsync) {
        lock_guard< mutex > lock(mutex_);
        load_();
    }
    else {
        load_();
    }
}

template < typename T >
void ResourceBase< T >::login() {
    // 静的多態の場合
    static_cast< T * >(this)->loginImpl();

    // 動的多態の場合
    // loginImpl();
}

// Tのデストラクタ呼び出し後に呼び出されるので、ログアウト処理の実装はTのデストラクタ内で行うようにする
// template < typename T >
// void ResourceBase< T >::logout() {
//     // 静的多態の場合
//     static_cast< T * >(this)->logoutImpl();

//     // 動的多態の場合
//     // logoutImpl();
// }

template < typename T >
system::ThreadPool::SPtr ResourceBase< T >::s_load_thread = nullptr;

template < typename T >
graphics::Device::SPtr ResourceBase< T >::s_graphics_device = nullptr;

template < typename T >
typename ResourceBase< T >::ResourceTableUPtr ResourceBase< T >::s_resource_table = nullptr;

template < typename T >
std::mutex ResourceBase< T >::s_table_mutex;

}
}
