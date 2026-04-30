// player.cpp
#include "player.h"
#include "core/scene.h"

void Player::init()
{
    max_speed_ = 500.0f;
}

void Player::handleEvents(SDL_Event& event)
{
}

void Player::update(float dt)
{
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
    game_.drawBoundary(render_position_, render_position_ + glm::vec2(20.0f), 5.0f, {1.0, 0.0, 0.0, 1.0});
}

void Player::clean()
{
}

void Player::keyboardControl()
{
    auto currentKeyStates = SDL_GetKeyboardState(NULL);
    auto temp_velocity = glm::vec2(velocity_.x, velocity_.y);
    if (currentKeyStates[SDL_SCANCODE_W]){
        temp_velocity.y = -max_speed_;
    }
    if (currentKeyStates[SDL_SCANCODE_S]){
        temp_velocity.y = max_speed_;
    }
    if (currentKeyStates[SDL_SCANCODE_A]){
        temp_velocity.x = -max_speed_;
    }
    if (currentKeyStates[SDL_SCANCODE_D]){
        temp_velocity.x = max_speed_;
    }
    if (currentKeyStates[SDL_SCANCODE_LSHIFT] && !is_dashing_){
        is_dashing_ = true;
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
    //game_.getCurrentScene()->setCameraPosition(position_ - game_.getScreenSize() / 2.0f);
    float smoothing_factor = 3.0f;                                     // 平滑因子，值越小越平滑
    auto target_camera_pos = position_ - game_.getScreenSize() / 2.0f;
    auto current_camera_pos = game_.getCurrentScene()->getCameraPos();
    auto new_camera_pos = current_camera_pos + (target_camera_pos - current_camera_pos) * smoothing_factor * dt; // 平滑移动摄像机

    game_.getCurrentScene()->setCameraPosition(new_camera_pos);
}

void Player::updateDash(float dt)
{
    if (is_dashing_) {
        dash_timer_ -= dt;
        if (dash_timer_ < 0.0f) {
            is_dashing_ = false;
            dash_timer_ = 0.0f;
            setMaxSpeed(max_speed_ / 3.0f); // 恢复正常速度
        }
    }
}