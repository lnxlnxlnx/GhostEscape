#ifndef D5647D5C_C342_48F8_A32B_722D34A9B313
#define D5647D5C_C342_48F8_A32B_722D34A9B313
// enemy.h
#ifndef ENEMY_H
#define ENEMY_H
#include "core/actor.h"

class Player;
class Enemy : public Actor
{
    enum class State
    {
        NORMAL,
        HURT,
        DIE
    };

    // 精灵动画
    SpriteAnim *anim_normal_ = nullptr;
    SpriteAnim *anim_hurt_ = nullptr;
    SpriteAnim *anim_die_ = nullptr;

    SpriteAnim *current_anim_ = nullptr;

    // 状态相关
    float timer_ = 0.0f; // 用于演示状态切换的计时器
    State current_state_ = State::NORMAL;
    Player *target_ = nullptr;

public:
    virtual void init();
    virtual void update(float dt) override; // override the update function from Actor

    // 行为函数
    void aim_target(Player *target);

    void changeState(State new_state);

    void updateState(float dt);

    // getters and setters
    Player *get_target() { return target_; }
    void set_target(Player *target) { target_ = target; }
};

#endif // ENEMY_H

#endif /* D5647D5C_C342_48F8_A32B_722D34A9B313 */
