#include "player.h"
#include "enemy.h"
#include "affiliate/sprite_anim.h"
#include "core/config_manager.h"

void Enemy::init()
{
    Actor::init();
    auto path = game_.getConfig()->get<std::string>("enemy.sprite_dead", "assets/sprite/ghostDead-Sheet.png");
    SpriteAnim::addSpriteAnimChild(this, "assets/sprite/ghost-Sheet.png", 2.0f);
}

void Enemy::update(float dt){
    Actor::update(dt);
    aim_target(target_);
    move(dt);
}

void Enemy::aim_target(Player *target)
{
    if (target == nullptr) return;
    auto direction = target->getPosition() - this->getPosition();
    direction = glm::normalize(direction);
    velocity_ = direction * max_speed_;
}

