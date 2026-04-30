#include "game.h"
#include "../scene_main.h"

// 自定义彩色日志输出函数
static void SDL_ColorLog(void *userdata, int category, SDL_LogPriority priority, const char *message)
{
    (void)userdata; // 未使用参数，避免编译器警告
    (void)category; // 未使用参数，避免编译器警告
    (void)message;  // 未使用参数，避免编译器警告
    const char *color = "";

    // ANSI 颜色代码（Linux/macOS 通用）
    switch (priority)
    {
    case SDL_LOG_PRIORITY_VERBOSE:
        color = "\033[90m";
        break; // 灰色
    case SDL_LOG_PRIORITY_DEBUG:
        color = "\033[36m";
        break; // 青色
    case SDL_LOG_PRIORITY_INFO:
        color = "\033[32m";
        break; // 绿色
    case SDL_LOG_PRIORITY_WARN:
        color = "\033[33m";
        break; // 黄色
    case SDL_LOG_PRIORITY_ERROR:
        color = "\033[31m";
        break; // 红色
    case SDL_LOG_PRIORITY_CRITICAL:
        color = "\033[35;1m";
        break; // 亮紫色
    default:
        color = "\033[0m";
        break; // 默认白色
    }

    // 输出：颜色 + 信息 + 恢复默认颜色
    printf("%s%s\033[0m\n", color, message);
}

bool Game::setFPS(Uint64 fps)
{
    if (fps <= 29)
    {
        SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, "设置的FPS过低，可能会导致游戏体验不佳: %lu\n", fps);
        return false;
    }
    else if (fps > 181)
    {
        SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, "设置的FPS过高，可能会导致性能问题: %lu\n", fps);
        return false;
    }
    FPS_ = fps;
    frame_delay_ = 1'000'000'000 / FPS_;
    return true;
}

void Game::drawGrid(const glm::vec2 &top_left, const glm::vec2 &botton_right, float grid_distance, SDL_FColor fcolor)
{
    SDL_SetRenderDrawColorFloat(renderer_, fcolor.r, fcolor.g, fcolor.b, fcolor.a);
    for (float x = top_left.x; x <= botton_right.x; x += grid_distance){
        SDL_RenderLine(renderer_, x, top_left.y, x, botton_right.y);
    }
    for (float y = top_left.y; y <= botton_right.y; y += grid_distance){
        SDL_RenderLine(renderer_, top_left.x, y, botton_right.x, y);
    }
    SDL_SetRenderDrawColorFloat(renderer_, 0, 0, 0, 1);
}

void Game::drawBoundary(const glm::vec2 &top_left, const glm::vec2 &botton_right, float boundary_width, SDL_FColor fcolor)
{
    SDL_SetRenderDrawColorFloat(renderer_, fcolor.r, fcolor.g, fcolor.b, fcolor.a);
    for (float i = 0; i < boundary_width; i++){
        SDL_FRect rect = {
            top_left.x - i,
            top_left.y - i,
            botton_right.x - top_left.x + 2 * i,
            botton_right.y - top_left.y + 2 * i
        };
        SDL_RenderRect(renderer_, &rect);
    }
    SDL_SetRenderDrawColorFloat(renderer_, 0, 0, 0, 1);
}

void Game::run()
{
    while (is_running_)
    {
        auto start = SDL_GetTicksNS(); // 纳秒级时间戳
        handleEvents();
        update(dt_); // 使用计算出的dt_更新游戏状态
        render();
        auto end = SDL_GetTicksNS();
        auto elapsed = end - start;
        if (elapsed < frame_delay_)
        {
            SDL_DelayNS((frame_delay_ - elapsed)); // 纳秒级延迟
            dt_ = frame_delay_ / 1.0e9;            // 纳秒转换为秒
        }
        else
        {
            dt_ = elapsed / 1.0e9; // 纳秒转换为秒
        }
        SDL_Log("FPS: %f", 1.0 / dt_);
    }
}

void Game::init(std::string title, int width, int height)
{
    screen_size_ = glm::vec2(width, height);
    SDL_SetLogOutputFunction(SDL_ColorLog, nullptr); // 设置自定义日志输出函数
    // SDL3初始化
    if (!SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO))
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL初始化失败: %s\n", SDL_GetError());
    }
    // 不需要进行SDL_image初始化
    // SDL3_Mixer初始化
    if (Mix_Init(MIX_INIT_MP3 | MIX_INIT_OGG) != (MIX_INIT_MP3 | MIX_INIT_OGG))
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_Mixer初始化失败: %s\n", SDL_GetError());
    }
    if (!Mix_OpenAudio(0, NULL))
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_Mixer打开音频失败: %s\n", SDL_GetError());
    }
    Mix_AllocateChannels(16);            // 分配16个音频通道
    Mix_VolumeMusic(MIX_MAX_VOLUME / 4); // 设置音乐音量
    Mix_Volume(-1, MIX_MAX_VOLUME / 4);  // 设置音效音量

    // SDL3_TTF初始化
    if (!TTF_Init())
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_TTF初始化失败: %s\n", SDL_GetError());
    }
    // 创建窗口与渲染器
    SDL_CreateWindowAndRenderer(title.c_str(), width, height, SDL_WINDOW_RESIZABLE, &window_, &renderer_);
    if (!window_ || !renderer_)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "创建窗口或渲染器失败: %s\n", SDL_GetError());
    }
    // 设置窗口逻辑分辨率
    SDL_SetRenderLogicalPresentation(renderer_, width, height, SDL_LOGICAL_PRESENTATION_LETTERBOX);

    frame_delay_ = 1'000'000'000 / FPS_; // 计算每帧的延迟时间，单位为纳秒
    current_scene_ = new SceneMain();
    current_scene_->init();
}

void Game::handleEvents()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_EVENT_QUIT:
            is_running_ = false;
            break;
        case SDL_EVENT_KEY_DOWN:
            switch (event.key.key)
            {
            case SDLK_ESCAPE:
                is_running_ = false;
                break;
            case SDLK_1:
                setFPS(90); // 切换到90 FPS
                break;
            case SDLK_2:
                setFPS(30); // 切换到30 FPS
                break;
            default:
                break;
            }
            break;
        default:
            current_scene_->handleEvents(event);
            break;
        }
    }
}

void Game::update(float dt)
{
    if (current_scene_)
    {
        current_scene_->update(dt_);
    }
}

void Game::render()
{
    SDL_SetRenderDrawColor(renderer_, 255, 255, 255, 255);
    SDL_RenderClear(renderer_);
    if (current_scene_)
    {
        current_scene_->render();
    }
    SDL_RenderPresent(renderer_);
}

void Game::clean()
{
    if (current_scene_)
    {
        current_scene_->clean();
        delete current_scene_;
        current_scene_ = nullptr;
    }
    if (renderer_)
    {
        SDL_DestroyRenderer(renderer_);
        renderer_ = nullptr;
    }
    if (window_)
    {
        SDL_DestroyWindow(window_);
        window_ = nullptr;
    }
    TTF_Quit();
    Mix_CloseAudio();
    Mix_Quit();
    SDL_Quit();
}
