#include "scene.h"

void Scene::setCameraZoom(float zoom)
{
    camera_zoom_ = zoom;
    // 限制缩放范围
    camera_zoom_ = glm::clamp(camera_zoom_, 0.5f, 3.0f);
}

void Scene::setCameraPosition(const glm::vec2 &pos)
{
    camera_pos_ = pos;
    // 限制摄像机在世界范围内
    camera_pos_ = glm::clamp(camera_pos_, glm::vec2(0), world_size_ - game_.getScreenSize() / camera_zoom_); // NOTE: / camera_zoom_ 是为了考虑缩放后的屏幕大小
}