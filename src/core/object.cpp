#include "object.h"

// object.cpp
void Object::handleEvents(SDL_Event &event)
{
    for (auto &child : children_)
    {
        child->handleEvents(event);
    }
}

void Object::update(float dt)
{
    for (auto &child : object_to_add_)
    {
        addChild(child);
        // child = nullptr;
    }
    object_to_add_.clear();
    
    for (auto it = children_.begin(); it != children_.end();)
    {
        auto child = *it;
        if (child->getNeedRemove())
        {
            it = children_.erase(it);
            child->clean();
            delete child;
            child = nullptr;
            continue;
        }
        ++it;
        if (!child->isActive() || child->isPaused())
        {
            continue;
        }
        child->update(dt);
    }
}

void Object::render()
{
    for (auto &child : children_)
    {
        if (child->isActive())
        {
            child->render();
        }
    }
}

void Object::clean()
{
    for (auto &child : children_)
    {
        child->clean();
    }
    children_.clear();
}

void Object::safeAddChild(Object *child)
{
    if (child == nullptr)
        return;
    spdlog::debug("safeAddChild: {}", static_cast<int>(child->getType()));
    object_to_add_.push_back(child);
}

void Object::removeChild(Object *child)
{
    children_.erase(std::remove(children_.begin(), children_.end(), child), children_.end());
}
