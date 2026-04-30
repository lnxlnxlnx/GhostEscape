#ifndef A8380280_8934_47CD_A1D2_F957AA645C23
#define A8380280_8934_47CD_A1D2_F957AA645C23
#include <glm/glm.hpp>
#include "object.h"
#include <vector>

class Scene : public Object {
protected:
    glm::vec2 camera_pos_ = glm::vec2(0);
    glm::vec2 world_size_ = glm::vec2(0); // 世界大小
    std::vector<Object*> objects_;
    float camera_zoom_ = 1.0f; // 摄像机缩放

public:
    Scene() = default;
    virtual ~Scene() = default;

    // 工具函数
    auto worldToScreen(glm::vec2 world_pos) const {
        return (world_pos - camera_pos_) * camera_zoom_;
    }

    auto screenToWorld(glm::vec2 screen_pos) const {
        return screen_pos / camera_zoom_ + camera_pos_;
    }

        //getter and setter
    auto getCameraPos() const { return camera_pos_; }
    auto getCameraZoom() const { return camera_zoom_; }

    void setCameraZoom(float zoom);

    void setCameraPosition(const glm::vec2& pos);

    auto getWorldSize() const { return world_size_; }

    virtual void init() override {}
    virtual void handleEvents(SDL_Event& event) override {(void)event;}
    virtual void update(float dt) override {(void) dt;}
    virtual void render() override {}
    virtual void clean() override {}
};

#endif /* A8380280_8934_47CD_A1D2_F957AA645C23 */
