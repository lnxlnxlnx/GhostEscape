#ifndef A8380280_8934_47CD_A1D2_F957AA645C23
#define A8380280_8934_47CD_A1D2_F957AA645C23
#include <glm/glm.hpp>
#include "object.h"
#include <vector>

class Scene : public Object {
protected:
    glm::vec2 camera_pos_ = glm::vec2(0);
    std::vector<Object*> objects_;

public:
    Scene() = default;
    virtual ~Scene() = default;

    virtual void init() override {}
    virtual void handleEvents(SDL_Event& event) override {}
    virtual void update(float dt) override {}
    virtual void render() override {}
    virtual void clean() override {}
};

#endif /* A8380280_8934_47CD_A1D2_F957AA645C23 */
