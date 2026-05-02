#include "bullet.h"
#include "core/config_manager.h"
#include <glm/glm.hpp>
#include "core/scene.h"
Bullet *Bullet::addBulletChild(Actor *parent, const std::string &file_path, float scale)
{
    Bullet *bullet = new Bullet();
    bullet->init();
    bullet->sprite_ = Sprite::addSpriteChild(bullet, file_path, scale);    // 为了了让子弹的精灵能够正确地跟随子弹的位置和旋转，设置精灵的父节点为子弹自己
    parent->addChild(bullet);
    bullet->velocity_ = glm::normalize(parent->getVelocity()) * bullet->getMaxSpeed(); // 子弹的初始速度与父对象的速度方向相同，大小为子弹的最大速度
    bullet->setRenderPosition(parent->getRenderPosition());
    return bullet;
}
void Bullet::init()
{
    //texture_ = Texture(game_.getConfig()->get<std::string>("bullet.texture", "assets/test/hp.png"));
    max_speed_ = 300.0f;   
}

void Bullet::update(float dt)
{
    if (ObjectWorld::ifOutOfWorld(this)){
        setNeedRemove(true);
        return;
    }
    move(dt);
}

void Bullet::clean()
{
    if (sprite_ != nullptr)
    {
        sprite_->clean();
        delete sprite_;
        sprite_ = nullptr;
    }
}

void Bullet::move(float dt)
{
    setPosition(position_ + velocity_ * dt);
    position_ = glm::clamp(position_, glm::vec2(-100), game_.getCurrentScene()->getWorldSize() + glm::vec2(100, 100));
}
