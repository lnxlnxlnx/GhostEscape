#include "physics_body.h"

void PhysicsBody::update(float dt)
{
    ObjectAffiliate::update(dt);
    tf_velocity_ += acceleration_ * dt;
    auto actor_parent_ = static_cast<Actor *>(parent_);
    if (actor_parent_)
    {
        auto new_velocity = tf_velocity_ * dt + actor_parent_->getVelocity();
        actor_parent_->setVelocity(new_velocity);
    }

    if (is_colliding_)
    {
        
    }
}

void PhysicsBody::applyForce(const glm::vec2 &force)
{
    if (isStatic)
        return;
    acceleration_ += force / mass;
}
