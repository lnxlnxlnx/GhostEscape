#include "actor.h"
#include <glm/glm.hpp>
#include "scene.h"

void Actor::move(float dt)
{
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

bool Actor::isAlive() const
{
    return stats_ != nullptr && stats_->isAlive();
}
