// player.cpp
#include "player.h"
#include "core/scene.h"
#include "core/asset_store.h"

void Player::init()
{
    Actor::init();
    max_speed_ = 500.0f;

    // 加载玩家纹理
    // 方法1：预先加载
    game_.getAssetStore()->loadImage("assets/test/hp.png");

    // 方法2：直接获取（如果不存在会自动加载）
    // SDL_Texture *playerTexture = game_.getAssetStore()->getImage("assets/test/yuki.jpg");
}

void Player::handleEvents(SDL_Event &event)
{
    Actor::handleEvents(event);
}

void Player::update(float dt)
{
    Actor::update(dt);
    keyboardControl();
    velocity_ *= 0.9f;
    // if (glm::length(velocity_) < 0.1f) {
    //     velocity_ = glm::vec2(0, 0);
    // }
    move(dt);
    syncCamera(dt);
    updateDash(dt);
}

void Player::render()
{
    Actor::render();
    auto assetStore = game_.getAssetStore();
    SDL_Texture *playerTexture = assetStore->getImage(game_.getConfig()->get<std::string>("player.texture4", "assets/test/hp.png"));

    // 创建源和目标矩形
    float w, h;
    SDL_GetTextureSize(playerTexture, &w, &h);
    SDL_FRect srcRect = {0, 0, w, h}; // 假设精灵表中的第一帧
    if (w > 200.0f)
    {
        w = w / 4.0f;       //TODO: 这里是为了测试，之后应该设计一个自动调整大小的函数
        h = h / 4.0f;
    }
    SDL_FRect destRect = {render_position_.x, render_position_.y, w, h};

    // 渲染纹理
    if (playerTexture)
    {
        SDL_RenderTexture(game_.getRenderer(), playerTexture, &srcRect, &destRect);
    }
    else
    {
        // 如果纹理加载失败，使用备用的渲染方法
        game_.drawBoundary(render_position_, render_position_ + glm::vec2(20.0f), 5.0f, {1.0, 0.0, 0.0, 1.0});
    }
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
    SDL_Log("dt: %f, position: (%f, %f), velocity: (%f, %f)", dt, position_.x, position_.y, velocity_.x, velocity_.y);
    position_ = glm::clamp(position_, glm::vec2(0), game_.getCurrentScene()->getWorldSize());
}

void Player::syncCamera(float dt)
{
    // game_.getCurrentScene()->setCameraPosition(position_ - game_.getScreenSize() / 2.0f);
    float dead_zone_percentage = 0.5f;
    float dead_zone_width = game_.getScreenSize().x * dead_zone_percentage;
    float dead_zone_height = game_.getScreenSize().y * dead_zone_percentage;
    SDL_FRect dead_zone = {
        static_cast<float>(game_.getCurrentScene()->getCameraPos().x + dead_zone_width / 2.0f),
        static_cast<float>(game_.getCurrentScene()->getCameraPos().y + dead_zone_height / 2.0f),
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