#ifndef BF50431D_FA79_44E9_A0A0_7290A39F43BD
#define BF50431D_FA79_44E9_A0A0_7290A39F43BD
#include "core/asset_store.h"
#include <fstream>
#include <nlohmann/json.hpp>

class AssetManager
{
public:
    AssetStore *asset_store_;
    nlohmann::json json_data;
    AssetManager(AssetStore *asset_store, const std::string &config_file);
    ~AssetManager() = default;

    void clean();
    void loadImage(const std::string &file_id);
    void loadSound(const std::string &file_id);
    void loadMusic(const std::string &file_id);
    void loadFont(const std::string &file_id);

    SDL_Texture* getImage(const std::string &file_id);
    Mix_Chunk* getSound(const std::string &file_id);
    Mix_Music* getMusic(const std::string &file_id);
    TTF_Font* getFont(const std::string &file_id);
};

#endif /* BF50431D_FA79_44E9_A0A0_7290A39F43BD */
