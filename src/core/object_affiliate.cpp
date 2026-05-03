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

void ObjectAffiliate::setOffsetByComponent(Anchor selfAnchor, Anchor targetAnchor, ObjectAffiliate *referenceComponent)
{
    if (!referenceComponent || !parent_)
    {
        return;
    }

    // 1. 获取参考组件在“父组件坐标系”中的绝对位置
    // 注意：这里假设 referenceComponent 和 this 拥有相同的 parent_。
    // 如果 referenceComponent 是深层嵌套的，需要将其位置转换到当前 parent_ 的坐标系下。
    // 简单情况下，我们直接取参考组件的世界位置（或相对于共同祖先的位置）。
    // 由于 ObjectAffiliate 通常存储的是相对于 parent 的 offset，
    // 我们需要计算 referenceComponent 相对于 current parent 的实际位置。
    
    // 如果 referenceComponent 的 parent 和 this 的 parent 是同一个：
    glm::vec2 refPosInParentSpace = referenceComponent->getOffset() + referenceComponent->getAnchorOffset(referenceComponent->getAnchor(), referenceComponent->getSize()); 
    // 上面的逻辑有点复杂，因为 getOffset 返回的是左上角相对于 parent 的偏移。
    // 更通用的做法是：获取参考组件某个锚点的世界坐标，然后减去当前 parent 的位置。
    
    // 简化方案：假设所有子组件的 getPosition() 返回的是相对于 Scene/World 的绝对坐标，
    // 或者我们有一个方法能获取相对于共同父节点的坐标。
    // 鉴于你的代码结构，最稳妥的方式是利用 getPosition() 如果它返回世界坐标：
    
    glm::vec2 refWorldPos = referenceComponent->parent_->getPosition(); // 假设这是参考组件左上角的世界坐标
    glm::vec2 refSize = referenceComponent->getSize();
    
    // 计算参考组件指定锚点 (targetAnchor) 的世界坐标
    glm::vec2 refAnchorOffset = getAnchorOffset(targetAnchor, refSize);
    glm::vec2 targetAnchorWorldPos = refWorldPos + refAnchorOffset;

    // 2. 计算当前组件自身锚点 (selfAnchor) 相对于自身左上角的偏移
    glm::vec2 myAnchorOffset = getAnchorOffset(selfAnchor, size_);

    // 3. 计算当前组件左上角应该处于的世界坐标
    // 使得: 我的左上角 + 我的锚点偏移 = 目标锚点世界坐标
    glm::vec2 myTopLeftWorldPos = targetAnchorWorldPos - myAnchorOffset;

    // 4. 计算相对于当前父组件的 offset_
    // offset_ = 我的左上角世界坐标 - 父组件左上角世界坐标
    glm::vec2 parentWorldPos = parent_->getPosition();
    
    // 更新自身的 anchor_ 记录，以便后续 autoResize 等操作能基于正确的锚点重新计算
    anchor_ = selfAnchor;
    
    offset_ = myTopLeftWorldPos - parentWorldPos;
}

// 辅助函数：获取指定锚点相对于组件原点(通常是左上角)的偏移向量
glm::vec2 ObjectAffiliate::getAnchorOffset(Anchor anchor, const glm::vec2 &size)
{
    switch (anchor)
    {
    case Anchor::TOP_LEFT:
        return glm::vec2(0.0f, 0.0f);
    case Anchor::TOP_CENTER:
        return glm::vec2(size.x / 2.0f, 0.0f);
    case Anchor::TOP_RIGHT:
        return glm::vec2(size.x, 0.0f);
    case Anchor::CENTER_LEFT:
        return glm::vec2(0.0f, size.y / 2.0f);
    case Anchor::CENTER:
        return glm::vec2(size.x / 2.0f, size.y / 2.0f);
    case Anchor::CENTER_RIGHT:
        return glm::vec2(size.x, size.y / 2.0f);
    case Anchor::BOTTOM_LEFT:
        return glm::vec2(0.0f, size.y);
    case Anchor::BOTTOM_CENTER:
        return glm::vec2(size.x / 2.0f, size.y);
    case Anchor::BOTTOM_RIGHT:
        return glm::vec2(size.x, size.y);
    default:
        return glm::vec2(0.0f, 0.0f);
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
