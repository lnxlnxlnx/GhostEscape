#include "object_affiliate.h"
#include "config_manager.h"

void ObjectAffiliate::autoResize()
{
    size_ = Game::GetInstance().getConfig()->get<glm::vec2>("player.size", glm::vec2(32.0f, 32.0f));
}