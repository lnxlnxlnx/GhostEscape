#ifndef F8E95DCF_98B2_43DE_8D8D_22AE3736F56E
#define F8E95DCF_98B2_43DE_8D8D_22AE3736F56E
// object_affiliate.h
#ifndef OBJECT_AFFILIATE_H
#define OBJECT_AFFILIATE_H

#include "object_screen.h"

class ObjectAffiliate : public Object 
{
protected:
    ObjectScreen *parent_ = nullptr; // 父节点
    glm::vec2 offset_ = glm::vec2(0, 0); // 相对父节点的偏移
    glm::vec2 size_ = glm::vec2(0, 0); // 大小

public:
    // getters and setters
    ObjectScreen *getParent() const { return parent_; }
    void setParent(ObjectScreen *parent) { parent_ = parent; }
    glm::vec2 getOffset() const { return offset_; }
    void setOffset(const glm::vec2 &offset) { offset_ = offset; }
    glm::vec2 getSize() const { return size_; }
    void setSize(const glm::vec2 &size) { size_ = size; }
};

#endif // OBJECT_AFFILIATE_H

#endif /* F8E95DCF_98B2_43DE_8D8D_22AE3736F56E */
