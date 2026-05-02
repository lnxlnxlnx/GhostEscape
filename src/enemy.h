#ifndef D5647D5C_C342_48F8_A32B_722D34A9B313
#define D5647D5C_C342_48F8_A32B_722D34A9B313
// enemy.h
#ifndef ENEMY_H
#define ENEMY_H
#include "core/actor.h"


class Player;
class Enemy : public Actor
{
    Player* target_ = nullptr;

public:
    virtual void init();
    virtual void update(float dt) override;  // override the update function from Actor

    void aim_target(Player* target);

    // getters and setters
    Player* get_target() { return target_; }
    void set_target(Player* target) { target_ = target; }
};

#endif // ENEMY_H

#endif /* D5647D5C_C342_48F8_A32B_722D34A9B313 */
