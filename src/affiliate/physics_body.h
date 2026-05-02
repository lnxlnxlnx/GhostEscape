#ifndef ECC3D75E_4E7E_45C1_A7E6_09B3C095D497
#define ECC3D75E_4E7E_45C1_A7E6_09B3C095D497
//#include <glm/glm.hpp>
#include "../core/object_affiliate.h"
#include "collider.h"
#include "../core/actor.h"

class PhysicsBody :public ObjectAffiliate{
    glm::vec2 position_;
    glm::vec2 tf_velocity_;
    glm::vec2 acceleration_;
    glm::vec2 other_position_; // 用于存储碰撞时另一个物体的位置，TODO: 可以改成一个碰撞信息结构体，包含碰撞点、碰撞法线等信息
    Collider *collider_ = nullptr;
    bool is_colliding_ = false;

    float mass = 1.0f; // 质量为0表示静态物体（不可推动）
    bool isStatic = false; // 是否为静态物体
public:
    PhysicsBody() = default;
    virtual void init() override;
    virtual void update(float dt) override;

    // 工具函数
    void applyForce(const glm::vec2 &force);

    void applyImpulse(const glm::vec2 &impulse);

    // getters and setters
    void setCollider(Collider *collider) { collider_ = collider; }
    Collider *getCollider() const { return collider_; }
    void setStatic(bool is_static) { isStatic = is_static; }
    bool getStatic() const { return isStatic; }
    void setMass(float mass) { this->mass = mass; }
    float getMass() const { return mass; }

};

#endif /* ECC3D75E_4E7E_45C1_A7E6_09B3C095D497 */
