#include "scene_main.h"

void SceneMain::init()
{
    world_size_ = game_.getScreenSize() * 3.0f; // 世界大小是屏幕大小的3倍
    camera_pos_ = glm::vec2(world_size_ / 2.0f);
    // camera_pos_ = glm::vec2(-100.0f);
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
        case SDLK_W:
        {
            auto camera_zoom = camera_zoom_ + 0.01f;
            setCameraZoom(camera_zoom);
            SDL_Log("Zoom: %f", camera_zoom_);
            break;
        }
        case SDLK_E:
        {
            auto camera_zoom = camera_zoom_ - 0.01f;
            setCameraZoom(camera_zoom);
            SDL_Log("Zoom: %f", camera_zoom_);
            break;
        }
        default:
            break;
        }
    }
}

void SceneMain::update(float dt)
{
    auto camera_pos_ds = glm::vec2(100.0f, 100.0f); // 每秒向右下方移动10个单位
    // camera_pos_ += glm::vec2(100.0f, 100.0f) * dt; // 每秒向右下方移动10个单位
    updateCamera(dt, camera_pos_ + camera_pos_ds);
}

void SceneMain::updateCamera(float dt, glm::vec2 target_pos)
{
    float smoothing_factor = 3.0f;                                     // 平滑因子，值越小越平滑
    camera_pos_ += (target_pos - camera_pos_) * smoothing_factor * dt; // 平滑移动摄像机
    // 限制摄像机在世界范围内
    camera_pos_ = glm::clamp(camera_pos_, glm::vec2(0), world_size_ - game_.getScreenSize());
}

void SceneMain::render()
{
    // 设置缩放因子
    setCameraZoom(camera_zoom_);
    SDL_SetRenderScale(game_.getRenderer(), camera_zoom_, camera_zoom_);
    renderBackground();
}

void SceneMain::clean()
{
}

void SceneMain::renderBackground()
{
    auto start = -camera_pos_;
    auto end = world_size_ - camera_pos_;
    game_.drawGrid(start, end, 80.0f, {0.5, 0.5, 0.5, 1.0});
    game_.drawBoundary(start, end, 5.0f, {0.5, 0.5, 0.5, 1.0});
}
