#include <iostream>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_mixer/SDL_mixer.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <glm/glm.hpp>

// 自定义彩色日志输出函数
void SDL_ColorLog(void *userdata, int category, SDL_LogPriority priority, const char *message)
{
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

int main(int, char **)
{

    glm::vec2 a = glm::vec2(1.0f, 2.0f);
    glm::vec2 b = glm::vec2(3.0f, 4.0f);
    auto c = a * b;
    auto d = glm::distance(a, b);
    auto e = glm::dot(a, b);
    auto f = glm::cross(glm::vec3(a, 0.0f), glm::vec3(b, 0.0f));
    SDL_SetLogOutputFunction(SDL_ColorLog, NULL);

    SDL_Log("普通日志 (白色)");
    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "信息 (蓝色)");
    SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, "警告 (黄色)");
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "错误 (红色)");
    SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "严重错误 (亮红)");
    SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "调试 (青色)");

    SDL_SetLogPriority(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_DEBUG);
    // 即使你设置所有分类只显示错误
    // SDL_SetLogPriority(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO);

    SDL_Log("d = (%3.3f)", d);
    SDL_Log("e = (%3.3f)", e);
    SDL_Log("f = (%3.3f, %3.3f, %3.3f)", f.x, f.y, f.z);
    SDL_Log("c = (%3.3f, %3.3f)", c.x, c.y);

    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Hello, SDL3!");
    SDL_LogInfo(SDL_LOG_CATEGORY_TEST, "Hello, SDL3!");
    SDL_LogError(SDL_LOG_CATEGORY_TEST, "Hello, SDL3!");

    std::cout << "Hello, World!" << std::endl;
    // SDL初始化
    if (!SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO))
    {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return 1;
    }
    // 创建窗口
    SDL_Window *window = SDL_CreateWindow("Hello World!", 800, 600, 0);
    // 创建渲染器
    SDL_Renderer *renderer = SDL_CreateRenderer(window, NULL);

    // SDL3_Image不需要手动初始化

    // 加载图片
    SDL_Texture *texture = IMG_LoadTexture(renderer, "assets/UI/A_Back1.png");

    // SDL_Mixer初始化
    if (!Mix_OpenAudio(0, NULL))
    {
        std::cerr << "Mix_OpenAudio Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    // 读取音乐
    Mix_Music *music = Mix_LoadMUS("assets/bgm/OhMyGhost.ogg");
    // 播放音乐
    Mix_PlayMusic(music, -1);

    // SDL_TTF初始化
    if (!TTF_Init())
    {
        std::cerr << "TTF_Init Error: " << SDL_GetError() << std::endl;
        return 1;
    }
    // 加载字体
    TTF_Font *font = TTF_OpenFont("assets/font/VonwaonBitmap-16px.ttf", 24);

    // 创建文本纹理
    SDL_Color color = {200, 255, 255, 255};
    SDL_Surface *surface = TTF_RenderText_Solid(font, "Hello, SDL! 中文也可以", 0, color);
    // 这种方法创建的纹理无法设置颜色了，除非重新创建一个新的surface
    SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer, surface);

    // SDL3 新的绘制文本方法
    TTF_TextEngine *textEngine = TTF_CreateRendererTextEngine(renderer);
    TTF_Text *text = TTF_CreateText(textEngine, font, "SDL3 新的文本渲染方式", 0);
    TTF_Text *text2 = TTF_CreateText(textEngine, font, "测试鼠标移动到指定范围", 0);
    TTF_SetTextColor(text, 200, 50, 0, 255);
    TTF_SetTextColor(text2, 200, 50, 0, 255);
    TTF_SetTextWrapWidth(text, 50);
    TTF_SetTextWrapWidth(text2, 50);
    // Do something with the window and renderer here...
    // 渲染循环
    glm::vec2 mousePos = glm::vec2(0.0f, 0.0f);
    while (true)
    {
        SDL_Event event;
        int r, g, b;

        if (SDL_PollEvent(&event))
        {
            if (event.type == SDL_EVENT_QUIT)
            {
                break;
            }
        }
        auto state = SDL_GetMouseState(&mousePos.x, &mousePos.y);
        // SDL_Log("Mouse Pos: (%f, %f)", mousePos.x, mousePos.y);
        // if (mousePos.x > 100 && mousePos.x < 300 && mousePos.y > 100 && mousePos.y < 300)
        // {
        //     SDL_Log("Mouse is inside the rectangle!");
        //     TTF_SetTextColor(text2, 0, 0, 100, 255);
        //     TTF_DrawRendererText(text2, 100, 200);
        // }
        // else{
        //     TTF_SetTextColor(text2, 200, 50, 0, 255);
        //     TTF_DrawRendererText(text2, 400, 450);
        // }

        if (state & SDL_BUTTON_LMASK)
        {
            SDL_Log("Left Button Down");
        }
        if (state & SDL_BUTTON_RMASK)
        {
            SDL_Log("Right Button Down");
        }
        // 清屏
        SDL_RenderClear(renderer);
        // 画一个长方形
        SDL_FRect rect = {100, 100, 200, 200};
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderFillRect(renderer, &rect);

        // 画图片
        SDL_FRect dstrect = {200, 200, 200, 200};
        SDL_RenderTexture(renderer, texture, NULL, &dstrect);

        // 画文本
        SDL_SetRenderDrawColor(renderer, r, g, b, 255);

        r = rand() % 255;
        g = rand() % 255;
        b = rand() % 255;
        SDL_FRect textRect = {300, 300, static_cast<float>(surface->w), static_cast<float>(surface->h)};
        TTF_SetTextColor(text, r, g, b, 255);
        SDL_SetRenderDrawColor(renderer, r, g, b, 255);
        SDL_RenderTexture(renderer, textTexture, NULL, &textRect);

        // 新的画文本方法：
        TTF_DrawRendererText(text, 400, 400);
        // TTF_DrawRendererText(text2, 100, 200);
        if (mousePos.x > 100 && mousePos.x < 300 && mousePos.y > 100 && mousePos.y < 300)
        {
            SDL_Log("Mouse is inside the rectangle!");
            TTF_SetTextColor(text2, 0, 0, 100, 255);
            TTF_DrawRendererText(text2, 100, 200);
        }
        else
        {
            TTF_SetTextColor(text2, 200, 50, 0, 255);
            TTF_DrawRendererText(text2, 400, 450);
        }
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

        // 更新屏幕
        SDL_RenderPresent(renderer);
    }

    // 清理图片资源
    SDL_DestroyTexture(texture);

    // 清理音乐资源
    Mix_FreeMusic(music);
    Mix_CloseAudio();
    Mix_Quit();

    // 清理字体资源
    SDL_DestroySurface(surface);
    SDL_DestroyTexture(textTexture);
    TTF_CloseFont(font);
    TTF_Quit();

    // 清理并退出
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}