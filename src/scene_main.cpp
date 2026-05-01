#include "scene_main.h"
#include "player.h"
#include "core/asset_store.h"

void SceneMain::init()
{
    world_size_ = game_.getScreenSize() * 3.0f; // 世界大小是屏幕大小的3倍
    camera_pos_ = glm::vec2(world_size_ / 2.0f);
    // camera_pos_ = glm::vec2(-100.0f);
    player_ = new Player();
    player_->init();
    player_->setPosition(world_size_ / 2.0f);

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
    player_->handleEvents(event);
}

void SceneMain::update(float dt)
{
    // auto camera_pos_ds = glm::vec2(100.0f, 100.0f); // 每秒向右下方移动10个单位
    //  camera_pos_ += glm::vec2(100.0f, 100.0f) * dt; // 每秒向右下方移动10个单位
    // updateCamera(dt, camera_pos_ + camera_pos_ds);
    player_->update(dt);
    updateCamera(dt);
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
    // 设置缩放因子
    setCameraZoom(camera_zoom_);
    SDL_SetRenderScale(game_.getRenderer(), camera_zoom_, camera_zoom_);
    renderBackground();
    player_->render();
}

void SceneMain::clean()
{
    player_->clean();
    delete player_;
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
