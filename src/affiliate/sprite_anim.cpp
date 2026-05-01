// sprite_anim.cpp
#include "sprite_anim.h"
void SpriteAnim::updateAnimByPlayMode(float dt)
{
    frame_timer_ += dt;
    if (frame_timer_ >= 1.0f / fps_)
    {
        frame_timer_ = 0.0f;
        switch (play_mode_)
        {
        case SpriteAnimPlayMode::PLAY_LOOP:
            current_frame_ = (current_frame_ + 1) % total_frames_;
            break;
        case SpriteAnimPlayMode::PLAY_ONCE:
            current_frame_++;
            if (current_frame_ == total_frames_ + 1)
            {
                setFinished(true);
                setActive(false); // 播放完成后禁用对象
                // TODO: 暂时还不知道怎么往下处理finish
            }
            break;
        case SpriteAnimPlayMode::PLAY_PING_PONG:
            static bool flip = false;
            if (current_frame_ == total_frames_)
            {
                flip = true;
            }
            else if (current_frame_ == 0)
            {
                flip = false;
            }
            if (flip)
            {
                current_frame_--;
            }
            else
            {
                current_frame_++;
            }
            break;
        }

        texture_.src_rect.x = current_frame_ * texture_.src_rect.w;
    }
}
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
    updateAnimByPlayMode(dt);
}

void SpriteAnim::setTexture(const Texture &texture)
{
    texture_ = texture;
    total_frames_ = texture.src_rect.w / texture.src_rect.h;
    texture_.src_rect.w = texture.src_rect.h;
    size_ = glm::vec2(texture_.src_rect.w, texture_.src_rect.h);
}
