#ifndef B7525D5C_C16F_4123_814C_374AB4A1EEA3
#define B7525D5C_C16F_4123_814C_374AB4A1EEA3
#include "game.h"

class Object {
protected:
    Game& game_ = Game::GetInstance();
public:
    Object() = default;
    virtual ~Object() = default;    // 所有的类，不在构造函数和析构函数里面做任何事。

    virtual void init() {}      // 需要初始化的事物，在init()函数里面做。
    virtual void handleEvents(SDL_Event& event) {(void)event;}  // 需要处理事件的事物，在handleEvents()函数里面做。
    virtual void update(float dt) {(void) dt;}  // 需要更新状态的事物，在update()函数里面做。
    virtual void render() {}
    virtual void clean() {}     // 需要清理的资源，在clean()函数里面做。
};

#endif /* B7525D5C_C16F_4123_814C_374AB4A1EEA3 */
