#include "spawner.h"
#include "enemy.h"
#include "world/effect.h"
#include "core/scene.h"

void Spawner::update(float dt)
{
    if (!target_ || !target_->getActive()) return;
    timer_ += dt;
    if (timer_ >= interval_)
    {
        timer_ = 0;
        game_.playSound("assets/sound/silly-ghost-sound-242342.mp3");
        for (int i = 0; i < num_; i++)
        {
            // spawn enemy
            //使用生成器可以持续地创建敌人，使游戏更具挑战性。
            auto pos = game_.randomVec2(game_.getCurrentScene()->getCameraPosition(), game_.getCurrentScene()->getCameraPosition() + game_.getScreenSize());
            Enemy* enemy = Enemy::addEnemyChild(nullptr, pos, target_);
            Effect::addEffectChild(game_.getCurrentScene(), "assets/effect/184_3.png", pos, 1.0f, enemy);
        }
    }
}
