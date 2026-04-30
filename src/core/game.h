#ifndef D612A095_AA1C_4DEA_BD5B_827592203F28
#define D612A095_AA1C_4DEA_BD5B_827592203F28
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_mixer/SDL_mixer.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <glm/glm.hpp>
#include <string>

class Scene; // 前向声明
class Game
{
    glm::vec2 screen_size_ = glm::vec2(0); // 屏幕大小
    bool is_running_ = true;               // 游戏是否运行

    SDL_Window *window_ = nullptr;     // 窗口
    SDL_Renderer *renderer_ = nullptr; // 渲染器

    // 帧率控制
    Uint64 FPS_ = 60;        // 游戏帧率
    Uint64 frame_delay_ = 0; // 帧延迟，单位ns
    float dt_ = 0.0f;        // 帧间隔

    // 当前场景
    Scene *current_scene_ = nullptr;

    // 私有构造函数
    Game() {}
    // 禁止拷贝构造函数与赋值操作符
    Game(const Game &) = delete;
    Game &operator=(const Game &) = delete;

public:
    static Game &GetInstance()
    {
        static Game instance;
        return instance;
    }

    void run();                                          // 运行游戏, 执行游戏主循环
    void init(std::string title, int width, int height); // 初始化游戏
    void handleEvents();                                 // 处理事件
    void update(float dt);                               // 更新游戏状态
    void render();                                       // 渲染游戏
    void clean();                                        // 清理游戏资源
};

#endif /* D612A095_AA1C_4DEA_BD5B_827592203F28 */
