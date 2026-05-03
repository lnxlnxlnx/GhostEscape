#ifndef F8E95DCF_98B2_43DE_8D8D_22AE3736F56E
#define F8E95DCF_98B2_43DE_8D8D_22AE3736F56E
// object_affiliate.h
#ifndef OBJECT_AFFILIATE_H
#define OBJECT_AFFILIATE_H

#include "object_screen.h"
#include "defs.h"

class ObjectAffiliate : public Object 
{
protected:
    ObjectScreen *parent_ = nullptr; // 父节点
    glm::vec2 offset_ = glm::vec2(0, 0); // 相对父节点的偏移
    glm::vec2 size_ = glm::vec2(0, 0); // 大小
    Anchor anchor_ = Anchor::NONE;

public:

    void autoResize();

    // getters and setters
    ObjectScreen *getParent() const { return parent_; }
    void setParent(ObjectScreen *parent) { parent_ = parent; }
    glm::vec2 getOffset() const { return offset_; }
    void setOffset(const glm::vec2 &offset) { offset_ = offset; }

    void setOffsetByAnchor(Anchor anchor);

    void setOffsetByComponent(Anchor selfAnchor, Anchor targetAnchor, ObjectAffiliate *referenceComponent);
    glm::vec2 getSize() const { return size_; }
    glm::vec2 getAnchorOffset(Anchor anchor, const glm::vec2 &size);
    void setSize(const glm::vec2 &size);

    void setScale(float scale);

    Anchor getAnchor() const { return anchor_; }
    void setAnchor(Anchor anchor) { anchor_ = anchor; }
};

#endif // OBJECT_AFFILIATE_H

#endif /* F8E95DCF_98B2_43DE_8D8D_22AE3736F56E */
