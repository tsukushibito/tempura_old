/**
 * @file resource_base_detail.h
 * @brief resource base class detail
 * @author tsukushibito
 * @version 0.0.1
 * @date 2016-02-23
 */
#include <fstream>
#include "temp/system/logger.h"
#include "temp/temp_assert.h"

namespace temp {
namespace resource {

using temp::system::Logger;

template <typename Type>
ResourceBase<Type>::ResourceBase(const system::Path& path)
    : path_(path), hash_(path.getHash()), state_(State::NotLoaded) {}

template <typename Type>
ResourceBase<Type>::~ResourceBase() {
    // リソース解放
    unload();

    std::unique_lock<std::mutex> lock(s_table_mutex);
    TEMP_ASSERT(s_resource_table.find(hash_) != s_resource_table.end(),
                "Not exist in the table. Management is out of resources.");

    // 管理テーブルから削除
    s_resource_table.erase(hash_);

    Logger::trace("[{0}] Deleted : path = {1} : hash = {2}", Type::kTypeName.c_str(), path_.getAbsolute().c_str(), hash_);
}

template <typename Type>
void ResourceBase<Type>::initialize(
    const system::ThreadPool::SPtr& loading_thread) {
    s_loading_thread = loading_thread;
}

template <typename Type>
void ResourceBase<Type>::terminate() {
    std::lock_guard<std::mutex> lock(s_table_mutex);
    for (auto&& key_value : s_resource_table) {
        auto&& res_wptr = key_value.second;
        auto&& res_sptr = res_wptr.lock();
        if (res_sptr) {
			Logger::trace("[{0}] {1} is not released!", Type::kTypeName.c_str(), res_sptr->path().getAbsolute());
        }
    }
    s_resource_table.clear();
    ResourceTable().swap(s_resource_table);
}

template <typename Type>
typename ResourceBase<Type>::ResourceSPtr ResourceBase<Type>::create(
    const system::Path& path) {
    std::unique_lock<std::mutex> lock(s_table_mutex);

    // 管理テーブルに既に存在しているパスであれば、それを返す
    Size hash = path.getHash();
    if (s_resource_table.find(hash) != s_resource_table.end()) {
        return std::move(s_resource_table[hash].lock());
    }

    // リソース作成
    struct Creator : public Type {
        explicit Creator(const system::Path& path) : Type(path) {}
    };
    auto p = std::make_shared<Creator>(path);

    s_resource_table[hash] = p;
	temp::system::Logger::trace("[{0}] Created : path = {1} : hash = {2}",
                                Type::kTypeName.c_str(), path.getAbsolute().c_str(), hash);
    return std::move(p);
}

template <typename Type>
typename ResourceBase<Type>::State ResourceBase<Type>::state() const {
    std::unique_lock<std::mutex> lock(mutex_);
    return state_;
}

template <typename Type>
const system::Path& ResourceBase<Type>::path() const {
    return path_;
}

template <typename Type>
const Size ResourceBase<Type>::hash() const {
    return hash_;
}

template <typename Type>
void ResourceBase<Type>::load() {
    std::unique_lock<std::mutex> lock(mutex_);
    if (state_ != State::NotLoaded) return;
    loadImpl(false);
    state_ = State::Loaded;
}

template <typename Type>
std::future<void> ResourceBase<Type>::asyncLoad() {
    std::unique_lock<std::mutex> lock(mutex_);
    if (state_ != State::NotLoaded) return std::future<void>();
    state_ = State::Loading;

    return s_loading_thread->pushJob([this]() { loadImpl(true); });
}

template <typename Type>
void ResourceBase<Type>::unload() {
    std::unique_lock<std::mutex> lock(mutex_);
    if (state_ == State::NotLoaded || state_ == State::Unloading) return;
    temp::system::Logger::trace(
		"[{0}] unloading : path = {1} : hash = {2}",
        Type::kTypeName.c_str(), path_.getAbsolute().c_str(), hash_);
    state_ = State::Unloading;

    ByteData().swap(byte_data_);  // メモリ解放

    state_ = State::NotLoaded;
}

template <typename Type>
typename ResourceBase<Type>::ByteData& ResourceBase<Type>::byteData() {
    return byte_data_;
}

template <typename Type>
void ResourceBase<Type>::loadImpl(bool isAsync) {
    using namespace std;
    temp::system::Logger::trace(
		"[{0}] loading({3}) : path = {1} : hash = {2}",
        Type::kTypeName.c_str(), path_.getAbsolute().c_str(), hash_, isAsync ? "async" : "sync");

    // 同期、非同期で排他処理の有無を分ける必要があるので、処理を一旦ラムダに持たせる
    auto load_task = [this]() {

        ifstream ifs(path_.getAbsolute().c_str());

        istreambuf_iterator<char> begin(ifs);
        istreambuf_iterator<char> end;
        byte_data_.assign(begin, end);

        ifs.close();

        login();

        state_ = State::Loaded;
    };

    if (isAsync) {
        lock_guard<mutex> lock(mutex_);
        load_task();
    } else {
        load_task();
    }
}

template <typename Type>
void ResourceBase<Type>::login() {
    // 静的多態の場合
    static_cast<Type*>(this)->loginImpl();

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

template <typename Type>
typename ResourceBase<Type>::ResourceTable ResourceBase<Type>::s_resource_table;

template <typename Type>
std::mutex ResourceBase<Type>::s_table_mutex;

template <typename Type>
system::ThreadPool::SPtr ResourceBase<Type>::s_loading_thread;
}
}
