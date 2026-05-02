#include "object.h"

// object.cpp
void Object::handleEvents(SDL_Event& event) {
    for (auto& child : children_) {
        child->handleEvents(event);
    }
}

void Object::update(float dt) {
    for (auto it = children_.begin(); it != children_.end();) {
        auto child = *it;
        if (child->getNeedRemove()) {
            it = children_.erase(it);
            child->clean();
            delete child;
            continue;
        }
        ++it;
        if (!child->isActive()|| child->isPaused()) {
            continue;
        }
        child->update(dt);
    }
} 

void Object::render() {
    for (auto& child : children_) {
        if (child->isActive()) {
            child->render();
        }
    }
}   

void Object::clean() {
    for (auto& child : children_) {
        child->clean();
    }
    children_.clear();
}