#ifndef F20D6098_BE6B_4F76_A0A2_638D345D3091
#define F20D6098_BE6B_4F76_A0A2_638D345D3091
#include "affiliate/sprite.h"
#include "core/actor.h"
#include <glm/glm.hpp>

class Bullet : public Actor { 
    float damage = 10.0f;
    Sprite *sprite_ = nullptr;

public:
    Bullet() = default;

    static Bullet *addBulletChild(Actor *parent, const std::string &file_path, float scale);

    void init() override;

    void update(float dt) override ;

    void clean() override;
    
    //getters and setters
    float getDamage() const { return damage; }
    void setDamage(float damage) { this->damage = damage; }

    void move(float dt) override;
};

#endif /* F20D6098_BE6B_4F76_A0A2_638D345D3091 */
