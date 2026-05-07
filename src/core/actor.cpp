#include "actor.h"
#include <glm/glm.hpp>
#include "scene.h"

void Actor::move(float dt)
{
    velocity_ = glm::clamp(velocity_, -max_speed_, max_speed_);
    setPosition(position_ + velocity_ * dt);
    position_ = glm::clamp(position_, glm::vec2(0), game_.getCurrentScene()->getWorldSize());
}

void Actor::takeDamage(float damage, const Stats *attacker)
{
    if (stats_ != nullptr && attacker != nullptr)
    {
        stats_->takeDamagePro(damage, attacker);
        return;
    }
    stats_->takeDamage(damage);
}

bool Actor::getIsAlive() const
{
    return stats_ != nullptr && stats_->getIsAlive();
}
