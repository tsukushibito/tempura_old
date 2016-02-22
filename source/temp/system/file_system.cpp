#include <algorithm>
#include <sstream>
#include "temp/system/file_system.h"

namespace temp {
namespace system {

namespace {
    
void backslashToSlash(String &string) { std::replace(string.begin(), string.end(), '\\', '/'); }
    
inline Vector<String> splitString(const String &str, char delim) {
    Vector<String> elems;
    std::stringstream ss(str);
    String item;
    while (getline(ss, item, delim)) {
        if (!item.empty()) {
            elems.push_back(item);
        }
    }
    
    return std::move(elems);
}

struct DecomposedPath {
    String root_;
    Vector< String > element_names_;
};

DecomposedPath decomposeAbsolutePath(const String &absPath) {
    DecomposedPath decomposedPath;

    decomposedPath.element_names_ = splitString(absPath, '/');

    String topOneChar;
    String topTowChar;
    if (absPath.size() >= 1) topTowChar = absPath.substr(0, 1);
    if (absPath.size() >= 2) topTowChar = absPath.substr(0, 2);
    if (topTowChar == "//") {
        // URL todo: 不完全な実装なので、正しく実装
        decomposedPath.root_ = "//";
    } else if (topOneChar == "/") {
        // Windows以外のパス
        decomposedPath.root_ = "/";
    } else if (decomposedPath.element_names_.size() > 0) {
        // Windowsのパス
        // ドライブ名を含むかチェック
        size_t pos = decomposedPath.element_names_[0].find_first_of(':');
        if (pos != String::npos) {
            decomposedPath.root_ = decomposedPath.element_names_[0] + "/";
            decomposedPath.element_names_.erase(decomposedPath.element_names_.begin());
        }
    }

    if (!absPath.empty()) {
        Char lastChar = *(--absPath.end());
        if (lastChar == '/') {
            decomposedPath.element_names_.push_back("");
        }
    }

    return std::move(decomposedPath);
}

} // namespace

Path::Path(const String &string) : absolute_path_string_(string) {
    convertToAbsolutePath(absolute_path_string_);
    backslashToSlash(absolute_path_string_);
    hash_ = std::hash< String >()(absolute_path_string_);
    DecomposedPath decomposed = decomposeAbsolutePath(absolute_path_string_);
    root_ = std::move(decomposed.root_);
    element_names_ = std::move(decomposed.element_names_);
}

String Path::getAbsolute() const { return absolute_path_string_; }

String Path::getRootName() const {
    // TODO: URL用の実装
    using namespace std;
    size_t pos = root_.find_first_of(":");
    if (pos == string::npos) {
        return "";
    }
    return root_.substr(0, pos + 1);
}

String Path::getRoot() const { return root_; }

String Path::getParent() const {
    String parent = getRootName();
    if (element_names_.size() >= 1) {
        for (UInt32 i = 0; i < element_names_.size() - 1; ++i) {
            parent += "/" + element_names_[i];
        }
    }

    return parent;
}

String Path::getRelative(const Path &base) const {
    if (root_ != base.root_) {
        return absolute_path_string_;
    }

    Size commonDirLevel = 0;
    for (; commonDirLevel < base.element_names_.size(); ++commonDirLevel) {
        if (element_names_[commonDirLevel] != base.element_names_[commonDirLevel]) {
            break;
        }
    }

    Size parentLevel = (base.element_names_.size()) - commonDirLevel;

    String relative;
    for (Size i = 0; i < parentLevel; ++i) {
        relative += "../";
    }

    for (Size i = commonDirLevel; i < element_names_.size(); ++i) {
        relative += element_names_[i];
        if (i < element_names_.size() - 1) {
            relative += "/";
        }
    }

    return relative;
}

String Path::getFileName() const {
    String fileName;
    if (element_names_.size() >= 1) {
        fileName = element_names_[element_names_.size() - 1];
    }

    return fileName;
}

String Path::getStem() const {
    String stem = getFileName();
    size_t pos = stem.find_last_of('.');
    if (pos != String::npos) {
        stem = stem.substr(0, pos);
    }
    return stem;
}

String Path::getExtension() const {
    String extension;
    String fileName = getFileName();
    size_t pos = fileName.find_last_of('.');
    if (pos != String::npos && pos < fileName.size() - 1) {
        extension = fileName.substr(pos);
    }

    return extension;
}

Bool Path::isEmpty() const { return absolute_path_string_.empty(); }

void setCurrentDirectory(const String &path) { setCurrentDirectory(Path(path)); }

}
}
