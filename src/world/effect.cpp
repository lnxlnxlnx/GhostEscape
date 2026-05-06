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
    if (next_object == nullptr)
    {
        spdlog::info("Effect::addEffectChild() no next_object");
    }
    else
    {
        effect->setNextObject(next_object);
    }
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
        //is_active_ = false;
        // sprite_->setFinished(false); // 重置动画状态，以防再次进入这个函数
        if (next_object_){
            game_.getCurrentScene()->safeAddChild(next_object_);
            spdlog::info("Effect::checkFinish()");
        }
    }
}

