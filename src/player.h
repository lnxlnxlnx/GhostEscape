#ifndef D671D27C_F2D8_49A4_B225_EA5C33173138
#define D671D27C_F2D8_49A4_B225_EA5C33173138
// player.h
#ifndef PLAYER_H
#define PLAYER_H

#include "core/actor.h"

class SpriteAnim;
class Collider;
class Effect;
class Player : public Actor
{

    // 冲刺相关
    bool is_dashing_ = false;
    float dash_timer_ = 0.0f;
    float dash_duration_ = 0.2f;
    float dash_cool_down = 0.0f;

    // 精灵动画     //TODO: 可以改成std::map<std::string, SpriteAnim*>，用状态名来索引不同的动画，或者用一个current_sprite指针来指向当前的动画
    SpriteAnim *sprite_idle_ = nullptr;
    SpriteAnim *sprite_move_ = nullptr;
    bool is_moving_ = false;

    // 碰撞体
    Collider *collider_ = nullptr;

    // 特效
    Effect *effect_ = nullptr;

public:
    virtual void init() override;
    virtual void handleEvents(SDL_Event &event) override;
    virtual void update(float dt) override;
    virtual void render() override;
    virtual void clean() override;

    // 移动和视角相关
    void keyboardControl();
    void move(float dt) override;
    void syncCamera(float dt);

    // 状态检查和切换
    void updateState();
    void changeState(bool is_moving);

    // 功能函数
    void updateDash(float dt);
    void checkIsDead();

    // getters and setters
    Collider *getCollider() const { return collider_; }
    void setCollider(Collider *collider) { collider_ = collider; }

};

#endif // PLAYER_H

#endif /* D671D27C_F2D8_49A4_B225_EA5C33173138 */
