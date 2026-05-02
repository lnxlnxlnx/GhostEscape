#ifndef D959CD80_0972_449D_9794_1160CAB7DC34
#define D959CD80_0972_449D_9794_1160CAB7DC34
// collider.h
#ifndef COLLIDER_H
#define COLLIDER_H

#include "../core/object_affiliate.h"

class Collider : public ObjectAffiliate
{
public:
    enum class Type{
        CIRCLE,         // size_ 的 x 轴为直径, 默认 y=x;
        RECTANGLE
    };
protected:
    Type type_ = Type::CIRCLE;

public:
    virtual void render() override;
    
    static Collider* addColliderChild(ObjectScreen* parent, glm::vec2 size, Type type = Type::CIRCLE);
    bool isColliding(Collider* other);

    // getters and setters
    Type type() const { return type_; }
    void setType(Type type) { type_ = type; }
};

#endif // COLLIDER_H
#endif /* D959CD80_0972_449D_9794_1160CAB7DC34 */
