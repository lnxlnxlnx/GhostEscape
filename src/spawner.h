#ifndef A97989D2_5E31_49E8_A727_30CD34CA30E9
#define A97989D2_5E31_49E8_A727_30CD34CA30E9
// spawner.h
#ifndef SPAWNER_H
#define SPAWNER_H

#include "core/object.h"
class Player;
class Spawner : public Object {
protected:
    int num_ = 20;            // 每次生成的敌人数量
    float timer_ = 0;         // 计时器
    float interval_ = 3.0f;   // 生成间隔（秒）
    Player* target_ = nullptr; // 目标玩家

public:
    virtual void update(float dt) override;

    // setters and getters
    int getNum() const { return num_; }
    void setNum(int num) { num_ = num; }
    float getTimer() const { return timer_; }
    void setTimer(float timer) { timer_ = timer; }
    float getInterval() const { return interval_; }
    void setInterval(float interval) { interval_ = interval; }
    Player* getTarget() const { return target_; }
    void setTarget(Player* target) { target_ = target; }
};

#endif // SPAWNER_H

#endif /* A97989D2_5E31_49E8_A727_30CD34CA30E9 */
