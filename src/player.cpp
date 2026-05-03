// player.cpp
#include "player.h"
#include "core/scene.h"
#include "core/asset_store.h"
#include "affiliate/sprite.h"
#include "affiliate/sprite_anim.h"
#include <spdlog/spdlog.h>
#include "affiliate/collider.h"

void Player::init()
{
    Actor::init();
    max_speed_ = 500.0f;
    setMass(8.0f);

    // 加载玩家纹理
    auto sprite = SpriteAnim::addSpriteChild(this, game_.getConfig()->get<std::string>("player.texture", "assets/test/hp.png"));
    auto sprite_hp = SpriteAnim::addSpriteAnimChild(this, game_.getConfig()->get<std::string>("player.textureHp", "assets/test/hp.png"));

    
    sprite->autoResize();
    sprite_hp->setOffsetByAnchor(Anchor::TOP_CENTER);
    //sprite_hp->setOffset(sprite_hp->getOffset() + glm::vec2(0, -sprite->getSize().y ));
    sprite->setOffset(glm::vec2(- sprite->getSize().x / 2.0f, sprite->getSize().y / 2.0f));
    sprite_idle_ = SpriteAnim::addSpriteAnimChild(this, game_.getConfig()->get<std::string>("player.sprite_idle", "assets/sprite/ghost-idle.png"), 2.0f);
    sprite_move_ = SpriteAnim::addSpriteAnimChild(this, game_.getConfig()->get<std::string>("player.sprite_move", "assets/sprite/ghostDead-Sheet.png"), 2.0f);
    sprite_move_->setActive(false);

    sprite_hp->setOffsetByComponent(Anchor::BOTTOM_CENTER,Anchor::TOP_CENTER, sprite_idle_);
    //sprite_hp->setOffsetByComponent(Anchor::TOP_CENTER,Anchor::BOTTOM_CENTER, sprite_idle_);
    //sprite_hp->setOffsetByComponent(Anchor::TOP_CENTER,Anchor::CENTER, sprite_idle_);
    //sprite_hp->setOffsetByComponent(Anchor::CENTER,Anchor::CENTER, sprite_idle_);

    auto explosion_sprite = SpriteAnim::addSpriteAnimChild(this, game_.getConfig()->get<std::string>("test.texture_explosion", "assets/sprite/ghost-idle.png"), 2.0f);
    explosion_sprite->setPlayMode(SpriteAnimPlayMode::PLAY_ONCE);

    // 碰撞体
    collider_ = Collider::addColliderChild(this, sprite_idle_->getSize()/2.0f, Collider::Type::CIRCLE);
}

void Player::handleEvents(SDL_Event &event)
{
    Actor::handleEvents(event);
}

void Player::update(float dt)
{
    Actor::update(dt);      //NOTE: 先调用父类的update函数，父类的update函数会自动更新所有子对象（比如精灵动画），然后在这里再处理玩家自己的逻辑，比如输入、移动、状态切换等。
    keyboardControl();
    velocity_ *= 0.9f;
    if (glm::length(velocity_) < 0.1f)
    {
        velocity_ = glm::vec2(0, 0);
    }
    move(dt);
    updateState();
    syncCamera(dt);
    updateDash(dt);
}

void Player::render()
{
    Actor::render();
}

void Player::clean()
{
    Actor::clean();
}

void Player::keyboardControl()
{
    auto currentKeyStates = SDL_GetKeyboardState(NULL);
    auto temp_velocity = glm::vec2(velocity_.x, velocity_.y);
    if (currentKeyStates[SDL_SCANCODE_W])
    {
        temp_velocity.y = -max_speed_;
    }
    if (currentKeyStates[SDL_SCANCODE_S])
    {
        temp_velocity.y = max_speed_;
    }
    if (currentKeyStates[SDL_SCANCODE_A])
    {
        temp_velocity.x = -max_speed_;
    }
    if (currentKeyStates[SDL_SCANCODE_D])
    {
        temp_velocity.x = max_speed_;
    }
    if (currentKeyStates[SDL_SCANCODE_LSHIFT] && !is_dashing_ && dash_cool_down <= 0.0f)
    {
        is_dashing_ = true;
        dash_cool_down = 1.0f;
        dash_timer_ = dash_duration_;
        temp_velocity *= 3.0f;
        setMaxSpeed(max_speed_ * 3.0f);
    }
    velocity_ = temp_velocity;
}

void Player::move(float dt)
{
    setPosition(position_ + velocity_ * dt);
    // SDL_Log("dt: %f, position: (%f, %f), velocity: (%f, %f)", dt, position_.x, position_.y, velocity_.x, velocity_.y);
    position_ = glm::clamp(position_, glm::vec2(0), game_.getCurrentScene()->getWorldSize());
}

void Player::syncCamera(float dt)
{
    //BUG: 导致玩家在靠近边界时摄像机无法跟随玩家移动
    // game_.getCurrentScene()->setCameraPosition(position_ - game_.getScreenSize() / 2.0f);
    float dead_zone_percentage = 0.3f;
    float dead_zone_width = game_.getScreenSize().x * dead_zone_percentage;
    float dead_zone_height = game_.getScreenSize().y * dead_zone_percentage;
    SDL_FRect dead_zone = {
        static_cast<float>((game_.getCurrentScene()->getCameraPos().x - dead_zone_width) /2.0f),
        static_cast<float>((game_.getCurrentScene()->getCameraPos().y - dead_zone_height) / 2.0f),
        static_cast<float>(dead_zone_width),
        static_cast<float>(dead_zone_height)};

    SDL_FPoint position = {static_cast<float>(getPosition().x), static_cast<float>(getPosition().y)};
    if (SDL_PointInRectFloat(&position, &dead_zone))
    {
        return; // 玩家在死区内，不移动摄像机
    }

    float smoothing_factor = 1.3f; // 平滑因子，值越小越平滑
    auto target_camera_pos = position_ - game_.getScreenSize() / 2.0f;
    auto current_camera_pos = game_.getCurrentScene()->getCameraPos();
    auto new_camera_pos = current_camera_pos + (target_camera_pos - current_camera_pos) * smoothing_factor * dt; // 平滑移动摄像机

    game_.getCurrentScene()->setCameraPosition(new_camera_pos);
}

void Player::updateState()
{
    // 类似施密特触发器的状态检查和切换
    if (! sprite_move_->getFlip() && velocity_.x < -10.0f)
    {
        sprite_move_->setFlip(true);
        sprite_idle_->setFlip(true);
    }
    else if (sprite_move_->getFlip() && velocity_.x > 10.0f)
    {
        sprite_move_->setFlip(false);
        sprite_idle_->setFlip(false);
    }

    bool new_is_moving = (glm::length(velocity_) > 0.1f);
    if (new_is_moving != is_moving_)
    {
        is_moving_ = new_is_moving;
        changeState(is_moving_);
    }
}

void Player::changeState(bool is_moving)
{
    if (is_moving)
    {
        sprite_idle_->setActive(false);
        sprite_move_->setActive(true);
        sprite_move_->setCurrentFrame(sprite_idle_->getCurrentFrame());
        sprite_move_->setFrameTimer(sprite_idle_->getFrameTimer());
    }
    else
    {
        sprite_idle_->setActive(true);
        sprite_move_->setActive(false);
        sprite_idle_->setCurrentFrame(sprite_move_->getCurrentFrame());
        sprite_idle_->setFrameTimer(sprite_move_->getFrameTimer());
    }
}

void Player::updateDash(float dt)
{
    if (is_dashing_)
    {
        dash_timer_ -= dt;
        if (dash_timer_ < 0.0f)
        {
            is_dashing_ = false;
            dash_timer_ = 0.0f;
            setMaxSpeed(max_speed_ / 3.0f); // 恢复正常速度
        }
    }
    if (dash_cool_down > 0.0f)
    {
        dash_cool_down -= dt;
        if (dash_cool_down < 0.0f)
        {
            dash_cool_down = 0.0f;
        }
    }
}