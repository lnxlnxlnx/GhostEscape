#include "stats.h"

/* 
这个方法创建一个新的Stats对象，设置其属性，并将其添加为父Actor的子对象。注意这里我们将组件的初始生命值设置为最大生命值，魔法值也是如此，这确保了角色初始状态是满血满魔的。
 */
Stats *Stats::addStatsChild(Actor *parent, float max_health, float max_mana, float damage, float mana_regen)
{
    Stats *stats = new Stats();
    stats->parent_ = parent;
    stats->max_health_ = max_health;
    stats->health_ = max_health;
    stats->max_mana_ = max_mana;
    stats->mana_ = max_mana;
    stats->damage_ = damage;
    stats->mana_regen_ = mana_regen;
    if (parent) parent->addChild(stats);
    return stats;
}

void Stats::update(float dt)
{
    Object::update(dt);
    regenMana(dt);
    if (is_invincible_) {
        invincible_timer_ += dt;
        if (invincible_timer_ >= invincible_time_) {
            is_invincible_ = false;
            invincible_timer_ = 0;
        }
    }
}

bool Stats::canUseMana(float cost)
{
    return mana_ >= cost;
}

void Stats::useMana(float cost)
{
    mana_ -= cost;
    if (mana_ < 0) mana_ = 0;
}

void Stats::regenMana(float dt)
{
    mana_ += mana_regen_ * dt;
    if (mana_ > max_mana_) mana_ = max_mana_;
}

void Stats::takeDamage(float damage)
{
    if (is_invincible_) return;

    health_ -= damage;
    if (health_ < 0) {
        health_ = 0;
        is_alive_ = false;
    }
    is_invincible_ = true;
    invincible_timer_ = 0.0f;
}