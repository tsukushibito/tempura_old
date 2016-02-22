/**
 * @file file_system.h
 * @brief file system 
 * @author tsukushibito
 * @version 0.0.1
 * @date 2015-04-03
 */
#pragma once
#ifndef GUARD_09a682659d4d459aa392b530fc1ec178
#define GUARD_09a682659d4d459aa392b530fc1ec178

#include "temp/type.h"

namespace temp {
namespace system {

class Path {
    friend bool operator==(const Path &lhs, const Path &rhs) { return lhs.hash_ == rhs.hash_; }
    friend bool operator!=(const Path &lhs, const Path &rhs) { return !(lhs == rhs); }

public:
    // MSVC12.0だとムーブコンストラクタとムーブ代入演算子の暗黙定義に対応していないので
    // 明示的に定義
    // constractor
    Path() = default;
    explicit Path(const String &string);
    Path(const Path &) = default;
    Path(Path &&rhs) { *this = std::move(rhs); }

    // destractor
    ~Path() = default;

    // assignment operator
    Path &operator=(const Path &rhs) = default;
    Path &operator=(Path &&rhs) {
        if (this != &rhs) {
            absolute_path_string_ = std::move(rhs.absolute_path_string_);
            root_ = std::move(rhs.root_);
            element_names_ = std::move(rhs.element_names_);
        }
        return *this;
    }

    String getAbsolute() const;
    String getRootName() const;
    String getRoot() const;
    String getParent() const;
    String getFileName() const;
    String getStem() const;
    String getExtension() const;
    String getRelative(const Path &base = Path(".")) const;

    Bool isEmpty() const;

    Size getHash() const { return hash_; }

private:
    void convertToAbsolutePath(String &string);

private:
    Size hash_ = 0;
    String absolute_path_string_;
    String root_;
    Vector< String > element_names_;
};

void setCurrentDirectory(const Path &path);
void setCurrentDirectory(const String &path);
Path getCurrentDirectory();

}
}

#endif // GUARD_09a682659d4d459aa392b530fc1ec178
