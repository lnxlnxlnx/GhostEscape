#include "object_affiliate.h"
#include "config_manager.h"

void ObjectAffiliate::autoResize()
{
    size_ = Game::GetInstance().getConfig()->get<glm::vec2>("player.size", glm::vec2(32.0f, 32.0f));
}

void ObjectAffiliate::init()
{
    Object::init();
}

void ObjectAffiliate::render()
{
    Object::render();
}

void ObjectAffiliate::update(float dt)
{
    Object::update(dt);
}

void ObjectAffiliate::clean()
{
    Object::clean();
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

//TODO: 核心还是坐标起点，一开始思路是对的，就是先设计一个setOffsetByPosition方法
void ObjectAffiliate::setOffsetByComponent(Anchor selfAnchor, Anchor targetAnchor, ObjectAffiliate *referenceComponent)
{
    if (!referenceComponent || !parent_)
    {
        return;
    }

    // --- 第一步：计算参考组件的目标锚点在世界空间中的绝对位置 ---
    
    // 1. 获取参考组件的父节点世界坐标
    // 注意：如果 referenceComponent 没有父节点，通常意味着它是根节点，其位置即为其 offset 或 getPosition()
    glm::vec2 refParentWorldPos = referenceComponent->parent_ ? referenceComponent->parent_->getPosition() : glm::vec2(0.0f);
    
    // 2. 计算参考组件左上角在世界空间中的位置
    // 参考组件的世界位置 = 参考组件父节点世界位置 + 参考组件相对于其父节点的 offset_
    glm::vec2 refTopLeftWorldPos = refParentWorldPos + referenceComponent->getOffset();
    
    // 3. 计算目标锚点相对于参考组件左上角的偏移
    glm::vec2 targetAnchorLocalOffset = getAnchorOffset(targetAnchor, referenceComponent->getSize());
    
    // 4. 得到目标锚点的世界坐标 (这就是我们要对齐的那个点)
    glm::vec2 targetAnchorWorldPos = refTopLeftWorldPos + targetAnchorLocalOffset;


    // --- 第二步：计算当前组件为了对齐该点，其左上角应该在哪里 ---

    // 5. 计算自身锚点相对于自身左上角的偏移
    glm::vec2 selfAnchorLocalOffset = getAnchorOffset(selfAnchor, size_);
    
    // 6. 计算自身左上角应该处于的世界坐标
    // 公式：自身左上角世界坐标 + 自身锚点局部偏移 = 目标锚点世界坐标
    glm::vec2 myTopLeftWorldPos = targetAnchorWorldPos - selfAnchorLocalOffset;


    // --- 第三步：计算相对于当前父节点 (this->parent_) 的 offset_ ---

    // 7. 获取当前组件父节点的世界坐标
    glm::vec2 myParentWorldPos = parent_->getPosition();
    
    // 8. 计算最终的 offset_
    // 公式：我的 offset_ = 我的左上角世界坐标 - 我父节点的世界坐标
    offset_ = myTopLeftWorldPos - myParentWorldPos;
    
    // 更新内部记录的锚点，以便后续 resize 等操作能正确重新计算
    anchor_ = selfAnchor;
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
