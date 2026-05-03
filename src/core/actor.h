#ifndef B06B7680_4628_4D5A_A71F_40980C03F748
#define B06B7680_4628_4D5A_A71F_40980C03F748
// actor.h
#ifndef ACTOR_H
#define ACTOR_H

#include "object_world.h"
#include "../raw/sats.h"
class Stats;
class Actor : public ObjectWorld
{
protected:
    Stats *stats_ = nullptr;

    glm::vec2 velocity_ = glm::vec2(0, 0); // 速度
    float max_speed_ = 100.0f;             // 最大速度大小
    float mass_ = 1000.0f;                 // 质量，TODO: 可以改成一个属性结构体，包含质量、速度、加速度等物理属性
    float acceleration_ = 0.0f;

public:
    virtual void move(float dt);
    void takeDamage(float damage);
    bool isAlive() const;
    // getters and setters
    glm::vec2 getVelocity() const { return velocity_; }
    void setVelocity(const glm::vec2 &velocity) { velocity_ = velocity; }
    float getMaxSpeed() const { return max_speed_; }
    void setMaxSpeed(float max_speed) { max_speed_ = max_speed; }
    float getMass() const { return mass_; }
    void setMass(float mass) { mass_ = mass; }
    float getAcceleration() const { return acceleration_; }
    void setAcceleration(float acceleration) { acceleration_ = acceleration; }
    Stats *getStats() const { return stats_; }
    void setStats(Stats *stats) { stats_ = stats; }
};

#endif // ACTOR_H

#endif /* B06B7680_4628_4D5A_A71F_40980C03F748 */
