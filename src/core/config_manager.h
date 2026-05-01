#pragma once

#include <string>
#include <vector>
#include <nlohmann/json.hpp>
#include <spdlog/spdlog.h>
#include <glm/glm.hpp>

using json = nlohmann::json;

// 为 glm::vec2 提供 JSON 转换支持
namespace nlohmann {
    template <>
    struct adl_serializer<glm::vec2> {
        static void to_json(json& j, const glm::vec2& v) {
            j = json{{"x", v.x}, {"y", v.y}};
        }

        static void from_json(const json& j, glm::vec2& v) {
            if (j.is_array() && j.size() >= 2) {
                v.x = j[0].get<float>();
                v.y = j[1].get<float>();
            } else if (j.is_object() && j.contains("x") && j.contains("y")) {
                v.x = j["x"].get<float>();
                v.y = j["y"].get<float>();
            } else {
                v = glm::vec2(0.0f);
            }
        }
    };

    template <>
    struct adl_serializer<glm::vec3> {
        static void to_json(json& j, const glm::vec3& v) {
            j = json{{"x", v.x}, {"y", v.y}, {"z", v.z}};
        }

        static void from_json(const json& j, glm::vec3& v) {
            if (j.is_array() && j.size() >= 3) {
                v.x = j[0].get<float>();
                v.y = j[1].get<float>();
                v.z = j[2].get<float>();
            } else if (j.is_object() && j.contains("x") && j.contains("y") && j.contains("z")) {
                v.x = j["x"].get<float>();
                v.y = j["y"].get<float>();
                v.z = j["z"].get<float>();
            } else {
                v = glm::vec3(0.0f);
            }
        }
    };

    template <>
    struct adl_serializer<glm::vec4> {
        static void to_json(json& j, const glm::vec4& v) {
            j = json{{"x", v.x}, {"y", v.y}, {"z", v.z}, {"w", v.w}};
        }

        static void from_json(const json& j, glm::vec4& v) {
            if (j.is_array() && j.size() >= 4) {
                v.x = j[0].get<float>();
                v.y = j[1].get<float>();
                v.z = j[2].get<float>();
                v.w = j[3].get<float>();
            } else if (j.is_object() && j.contains("x") && j.contains("y") && j.contains("z") && j.contains("w")) {
                v.x = j["x"].get<float>();
                v.y = j["y"].get<float>();
                v.z = j["z"].get<float>();
                v.w = j["w"].get<float>();
            } else {
                v = glm::vec4(0.0f);
            }
        }
    };
}

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