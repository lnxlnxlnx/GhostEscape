#ifndef COLLIDER_H
#define COLLIDER_H

#include "../core/object_affiliate.h"

class Spell;
class Collider : public ObjectAffiliate
{
protected:
    //  友元        
    /* 
    如果在类 A 中声明friend Spell;，则Spell类的所有成员函数都可以直接访问类 A 的私有成员和保护成员，就像这些成员是Spell类自己的成员一样。
    */
    friend Spell;
    enum class Type{
        CIRCLE,         // size_ 的 x 轴为直径, 默认 y=x;
        RECTANGLE
    };
    Type collider_type_ = Type::CIRCLE;

public:
    virtual void render() override;
    
    static Collider* addColliderChild(ObjectScreen* parent, glm::vec2 size, Type collider_type = Type::CIRCLE, Anchor anchor = Anchor::CENTER);
    bool isColliding(Collider* other);

    // getters and setters
    Type getColliderType() const { return collider_type_; }
    void setColliderType(Type collider_type) { collider_type_ = collider_type; }
};







#endif // COLLIDER_H