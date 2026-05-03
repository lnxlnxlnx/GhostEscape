#include "actor.h"
#include <glm/glm.hpp>
#include "scene.h"

void Actor::move(float dt)
{
    setPosition(position_ + velocity_ * dt);
    position_ = glm::clamp(position_, glm::vec2(0), game_.getCurrentScene()->getWorldSize());
}

void Actor::takeDamage(float damage)
{
    if (stats_ != nullptr)
    {
        stats_->takeDamage(damage);
    }
}

bool Actor::isAlive() const
{
    return stats_ != nullptr && stats_->isAlive();
}
