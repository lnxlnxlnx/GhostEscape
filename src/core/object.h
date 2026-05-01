#ifndef B7525D5C_C16F_4123_814C_374AB4A1EEA3
#define B7525D5C_C16F_4123_814C_374AB4A1EEA3
#include "game.h"
#include "defs.h"
#include <spdlog/spdlog.h>
#include <vector>

class Object
{
protected:
    Game &game_ = Game::GetInstance();
    ObjectType type_ = ObjectType::NONE;

    std::vector<Object *> children_;

public:
    Object() = default;
    virtual ~Object() = default; // 所有的类，不在构造函数和析构函数里面做任何事。

    virtual void init() { type_ = ObjectType::NONE; }            // 需要初始化的事物，在init()函数里面做。
    virtual void handleEvents(SDL_Event &event); // 需要处理事件的事物，在handleEvents()函数里面做。
    virtual void update(float dt);                  // 需要更新状态的事物，在update()函数里面做。
    virtual void render();
    virtual void clean(); // 需要清理的资源，在clean()函数里面做。

    // getters and stters
    ObjectType getType() const { return type_; }
    void setType(ObjectType type) { type_ = type; }

    // children
    virtual void addChild(Object *child) { children_.push_back(child); }
    virtual void removeChild(Object *child)
    {
        children_.erase(std::remove(children_.begin(), children_.end(), child), children_.end());
    }
};

#endif /* B7525D5C_C16F_4123_814C_374AB4A1EEA3 */
