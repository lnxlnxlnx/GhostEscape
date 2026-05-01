// sprite_anim.cpp
#include "sprite_anim.h"
SpriteAnim *SpriteAnim::addSpriteAnimChild(ObjectScreen *parent, const std::string &file_path, float scale)
{
    auto sprite_anim = new SpriteAnim();
    sprite_anim->init();
    sprite_anim->setTexture(Texture(file_path));
    sprite_anim->setScale(scale);
    sprite_anim->setParent(parent);
    parent->addChild(sprite_anim);
    return sprite_anim;
}

void SpriteAnim::update(float dt)
{ 
    frame_timer_ += dt;
    if (frame_timer_ >= 1.0f / fps_)
    {
        frame_timer_ = 0.0f;
        current_frame_ = (current_frame_ + 1) % total_frames_;
        texture_.src_rect.x = current_frame_ * texture_.src_rect.w;
    }
    texture_.src_rect.x = current_frame_ * texture_.src_rect.w;
}

void SpriteAnim::setTexture(const Texture &texture)
{
    texture_ = texture;
    total_frames_ = texture.src_rect.w / texture.src_rect.h;
    texture_.src_rect.w = texture.src_rect.h;
    size_ = glm::vec2(texture_.src_rect.w, texture_.src_rect.h);
}
