#ifndef A8A185ED_E924_456F_A5CA_E4DF1F95705C
#define A8A185ED_E924_456F_A5CA_E4DF1F95705C
#include "core/scene.h"

class SceneMain: public Scene
{
    glm::vec2 world_size_ = glm::vec2(0); // 世界大小

public:
    SceneMain() = default;
    virtual ~SceneMain() = default;

    virtual void init() override;
    virtual void handleEvents(SDL_Event& event) override;
    virtual void update(float dt) override;
    virtual void render() override;
    virtual void clean() override;

    void renderBackground();
};

#endif /* A8A185ED_E924_456F_A5CA_E4DF1F95705C */
