#pragma once

#include <string>
#include <vector>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class Config
{
public:
    Config() = default;

    // 加载 / 保存文件
    bool load(const std::string &file_path);
    bool reload(const std::string &new_file_path);
    bool save(const std::string &file_path) const;

    // 清空数据
    void clear();

    // 获取值（支持嵌套 key："a.b.c"）
    template <typename T>
    T get(const std::string &key) const
    {
        std::vector<std::string> keys = splitKey(key);
        const json *node = &root_;

        for (const auto &k : keys)
        {
            if (!node->contains(k))
            {
                return T{};
            }
            node = &(*node)[k];
        }
        return node->get<T>();
    }

    // 👉 新增：找不到key就返回默认值
    template <typename T>
    T get(const std::string &key, const T &default_val) const
    {
        std::vector<std::string> keys = splitKey(key);
        const json *node = &root_;

        for (const auto &k : keys)
        {
            if (!node->contains(k))
                return default_val;
            node = &(*node)[k];
        }

        try
        {
            return node->get<T>();
        }
        catch (...)
        {
            // 类型不匹配也返回默认
            return default_val;
        }
    }

    // 设置值（支持嵌套 key："a.b.c"）
    template <typename T>
    void set(const std::string &key, const T &value)
    {
        std::vector<std::string> keys = splitKey(key);
        json *node = &root_;

        for (size_t i = 0; i < keys.size() - 1; ++i)
        {
            if (!node->contains(keys[i]))
            {
                (*node)[keys[i]] = json::object();
            }
            node = &(*node)[keys[i]];
        }
        (*node)[keys.back()] = value;
    }

    // 获取根节点（只读）
    const json &root() const { return root_; }

private:
    // 拆分 key："player.speed" → ["player", "speed"]
    std::vector<std::string> splitKey(const std::string &key) const;

private:
    json root_;
};