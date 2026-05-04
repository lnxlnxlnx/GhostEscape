#include "stats.h"

Stats *Stats::addStatsChild(Actor *parent, float max_health, float max_mana, float damage, float mana_regen)
{
    // 创建一个Stats对象，并将其添加为parent的子对象
    Stats *stats = new Stats();
    stats->max_health_ = max_health;
    stats->health_ = max_health;
    stats->max_mana_ = max_mana;
    stats->mana_ = max_mana;
    stats->damage_ = damage;
    stats->mana_regen_ = mana_regen;

    // 将stats添加为parent的子对象，并设置parent指针
    stats->parent_ = parent;
    parent->addChild(stats);
    // stats->setType(ObjectType::OBJECT_WORLD);
    return stats;
}

void Stats::update(float dt)
{
    Object::update(dt);
    if (!is_alive_)
        return;
    if (is_invincible_)
    {
        invincible_timer_ += dt;
        if (invincible_timer_ >= invincible_time_)
        {
            is_invincible_ = false;
            invincible_timer_ = 0.0f;
        }
    }

    regenMana(dt);
}

bool Stats::canUseMana(float mana_cost)
{
    if (getMana() >= mana_cost)
        return true;
    return false;
}

void Stats::useMana(float mana_cost)
{
    if (canUseMana(mana_cost))
    {
        mana_ -= mana_cost;
    }
}

void Stats::regenMana(float dt)
{
    if (getMana() < getMaxMana())
    {
        mana_ += getManaRegen() * dt;
        if (mana_ > getMaxMana())
        {
            mana_ = getMaxMana();
        }
    }
}

void Stats::takeDamage(float damage)
{
    if (is_invincible_ || !is_alive_)
        return;

    health_ -= damage;
    if (health_ <= 0)
    {
        health_ = 0;
        is_alive_ = false;
    }
// 受伤后进入无敌状态
#ifdef DEBUG_MODE
    spdlog::info("Take Damage: {},current Health: {}", damage, health_);
#endif
    is_invincible_ = true;
    invincible_timer_ = 0.0f;
}

void Stats::takeDamagePro(float damage, const Stats *attacker)
{
    if (is_invincible_ || !is_alive_)
        return;
    float rand_val_miss = game_.getRandomFloat(0.0f, 1.0f);
    float rand_val_crit = game_.getRandomFloat(0.0f, 1.0f);
    spdlog::info("Random Values - Miss: {}, Crit: {}", rand_val_miss, rand_val_crit);
    auto judge_miss = rand_val_miss < getMissRate();
    if (judge_miss)
    {
#ifdef DEBUG_MODE
        spdlog::info("Attack Missed!");
#endif
        return;
    }
    auto is_crit = rand_val_crit < attacker->getCritRate();
    if (is_crit)    {
        damage *= attacker->getCritDamage();
#ifdef DEBUG_MODE
        spdlog::info("Critical Hit! Crit Damage: {}", damage);
#endif
    }
    health_ -= damage;
    if (health_ <= 0)
    {
        health_ = 0;
        is_alive_ = false;
    }
// 受伤后进入无敌状态
#ifdef DEBUG_MODE
    spdlog::info("Take Damage: {},current Health: {}", damage, health_);
#endif
    is_invincible_ = true;
    invincible_timer_ = 0.0f;
}
