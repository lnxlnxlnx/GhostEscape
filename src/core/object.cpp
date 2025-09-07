#include "object.h"

bool Object::handleEvents(SDL_Event& event) {
    for (auto& child : children_) {
        if(child->getActive()) {
            if (child->handleEvents(event)) return true;
        }
    }
    return false;
}

void Object::update(float dt) {
    for (auto& child : object_to_add_) {
        addChild(child);        //懒更新
    }
    
    object_to_add_.clear();
    for (auto it = children_.begin(); it != children_.end();) {
        //child 只是一个指针变量，用来接收迭代器解引用后得到的指针值，方便后续对该指针指向的对象进行操作（如判断是否需要删除、更新等）。
        //这里iterator解引用得到的是一个Object*类型的指针，child变量就是用来存储这个指针的。
        //就是说it指向的也是一个指针，这个指针指向的对象是一个Object对象。
        auto child = *it;
        if (child->getNeedRemove()){
            it = children_.erase(it);
            child->clean();
            delete child;
            child = nullptr;
        } else {
            if(child->getActive()) {        
                //这里的child不仅仅是人物角色，也可能是子弹，特效，UI等对象，所以这里要判断是否激活
                child->update(dt);
            }
            ++it;
        }
    }
} 

void Object::render() {
    for (auto& child : children_) {
        if(child->getActive()) {
            child->render();
        }
    }
}

void Object::clean() {
    for (auto& child : children_) {
        child->clean();
        delete child;
        child = nullptr;
    }
    children_.clear();
}