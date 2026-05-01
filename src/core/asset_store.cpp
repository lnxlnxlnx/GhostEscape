#include "asset_store.h"

// asset_store.cpp
void AssetStore::clean()
{
    for (auto &texture : textures_)
    {
        SDL_DestroyTexture(texture.second);
    }
    textures_.clear();

    for (auto &sound : sounds_)
    {
        Mix_FreeChunk(sound.second);
    }
    sounds_.clear();

    for (auto &music : music_)
    {
        Mix_FreeMusic(music.second);
    }
    music_.clear();

    for (auto &font : fonts_)
    {
        TTF_CloseFont(font.second);
    }
    fonts_.clear();
}

// asset_store.cpp
void AssetStore::loadImage(const std::string &file_path)
{
    SDL_Texture *texture = IMG_LoadTexture(renderer_, file_path.c_str());
    if (texture == nullptr)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to load image: %s", file_path.c_str());
        return;
    }
    // textures_[file_path] = texture;         // 可行，会覆盖之前的值。
    textures_.emplace(file_path, texture);   // 如果已经存在，则不会插入。
}

void AssetStore::loadSound(const std::string &file_path)
{
    Mix_Chunk *sound = Mix_LoadWAV(file_path.c_str());
    if (sound == nullptr)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to load sound: %s", file_path.c_str());
        return;
    }
    sounds_.emplace(file_path, sound);
}

void AssetStore::loadMusic(const std::string &file_path)
{
    Mix_Music *music = Mix_LoadMUS(file_path.c_str());
    if (music == nullptr)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to load music: %s", file_path.c_str());
        return;
    }
    music_.emplace(file_path, music);
}

void AssetStore::loadFont(const std::string &file_path, int font_size)
{
    TTF_Font *font = TTF_OpenFont(file_path.c_str(), font_size);
    if (font == nullptr)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to load font: %s", file_path.c_str());
        return;
    }
    fonts_.emplace(file_path + std::to_string(font_size), font);
}

// asset_store.cpp
SDL_Texture *AssetStore::getImage(const std::string &file_path)
{
    auto iter = textures_.find(file_path);
    if (iter == textures_.end())        // 如果没有找到，则载入。
    {
        loadImage(file_path);       // 载入图片，懒加载
        iter = textures_.find(file_path);
    }
    if (iter == textures_.end())        // 如果载入失败，则返回空指针。
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to get image: %s", file_path.c_str());
        return nullptr;
    }
    return iter->second;
}

Mix_Chunk *AssetStore::getSound(const std::string &file_path)
{
    auto iter = sounds_.find(file_path);
    if (iter == sounds_.end())          // 如果没有找到，则载入。
    {
        loadSound(file_path);
        iter = sounds_.find(file_path);
    }
    if (iter == sounds_.end())          // 如果载入失败，则返回空指针。
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to get sound: %s", file_path.c_str());
        return nullptr;
    }
    return iter->second;
}

Mix_Music *AssetStore::getMusic(const std::string &file_path)
{
    auto iter = music_.find(file_path);
    if (iter == music_.end())           // 如果没有找到，则载入。
    {
        loadMusic(file_path);
        iter = music_.find(file_path);
    }
    if (iter == music_.end())           // 如果载入失败，则返回空指针。
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to get music: %s", file_path.c_str());
        return nullptr;
    }
    return iter->second;
}

TTF_Font *AssetStore::getFont(const std::string &file_path, int font_size)
{
    auto iter = fonts_.find(file_path + std::to_string(font_size));
    if (iter == fonts_.end())           // 如果没有找到，则载入。
    {
        loadFont(file_path, font_size);
        iter = fonts_.find(file_path + std::to_string(font_size));
    }
    if (iter == fonts_.end())           // 如果载入失败，则返回空指针。
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to get font: %s", file_path.c_str());
        return nullptr;
    }
    return iter->second;
}

void AssetStore::preloadResources(const std::vector<std::string>& imagePaths, 
                                  const std::vector<std::string>& soundPaths,
                                  const std::vector<std::string>& musicPaths)
{
    // 加载所有图像
    for (const auto& path : imagePaths) {
        loadImage(path);
    }
    
    // 加载所有音效
    for (const auto& path : soundPaths) {
        loadSound(path);
    }
    
    // 加载所有音乐
    for (const auto& path : musicPaths) {
        loadMusic(path);
    }
}

void AssetStore::unloadImage(const std::string& file_path)
{
    auto iter = textures_.find(file_path);
    if (iter != textures_.end()) {
        SDL_DestroyTexture(iter->second);
        textures_.erase(iter);
    }
}

void AssetStore::unloadSound(const std::string &file_path)
{
    auto iter = sounds_.find(file_path);
    if (iter != sounds_.end()) {
        Mix_FreeChunk(iter->second);
        sounds_.erase(iter);
    }
}

void AssetStore::unloadMusic(const std::string &file_path)
{
    auto iter = music_.find(file_path);
    if (iter != music_.end()) {
        Mix_FreeMusic(iter->second);
        music_.erase(iter);
    }
}

void AssetStore::unloadFont(const std::string &file_path)
{
    auto iter = fonts_.find(file_path);
    if (iter != fonts_.end()) {
        TTF_CloseFont(iter->second);
        fonts_.erase(iter);
    }
}





