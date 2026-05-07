#include "effect.h"
#include "../core/scene.h"

Effect *Effect::addEffectChild(Object* parent, const std::string &file_path, glm::vec2 pos, float scale, ObjectWorld *next_object)
{
    auto effect = new Effect();
    effect->init();
    effect->sprite_ = SpriteAnim::addSpriteAnimChild(effect, file_path, scale);
    effect->sprite_->setPlayMode(SpriteAnimPlayMode::PLAY_ONCE);
    effect->setPosition(pos);
    effect->setNextObject(next_object);
    if (parent) parent->addChild(effect);
    return effect;
}

void Effect::update(float dt)
{
    ObjectWorld::update(dt);
    checkFinish();
}

void Effect::clean()
{
    ObjectWorld::clean();
    if (next_object_){      // 如果next_object_已经添加到场景中，就不应该再去删除
        next_object_->clean();
        delete next_object_;
        next_object_ = nullptr;
    }
}

void Effect::checkFinish()
{
    if (sprite_->isFinished())
    {
        need_remove_ = true;
        if (next_object_){
            game_.getCurrentScene()->safeAddChild(next_object_);
            next_object_ = nullptr;     //不能重复添加，所以添加完了就置空
        }
    }
}