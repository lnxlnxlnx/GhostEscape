#include "player.h"
#include "enemy.h"
#include "affiliate/sprite_anim.h"
#include "core/config_manager.h"
#include "bullet.h"
#include "affiliate/collider.h"
#include "scene_main.h"

void Enemy::init()
{
    Actor::init();
    anim_normal_ = SpriteAnim::addSpriteAnimChild(this, game_.getConfig()->get<std::string>("enemy.sprite_move"), 2.0f);
    anim_hurt_ = SpriteAnim::addSpriteAnimChild(this, game_.getConfig()->get<std::string>("enemy.sprite_hurt"), 2.0f);
    anim_die_ = SpriteAnim::addSpriteAnimChild(this, game_.getConfig()->get<std::string>("enemy.sprite_dead"), 2.0f);
    anim_hurt_->setActive(false);
    anim_die_->setActive(false);
    // 设置死亡动画为播放一次模式
    anim_die_->setPlayMode(SpriteAnimPlayMode::PLAY_ONCE);
    current_anim_ = anim_normal_;

    // 碰撞体
    collider_ = Collider::addColliderChild(this, anim_normal_->getSize(), Collider::Type::CIRCLE);
    stats_ = Stats::addStatsChild(this);
}

void Enemy::update(float dt)
{
    Actor::update(dt);
    aim_target(target_);
    move(dt);
    timer_ += dt;
    if (timer_ > 2.0f && timer_ < 4.0f)
    {
        changeState(State::HURT);
    }
    else if (timer_ > 4.0f)
    {
        changeState(State::DIE);
        Bullet::addBulletChild(this, game_.getConfig()->get<std::string>("bullet.texture", "assets/test/hp.png"), 1.0f);
    }
    if (timer_ > 6.0f){
        timer_ = 0.0f;
        changeState(State::NORMAL);
    }
    attack();
}

void Enemy::aim_target(Player *target)
{
    if (target == nullptr)
        return;
    auto direction = target->getPosition() - this->getPosition();
    direction = glm::normalize(direction);
    velocity_ = direction * max_speed_;
}

void Enemy::changeState(State new_state)
{
    if (new_state == current_state_)
        return;
    current_anim_->setActive(false);
    switch (new_state)
    {
    case State::NORMAL:
        current_anim_ = anim_normal_;
        current_anim_->setActive(true);
        break;
    case State::HURT:
        current_anim_ = anim_hurt_;
        current_anim_->setActive(true);
        break;
    case State::DIE:
        current_anim_ = anim_die_;
        current_anim_->setActive(true);
        break;
    }
    current_state_ = new_state;
}

void Enemy::updateState(float dt)
{
}

void Enemy::attack()
{
    if (!collider_ || target_->getCollider() == nullptr) return;
    if (collider_->isColliding(target_->getCollider())) {
        // TODO: attack
        SceneMain::solveImpulse(this, target_);
        if (stats_ != nullptr && target_ ->getStats() != nullptr && stats_->isAlive())
        {
            target_->takeDamage(stats_->getDamage());
        }
        //SDL_Log("Circle vs Circle");
    }
}
