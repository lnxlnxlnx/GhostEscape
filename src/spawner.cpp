#include "spawner.h"
#include "player.h"
#include "enemy.h"
#include "core/scene.h"
#include "world/effect.h"

void Spawner::update(float dt)
{
    Object::update(dt);
    if (!target_ || !target_->isActive())
        return;
    timer_ += dt;
    if (timer_ >= interval_)
    {
        timer_ = 0;
        for (int i = 0; i < num_; ++i)
        {
            // spawn enemy
            auto pos = game_.randomVec2(game_.getCurrentScene()->getCameraPos(), game_.getCurrentScene()->getCameraPos() + game_.getScreenSize());
            Enemy* enemy = Enemy::addEnemyChild(nullptr, pos, target_);
            Effect::addEffectChild(game_.getCurrentScene(), "assets/effect/184_3.png", pos, 1.0f, enemy);
        }
    }
}
