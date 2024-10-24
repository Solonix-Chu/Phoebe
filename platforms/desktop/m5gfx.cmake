# M5GXF
# https://github.com/lovyan03/LovyanGFX/blob/master/examples_for_PC/CMake_SDL/CMakeLists.txt
add_definitions(-DLGFX_SDL)

# ビルド対象にするファイルを指定する;
# LovyanGFXのあるパスと位置関係を変えた場合は相対パス記述を環境に合わせて調整すること;
file(GLOB Target_Files RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} CONFIGURE_DEPENDS 
    dependencies/M5GFX/src/lgfx/Fonts/efont/*.c
    dependencies/M5GFX/src/lgfx/Fonts/IPA/*.c
    dependencies/M5GFX/src/lgfx/utility/*.c
    dependencies/M5GFX/src/lgfx/v1/*.cpp
    dependencies/M5GFX/src/lgfx/v1/misc/*.cpp
    dependencies/M5GFX/src/lgfx/v1/panel/Panel_Device.cpp
    dependencies/M5GFX/src/lgfx/v1/panel/Panel_FrameBufferBase.cpp
    dependencies/M5GFX/src/lgfx/v1/platforms/sdl/*.cpp
    )
add_library(m5gfx ${Target_Files})

# includeするファイルのパスを指定する;
# LovyanGFXのあるパスと位置関係を変えた場合は相対パス記述を環境に合わせて調整すること;
target_include_directories(m5gfx PUBLIC dependencies/M5GFX/src/)

IF (CMAKE_SYSTEM_NAME MATCHES "Linux")

# Linux環境の場合;
# SDL2_INCLUDE_DIRS と SDL2_LIBRARIES を事前に設定しておく;
    find_package(SDL2 REQUIRED SDL2)
    include_directories(${SDL2_INCLUDE_DIRS})
    target_link_libraries(m5gfx -lpthread ${SDL2_LIBRARIES})

ELSEIF (CMAKE_SYSTEM_NAME MATCHES "Windows")

# Windows環境の場合;
# SDL2を配置したパス内のincludeのパスを指定する;
    target_include_directories(m5gfx PUBLIC "C:/SDL2/include")

# SDL2を配置したパス内の.libファイルのパスを指定する;
    target_link_libraries(m5gfx PUBLIC "C:/SDL2/lib/x64/SDL2.lib")


    add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
    add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
    add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/Zc:__cplusplus>")

ELSEIF (CMAKE_SYSTEM_NAME MATCHES "Darwin")

# MacOS(Darwin)環境の場合;
    find_package(SDL2 REQUIRED COMPONENTS SDL2)
    target_link_libraries(lovyangfx PRIVATE SDL2::SDL2)

ENDIF ()

target_compile_features(m5gfx PUBLIC cxx_std_17)
