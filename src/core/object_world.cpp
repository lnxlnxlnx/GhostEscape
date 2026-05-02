// object_world.cpp
#include "object_world.h"
#include "scene.h"

void ObjectWorld::update(float dt)
{
    ObjectScreen::update(dt);
    render_position_ = game_.getCurrentScene()->worldToScreen(position_);
}

bool ObjectWorld::ifOutOfWorld(ObjectWorld *obj)
{

    auto world_size = Game::GetInstance().getCurrentScene()->getWorldSize();
    auto pos = obj->getPosition();
    return pos.x < 0 || pos.y < 0 || pos.x > world_size.x || pos.y > world_size.y;
}

void ObjectWorld::setPosition(const glm::vec2 &position)
{
    position_ = position;
    render_position_ = game_.getCurrentScene()->worldToScreen(position_);
}

void ObjectWorld::setRenderPosition(const glm::vec2 &render_position)
{
    render_position_ = render_position;
    position_ = game_.getCurrentScene()->screenToWorld(render_position);
}