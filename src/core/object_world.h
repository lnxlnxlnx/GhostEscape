#ifndef A2237F9C_F86B_4423_BA03_34AE516113AC
#define A2237F9C_F86B_4423_BA03_34AE516113AC
// object_world.h
#ifndef OBJECT_WORLD_H
#define OBJECT_WORLD_H

#include "object_screen.h"

class ObjectWorld : public ObjectScreen
{
protected:
    glm::vec2 position_ = glm::vec2(0, 0); // 世界位置

public:
    virtual void update(float dt) override;
    // getters and stters
    glm::vec2 getPosition() const { return position_; }
    void setPosition(const glm::vec2 &position);
    virtual void setRenderPosition(const glm::vec2 &render_position) override;
};

#endif // OBJECT_WORLD_H

#endif /* A2237F9C_F86B_4423_BA03_34AE516113AC */
