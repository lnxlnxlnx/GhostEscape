#include "scene.h"
#include "object_world.h"

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

void Scene::addChild(Object *child)
{
    switch (child->getType())
    {
        case ObjectType::OBJECT_WORLD:
            children_world_.push_back(dynamic_cast<ObjectWorld *>(child));
            break;
        case ObjectType::OBJECT_SCREEN:
            children_screen_.push_back(dynamic_cast<ObjectScreen *>(child));
            break;
        default:
            children_.push_back(child);
            break;
    }
}

void Scene::removeChild(Object *child)
{
    switch (child->getType())
    {
        case ObjectType::OBJECT_WORLD:
            children_world_.erase(std::remove(children_world_.begin(), children_world_.end(), dynamic_cast<ObjectWorld *>(child)), children_world_.end());
            break;
        case ObjectType::OBJECT_SCREEN:
            children_screen_.erase(std::remove(children_screen_.begin(), children_screen_.end(), dynamic_cast<ObjectScreen *>(child)), children_screen_.end());
            break;
        default:
            children_.erase(std::remove(children_.begin(), children_.end(), child), children_.end());
            break;
    }
}

void Scene::init()
{
}

// scene.cpp
void Scene::handleEvents(SDL_Event &event)
{
    Object::handleEvents(event);
    for (auto &child : children_screen_)
    {
        child->handleEvents(event);
    }
    for (auto &child : children_world_)
    {
        child->handleEvents(event);
    }
}

void Scene::update(float dt)
{
    Object::update(dt);
    for (auto &child : children_world_)
    {
        if (child->isPaused() || !child->isActive()) continue;
        child->update(dt);
    }
    for (auto &child : children_screen_)
    {
        if (child->isPaused() || !child->isActive()) continue;
        child->update(dt);
    }
}

void Scene::render()
{
    Object::render();
    for (auto &child : children_world_)
    {
        if (!child->isActive()) continue;
        child->render();
    }
    for (auto &child : children_screen_)
    {
        if (!child->isActive()) continue;
        child->render();
    }
}

void Scene::clean()
{
    Object::clean();
    for (auto &child : children_world_)
    {
        child->clean();
    }
    children_world_.clear();
    for (auto &child : children_screen_)
    {
        child->clean();
    }
    children_screen_.clear();
}
