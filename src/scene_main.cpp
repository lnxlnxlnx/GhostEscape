#include "scene_main.h"
#include "player.h"
#include "core/asset_store.h"
#include "enemy.h"
#include "core/actor.h" // Ensure the Actor class is included

void SceneMain::init()
{
    world_size_ = game_.getScreenSize() * 3.0f; // 世界大小是屏幕大小的3倍
    camera_pos_ = glm::vec2(world_size_ / 2.0f);

    // 创建玩家
    player_ = new Player();
    player_->init();
    player_->setPosition(world_size_ / 2.0f);
    addChild(player_);

    // 创建敌人
    auto enemy = new Enemy();
    enemy->init();
    enemy->set_target(player_);
    enemy->setPosition(world_size_ / 2.0f + glm::vec2(200.0f));
    addChild(enemy);

    // 加载背景音乐
    game_.getAssetStore()->loadMusic(game_.getConfig()->get<std::string>("background_music"));

    // 播放背景音乐（循环）
    Mix_Music *backgroundMusic = game_.getAssetStore()->getMusic(game_.getConfig()->get<std::string>("background_music"));
    if (backgroundMusic)
    {
        Mix_PlayMusic(backgroundMusic, -1); // -1表示无限循环
    }
}

void SceneMain::handleEvents(SDL_Event &event)
{
    Scene::handleEvents(event);
    switch (event.type)
    {
    case SDL_EVENT_MOUSE_WHEEL:
        setCameraZoom(camera_zoom_ + event.wheel.y * 0.05f);
        SDL_Log("Zoom: %f", camera_zoom_);
        break;
    case SDL_EVENT_KEY_DOWN:
        switch (event.key.key)
        {
        case SDLK_SPACE:
            cameraShake(10.0f, 1.0f);
            break;
        default:
            break;
        }
    }
}

/*brief://NOTE: 这里的dt是从Game传过来的，已经经过了帧率控制，单位是秒*/
void SceneMain::update(float dt)
{
    Scene::update(dt);
    // auto camera_pos_ds = glm::vec2(100.0f, 100.0f); // 每秒向右下方移动10个单位
    //  camera_pos_ += glm::vec2(100.0f, 100.0f) * dt; // 每秒向右下方移动10个单位
    // updateCamera(dt, camera_pos_ + camera_pos_ds);
    updateCamera(dt);
    static float time_accumulator = 0.0f;
    time_accumulator += dt;
    if (time_accumulator >= 3.0f)
    {
        cameraShake(10.0f, 1.0f);
        time_accumulator = 0.0f;
        // player_->setPaused(!player_->isPaused()); // 每5秒切换玩家的活跃状态
        // spdlog::info("Player active: {}", player_->isActive());
        // spdlog::info("Player paused: {}", player_->isPaused());
    }
}

void SceneMain::updateCamera(float dt)
{
    // 限制摄像机在世界范围内
    camera_pos_ = glm::clamp(camera_pos_, glm::vec2(0), world_size_ - game_.getScreenSize());
    if (shake_time_ > 0.0f)
    {
        updateCameraShake(dt);
    }
}

void SceneMain::updateCameraShake(float dt)
{
    shake_time_ -= dt;
    float shake_offset_x = (rand() / (float)RAND_MAX - 0.5f) * 2.0f * shake_power_;
    float shake_offset_y = (rand() / (float)RAND_MAX - 0.5f) * 2.0f * shake_power_;
    camera_pos_ += glm::vec2(shake_offset_x, shake_offset_y);
    shake_power_ *= shake_decay_; // 振动衰减
    if (shake_power_ < 0.1f)
    {
        shake_time_ = 0.0f;
    }
}
void SceneMain::render()
{
    renderBackground();
    Scene::render();
    // 设置缩放因子
    setCameraZoom(camera_zoom_);
    SDL_SetRenderScale(game_.getRenderer(), camera_zoom_, camera_zoom_);
}

void SceneMain::clean()
{
    Scene::clean();
}

void SceneMain::renderBackground()
{
    auto start = -camera_pos_;
    auto end = world_size_ - camera_pos_;
    game_.drawGrid(start, end, 80.0f, {0.5, 0.5, 0.5, 1.0});
    game_.drawBoundary(start, end, 5.0f, {0.5, 0.5, 0.5, 1.0});
}

void SceneMain::cameraShake(float power, float duration)
{
    shake_power_ = power;
    shake_time_ = duration;
}

void SceneMain::solveImpulse(Actor *other, Actor *player)
{
    auto normal_line = other->getPosition() - player->getPosition();
    normal_line = glm::normalize(normal_line);
    auto player_velocity = glm::dot(player->getVelocity(), normal_line);
    auto other_velocity = glm::dot(other->getVelocity(), normal_line);
    auto player_mass = player->getMass();
    auto other_mass = other->getMass();
    auto new_player_velocity_dv = ((player_mass - other_mass) * player_velocity + 2.0f * other_mass * other_velocity) / (player_mass + other_mass) ;
    auto new_other_velocity_dv = ((other_mass - player_mass) * other_velocity + 2.0f * player_mass * player_velocity) / (player_mass + other_mass) ;

    auto new_player_velocity = player->getVelocity() + (new_player_velocity_dv - player_velocity) * normal_line;
    auto new_other_velocity = other->getVelocity() + (new_other_velocity_dv - other_velocity) * normal_line;
    player->setVelocity(new_player_velocity);
    other->setVelocity(new_other_velocity);
}
