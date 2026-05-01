#include "config_manager.h"
#include <fstream>
#include <sstream>
#include <spdlog/spdlog.h>

bool Config::load(const std::string& file_path) {
    std::ifstream file(file_path);
    if (!file.is_open()) {
        spdlog::error("Failed to open file: {}", file_path);
        return false;
    }

    try {
        file >> root_;
    } catch (...) {
        spdlog::error("Failed to parse JSON from file: {}", file_path);
        return false;
    }
    return true;
}

bool Config::reload(const std::string& new_file_path) {
    clear();          // 清空旧数据
    return load(new_file_path); // 加载新数据
}
bool Config::save(const std::string& file_path) const {
    std::ofstream file(file_path);
    if (!file.is_open()) return false;

    file << root_.dump(4); // 格式化输出，缩进4
    return true;
}

void Config::clear() {
    root_.clear();
}

std::vector<std::string> Config::splitKey(const std::string& key) const {
    std::vector<std::string> keys;
    std::stringstream ss(key);
    std::string part;

    while (std::getline(ss, part, '.')) {
        keys.push_back(part);
    }
    return keys;
}