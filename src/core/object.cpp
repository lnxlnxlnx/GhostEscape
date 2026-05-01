#include "object.h"

// object.cpp
void Object::handleEvents(SDL_Event& event) {
    for (auto& child : children_) {
        child->handleEvents(event);
    }
}

void Object::update(float dt) {
    for (auto& child : children_) {
        child->update(dt);
    }
} 

void Object::render() {
    for (auto& child : children_) {
        child->render();
    }
}

void Object::clean() {
    for (auto& child : children_) {
        child->clean();
    }
    children_.clear();
}