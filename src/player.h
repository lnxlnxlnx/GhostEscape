#ifndef D671D27C_F2D8_49A4_B225_EA5C33173138
#define D671D27C_F2D8_49A4_B225_EA5C33173138
// player.h
#ifndef PLAYER_H
#define PLAYER_H

#include "core/actor.h"

class Player : public Actor
{

    bool is_dashing_ = false;
    float dash_timer_ = 0.0f;
    float dash_duration_ = 0.2f;

public:
    virtual void init() override;
    virtual void handleEvents(SDL_Event &event) override;
    virtual void update(float dt) override;
    virtual void render() override;
    virtual void clean() override;

    void keyboardControl();
    void move(float dt);
    void syncCamera(float dt);

    // 功能函数
    void updateDash(float dt);
};

#endif // PLAYER_H

#endif /* D671D27C_F2D8_49A4_B225_EA5C33173138 */
