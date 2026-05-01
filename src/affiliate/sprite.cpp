#include "sprite.h"
#include "../core/game.h"
#include "../core/asset_store.h"
#include <spdlog/spdlog.h>
Texture::Texture(std::string_view file_path)
{
    texture = Game::GetInstance().getAssetStore()->getImage(std::string(file_path));
    if (texture)
    {
        SDL_GetTextureSize(texture, &src_rect.w, &src_rect.h);
    }else{
        spdlog::error("Failed to load texture: {}", file_path);
    }
}

Sprite *Sprite::addSpriteChild(ObjectScreen *parent, const std::string &file_path, float scale)
{
    Sprite *sprite = new Sprite();
    sprite->init();
    sprite->setTexture(Texture(file_path));
    sprite->setScale(scale);
    sprite->setParent(parent);
    parent->addChild(sprite);
    return sprite;
}

// sprite.cpp
void Sprite::render()
{
    if (texture_.texture == nullptr)
    {
        return;
    }
    if (parent_ == nullptr)
    {
        return;
    }
    auto pos = parent_->getRenderPosition() + offset_;
    game_.renderTexture(texture_, pos, size_);
}

void Sprite::setTexture(const Texture &texture)
{
    texture_ = texture;
    size_ = glm::vec2(texture.src_rect.w, texture.src_rect.h);
}

