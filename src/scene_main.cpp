#include "scene_main.h"

void SceneMain::init()
{
    world_size_ = game_.getScreenSize() * 3.0f; // 世界大小是屏幕大小的3倍
    camera_pos_ = glm::vec2(world_size_ / 2.0f);
    //camera_pos_ = glm::vec2(-100.0f);
}

void SceneMain::handleEvents(SDL_Event& event)
{
}

void SceneMain::update(float dt)
{
camera_pos_ += glm::vec2(100.0f, 100.0f) * dt; // 每秒向右下方移动10个单位
}

void SceneMain::render()
{
    renderBackground();
}

void SceneMain::clean()
{
}

void SceneMain::renderBackground()
{
    auto start = - camera_pos_;
    auto end = world_size_ - camera_pos_;
    game_.drawGrid(start, end, 80.0f, {0.5, 0.5, 0.5, 1.0});
    game_.drawBoundary(start, end, 5.0f, {0.5, 0.5, 0.5, 1.0});
}
