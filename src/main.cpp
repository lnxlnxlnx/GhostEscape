#include <iostream>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_mixer/SDL_mixer.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <glm/glm.hpp>
#include "game.h"

int main(int argc, char *argv[]){
    (void)argc; // 未使用参数，避免编译器警告
    (void)argv; // 未使用参数，避免编译器警告
    auto &game = Game::GetInstance();
    game.init("Ghost Escape", 1280, 720);
    game.run();
    return 0;
}


