#include "asset_manager.h"
#include <spdlog/spdlog.h>

AssetManager::AssetManager(AssetStore *asset_store, const std::string &config_file)
{
    asset_store_ = asset_store;
    std::ifstream file(config_file);
    file >> json_data;
    file.close();
    spdlog::info("JSON 成功载入!");
}

void AssetManager::clean()
{
    asset_store_->clean();
    delete asset_store_;
    asset_store_ = nullptr;
}

void AssetManager::loadImage(const std::string &file_id)
{
    asset_store_->loadImage(json_data.at("images").value(file_id, ""));
}
