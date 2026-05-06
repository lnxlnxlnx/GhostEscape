#ifndef A8A185ED_E924_456F_A5CA_E4DF1F95705C
#define A8A185ED_E924_456F_A5CA_E4DF1F95705C
#include "core/scene.h"

class Player;
class Actor;
class Spawner;
class SceneMain: public Scene
{
    // 相机振动
    float shake_power_ = 5.0f;
    float shake_time_ = 1.0f;
    float shake_decay_ = 0.90f;

    // 玩家
    Player* player_ = nullptr; // 玩家
    // 敌人生成器
    Spawner* spawner_ = nullptr;


public:
    SceneMain() = default;
    virtual ~SceneMain() = default;

    virtual void init() override;
    virtual void handleEvents(SDL_Event& event) override;
    virtual void update(float dt) override;
    void updateCamera(float dt);
    void updateCameraShake(float dt);
    virtual void render() override;
    virtual void clean() override;

    // 工具函数
    void renderBackground();
    void cameraShake(float power, float duration);
    static void solveImpulse(Actor* other, Actor* player);

};

#endif /* A8A185ED_E924_456F_A5CA_E4DF1F95705C */
