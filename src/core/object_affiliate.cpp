#include "object_affiliate.h"
#include "config_manager.h"

void ObjectAffiliate::autoResize()
{
    size_ = Game::GetInstance().getConfig()->get<glm::vec2>("player.size", glm::vec2(32.0f, 32.0f));
}

void ObjectAffiliate::setOffsetByAnchor(Anchor anchor)
{
    anchor_ = anchor;
    switch (anchor)
    {
        case Anchor::TOP_LEFT:
            offset_ = glm::vec2(0.0f, 0.0f);
            break;
        case Anchor::TOP_CENTER:
            offset_ = glm::vec2(-size_.x / 2.0f, 0);
            break;
        case Anchor::TOP_RIGHT:
            offset_ = glm::vec2(-size_.x, 0.0f);
            break;
        case Anchor::CENTER_LEFT:
            offset_ = glm::vec2(0.0f, -size_.y / 2.0f);
            break;
        case Anchor::CENTER:
            offset_ = glm::vec2(-size_.x / 2.0f, -size_.y / 2.0f);
            break;
        case Anchor::CENTER_RIGHT:
            offset_ = glm::vec2(-size_.x, -size_.y / 2.0f);
            break;
        case Anchor::BOTTOM_LEFT:
            offset_ = glm::vec2(0.0f, -size_.y);
            break;
        case Anchor::BOTTOM_CENTER:
            offset_ = glm::vec2(-size_.x / 2.0f, -size_.y);
            break;
        case Anchor::BOTTOM_RIGHT:
            offset_ = glm::vec2(-size_.x, -size_.y);
            break;
        default:
            break;
    }
}

void ObjectAffiliate::setSize(const glm::vec2 &size)
{
    size_ = size;
    setOffsetByAnchor(anchor_);
}

void ObjectAffiliate::setScale(float scale)
{
    size_ *= scale;
    setOffsetByAnchor(anchor_);
}
