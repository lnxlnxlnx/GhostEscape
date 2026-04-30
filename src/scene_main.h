#ifndef A8A185ED_E924_456F_A5CA_E4DF1F95705C
#define A8A185ED_E924_456F_A5CA_E4DF1F95705C
#include "core/scene.h"

class SceneMain: public Scene
{
    glm::vec2 world_size_ = glm::vec2(0); // 世界大小
    float camera_zoom_ = 1.0f; // 摄像机缩放

    // 相机振动
    float shake_power_ = 5.0f;
    float shake_time_ = 1.0f;
    float shake_decay_ = 0.90f;


public:
    SceneMain() = default;
    virtual ~SceneMain() = default;

    virtual void init() override;
    virtual void handleEvents(SDL_Event& event) override;
    virtual void update(float dt) override;
    void updateCamera(float dt, glm::vec2 target_pos);
    void updateCameraShake(float dt);
    virtual void render() override;
    virtual void clean() override;

    // 工具函数
    void renderBackground();
    void cameraShake(float power, float duration);

    //getter and setter
    auto getCameraPos() const { return camera_pos_; }
    auto getCameraZoom() const { return camera_zoom_; }

    auto setCameraZoom(float zoom) {
        camera_zoom_ = zoom;
        // 限制缩放范围
        camera_zoom_ = glm::clamp(camera_zoom_, 0.5f, 3.0f);
    }

    auto setCameraPos(const glm::vec2& pos) {
        camera_pos_ = pos;
        // 限制摄像机在世界范围内
        camera_pos_ = glm::clamp(camera_pos_, glm::vec2(0), world_size_ - game_.getScreenSize() / camera_zoom_); //NOTE: / camera_zoom_ 是为了考虑缩放后的屏幕大小
    }
};

#endif /* A8A185ED_E924_456F_A5CA_E4DF1F95705C */
