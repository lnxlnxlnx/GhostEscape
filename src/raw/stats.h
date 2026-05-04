#ifndef C204A269_924F_4D69_8A31_7A7EA2E1A5D7
#define C204A269_924F_4D69_8A31_7A7EA2E1A5D7
// stats.h
#ifndef STATS_H
#define STATS_H

#include "../core/actor.h"
class Actor;
class Stats : public Object
{
protected:
    Actor* parent_ = nullptr;
    float health_ = 100.0f;
    float max_health_ = 100.0f;
    float mana_ = 100.0f;
    float max_mana_ = 100.0f;
    float damage_ = 40.0f;
    float mana_regen_ = 10.0f;

    // 高级属性
    float crit_rate_ = 0.5f;
    float crit_damage_ = 1.5f;
    float miss_rate_ = 0.5f;

    // 等级
    uint8_t level_ = 1;
    uint32_t current_exp_ = 0;
    uint32_t exp_to_next_level_ = 100;

    // 效果状态
    float invincible_time_ = 0.3f;      // 受伤后，无敌时间有多长
    float invincible_timer_ = 0.0f;     // 无敌计时器
    bool is_alive_ = true;
    bool is_invincible_ = false;

public:
    static Stats* addStatsChild(Actor* parent, float max_health = 100.0f, float max_mana = 100.0f, float damage = 40.0f, float mana_regen = 10.0f);
    virtual void update(float dt) override;

    bool canUseMana(float mana_cost);
    void useMana(float mana_cost);
    void regenMana(float dt);
    void takeDamage(float damage);
    void takeDamagePro(float damage, const Stats *attacker);
    void levelUp();

    // getters and setters
    float getHealth() const { return health_; }
    float getMaxHealth() const { return max_health_; }
    float getMana() const { return mana_; }
    float getMaxMana() const { return max_mana_; }
    float getDamage() const { return damage_; }
    float getManaRegen() const { return mana_regen_; }
    bool getIsAlive() const { return is_alive_; }
    float getCritRate() const { return crit_rate_; }
    float getCritDamage() const { return crit_damage_; }
    float getMissRate() const { return miss_rate_; }
    void setCritRate(float crit_rate) { crit_rate_ = crit_rate; }
    void setCritDamage(float crit_damage) { crit_damage_ = crit_damage; }
    void setMissRate(float miss_rate) { miss_rate_ = miss_rate; }
    // ... 更多getter和setter方法
};

#endif // STATS_H

#endif /* C204A269_924F_4D69_8A31_7A7EA2E1A5D7 */
