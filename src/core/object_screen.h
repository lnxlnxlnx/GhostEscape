#ifndef D4B9B240_CDE4_4096_BE94_40B9F344BFA8
#define D4B9B240_CDE4_4096_BE94_40B9F344BFA8
// object_screen.h
#ifndef OBJECT_SCREEN_H
#define OBJECT_SCREEN_H

#include "object.h"

class ObjectScreen : public Object
{
protected:
    glm::vec2 render_position_ = glm::vec2(0, 0); // 渲染(屏幕)位置

public:
    // getters and stters
    glm::vec2 getRenderPosition() const { return render_position_; }
    virtual void setRenderPosition(const glm::vec2 &render_position) { render_position_ = render_position; }
    virtual void init() override{ type_ = ObjectType::OBJECT_SCREEN; }
};

#endif // OBJECT_SCREEN_H

#endif /* D4B9B240_CDE4_4096_BE94_40B9F344BFA8 */
