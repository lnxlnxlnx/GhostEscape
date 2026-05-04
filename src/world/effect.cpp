#include "effect.h"
#include "../affiliate/sprite_anim.h"
#include "../core/scene.h"

Effect *Effect::addEffectChild(Object *parent, const std::string &file_path, glm::vec2 pos, float scale, ObjectWorld *next_object)
{
    Effect *effect = new Effect();
    effect->init();     // 初始化类型为OBJECT_WORLD
    auto sprite = SpriteAnim::addSpriteAnimChild(effect, file_path, scale);
    sprite->setPlayMode(SpriteAnimPlayMode::PLAY_ONCE);
    effect->setSpriteAnim(sprite);
    effect->setPosition(pos);
    effect->setNextObject(next_object);
    if (parent != nullptr)
    {
        parent->addChild(effect);
    }
    return effect;
}

void Effect::update(float dt)
{
    ObjectWorld::update(dt);
    checkFinish();
}


void Effect::checkFinish()
{
    if (sprite_->isFinished())
    {
        need_remove_ = true;
        is_active_ = false;
        if (next_object_){
            game_.getCurrentScene()->safeAddChild(next_object_);
            spdlog::info("Effect::checkFinish()");
        }
    }
}

