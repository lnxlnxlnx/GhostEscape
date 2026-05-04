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
    bool is_paused_ = false;              // 是否暂停，暂停的对象不会被更新但会被渲染
    bool is_active_ = true;               // 是否活跃，活跃的对象会被更新和渲染
    bool need_remove_ = false;            // 是否需要被移除，标记为true的对象会在下一帧被从场景中移除并清理资源
    std::vector<Object *> object_to_add_; // 需要添加的对象，标记的对象会在下一帧被添加到场景中
    std::vector<Object *> children_;

public:
    Object() = default;
    virtual ~Object() = default; // 所有的类，不在构造函数和析构函数里面做任何事。

    virtual void init() { type_ = ObjectType::NONE; } // 需要初始化的事物，在init()函数里面做。
    virtual void handleEvents(SDL_Event &event);      // 需要处理事件的事物，在handleEvents()函数里面做。
    virtual void update(float dt);                    // 需要更新状态的事物，在update()函数里面做。
    virtual void render();
    virtual void clean(); // 需要清理的资源，在clean()函数里面做。

    // getters and setters
    ObjectType getType() const { return type_; }
    void setType(ObjectType type) { type_ = type; }
    bool isActive() const { return is_active_; }
    void setActive(bool active) { is_active_ = active; }
    bool isPaused() const { return is_paused_; }
    void setPaused(bool paused) { is_paused_ = paused; }

    void setNeedRemove(bool need_remove) { need_remove_ = need_remove; }

    bool getNeedRemove() const { return need_remove_; }

    // children
    void safeAddChild(Object *child) { object_to_add_.push_back(child); }
    virtual void addChild(Object *child) { children_.push_back(child); }
    virtual void removeChild(Object *child);
};

#endif /* B7525D5C_C16F_4123_814C_374AB4A1EEA3 */
