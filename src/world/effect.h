#ifndef CDD51147_FF71_4301_96FE_5DD91901CF9D
#define CDD51147_FF71_4301_96FE_5DD91901CF9D
// effect.h
#ifndef EFFECT_H
#define EFFECT_H

#include "../core/object_world.h"
#include "../affiliate/sprite_anim.h"
#include <string>

class Effect : public ObjectWorld
{
    SpriteAnim* sprite_ = nullptr;
    ObjectWorld* next_object_ = nullptr;        // 播放完毕后添加到场景中。

public:
    static Effect* addEffectChild(Object* parent, const std::string& file_path,glm::vec2 pos, float scale = 1.0f, ObjectWorld* next_object = nullptr);
    virtual void update(float dt) override;

    // setters and getters
    void setSpriteAnim(SpriteAnim* sprite) { sprite_ = sprite; }
    SpriteAnim* getSpriteAnim() { return sprite_; }
    void setNextObject(ObjectWorld* next_object) { next_object_ = next_object; }
    ObjectWorld* getNextObject() { return next_object_; }

    virtual void clean() override;

private:
    void checkFinish();
};

#endif // EFFECT_H

#endif /* CDD51147_FF71_4301_96FE_5DD91901CF9D */
