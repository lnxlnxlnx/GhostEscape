cmake_minimum_required(VERSION 3.10.0)
project(GhostEscape VERSION 0.1.0 LANGUAGES C CXX)

# 设置C++标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 设置编译选项
if (MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
    # Linux 下链接 SDL3 可能需要的线程/数学库
    if (UNIX)
        link_libraries(-pthread -lm)
    endif()
endif()

# 设置编译输出目录（建议用 build/ 分离，避免污染源文件）
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/bin)

set(TARGET ${PROJECT_NAME}-${CMAKE_SYSTEM_NAME})

# 手动指定 SDL3 路径（若为手动编译）
# set(SDL3_DIR "/path/to/SDL3/cmake")  # 取消注释并替换路径

# 查找库（确保 .pc 文件或 cmake 配置正确）
find_package(SDL3 REQUIRED)
find_package(SDL3_image REQUIRED)
find_package(SDL3_mixer REQUIRED)
find_package(SDL3_ttf REQUIRED)
find_package(glm REQUIRED)

# 通用源文件
set(SOURCES
    src/core/game.cpp
    src/core/asset_store.cpp
    src/core/object.cpp
    src/core/object_world.cpp
    src/core/object_affiliate.cpp
    src/core/scene.cpp
    src/core/actor.cpp
    src/screen/ui_mouse.cpp
    src/screen/hud_stats.cpp
    src/screen/hud_skill.cpp
    src/screen/hud_text.cpp
    src/screen/hud_button.cpp
    src/raw/stats.cpp
    src/raw/weapon.cpp
    src/raw/timer.cpp
    src/raw/bg_star.cpp
    src/world/effect.cpp
    src/world/spell.cpp
    src/affiliate/sprite.cpp
    src/affiliate/sprite_anim.cpp
    src/affiliate/collider.cpp
    src/affiliate/affiliate_bar.cpp
    src/affiliate/text_label.cpp
    src/spawner.cpp
    src/player.cpp
    src/enemy.cpp
    src/weapon_thunder.cpp
    src/main.cpp
    src/scene_title.cpp
    src/scene_main.cpp
)

# 平台专属文件
if(WIN32)
    list(APPEND SOURCES resources.rc)
elseif(APPLE)
    # macOS 可能需要 Info.plist 或其他资源
    set(MACOSX_BUNDLE TRUE)
    set(MACOSX_BUNDLE_INFO_PLIST ${CMAKE_SOURCE_DIR}/Info.plist)
elseif(UNIX)
    # Linux 无需额外资源文件
endif()

# 生成可执行文件
add_executable(${TARGET} ${SOURCES})

# 链接库（确保目标正确）
target_link_libraries(${TARGET}
    SDL3::SDL3
    SDL3_image::SDL3_image
    SDL3_mixer::SDL3_mixer
    SDL3_ttf::SDL3_ttf
    glm::glm
)

# Windows 隐藏控制台
if (MSVC)
    target_link_options(${TARGET} PRIVATE "/SUBSYSTEM:WINDOWS")
endif()