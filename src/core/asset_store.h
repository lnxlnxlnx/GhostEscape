#ifndef B8FF0DEC_FBB6_4A53_BDD1_980ABFAB4BED
#define B8FF0DEC_FBB6_4A53_BDD1_980ABFAB4BED
// asset_store.h
#ifndef ASSET_STORE_H
#define ASSET_STORE_H
#include <unordered_map>  //无序map
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_mixer/SDL_mixer.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <string>

class AssetStore
{
    SDL_Renderer *renderer_ = nullptr;
    std::unordered_map<std::string, SDL_Texture*> textures_;
    std::unordered_map<std::string, Mix_Chunk*> sounds_;
    std::unordered_map<std::string, Mix_Music*> music_;
    std::unordered_map<std::string, TTF_Font*> fonts_;

public:

//NOTE: 如果是智能指针，则需要使用std::move()、game引用或者使用share_ptr
    AssetStore(SDL_Renderer* renderer) { renderer_ = renderer; }
    ~AssetStore() = default;

    void clean();

    // 4个载入函数
    void loadImage(const std::string& file_path);
    void loadSound(const std::string& file_path);
    void loadMusic(const std::string& file_path);
    void loadFont(const std::string& file_path, int font_size);

    // 4个读取函数
    SDL_Texture* getImage(const std::string& file_path);
    Mix_Chunk* getSound(const std::string& file_path);
    Mix_Music* getMusic(const std::string& file_path);
    TTF_Font* getFont(const std::string& file_path, int font_size);
};

#endif // ASSET_STORE_H

#endif /* B8FF0DEC_FBB6_4A53_BDD1_980ABFAB4BED */
