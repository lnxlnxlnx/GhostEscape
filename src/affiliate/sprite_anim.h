#ifndef A35E3D3C_F21D_4163_A036_4D8FF33E4A76
#define A35E3D3C_F21D_4163_A036_4D8FF33E4A76
#include "sprite.h"

enum class SpriteAnimPlayMode
{
    PLAY_ONCE,
    PLAY_LOOP,
    PLAY_PING_PONG
};

// sprite_anim.h
class SpriteAnim : public Sprite
{
    int current_frame_ = 0;
    int total_frames_ = 0;
    int fps_ = 10;
    float frame_timer_ = 0.0f;
    bool finished_ = false; // 仅在PLAY_ONCE模式下使用，表示动画是否已经播放完成
    SpriteAnimPlayMode play_mode_ = SpriteAnimPlayMode::PLAY_LOOP;

    void updateAnimByPlayMode(float dt);

public:
    static SpriteAnim* addSpriteAnimChild(ObjectScreen* parent, const std::string& file_path, float scale = 1.0f);
    virtual void update(float dt) override;

    // getters and setters
    virtual void setTexture(const Texture &texture) override;

    int getCurrentFrame() const { return current_frame_; }
    void setCurrentFrame(int current_frame) { current_frame_ = current_frame; }
    int getTotalFrames() const { return total_frames_; }
    void setTotalFrames(int total_frames) { total_frames_ = total_frames; }
    int getFps() const { return fps_; }
    void setFps(int fps) { fps_ = fps; }
    SpriteAnimPlayMode getPlayMode() const { return play_mode_; }
    void setPlayMode(SpriteAnimPlayMode play_mode) { play_mode_ = play_mode; }
    bool isFinished() const { return finished_; }
    void setFinished(bool finished) { finished_ = finished; }
};

#endif /* A35E3D3C_F21D_4163_A036_4D8FF33E4A76 */
