cmake_minimum_required(VERSION 3.28)
project(BNW LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)


set(source ${CMAKE_SOURCE_DIR}/assets)
set(destination ${CMAKE_CURRENT_BINARY_DIR}/bin/assets)

message(STATUS ${CMAKE_SOURCE_DIR})
message(STATUS ${CMAKE_CURRENT_BINARY_DIR})

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.1
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

FetchContent_Declare(ImGui
    GIT_REPOSITORY https://github.com/ocornut/imgui
    GIT_TAG v1.91.1
    GIT_SHALLOW ON
)
FetchContent_MakeAvailable(ImGui)

FetchContent_Declare(ImGui_SFML
    GIT_REPOSITORY https://github.com/SFML/imgui-sfml
    GIT_TAG v3.0
    GIT_SHALLOW ON
)
set(IMGUI_DIR ${imgui_SOURCE_DIR})
set(IMGUI_SFML_FIND_SFML OFF)
set(IMGUI_SFML_IMGUI_DEMO ON)
FetchContent_MakeAvailable(ImGui_SFML)

FetchContent_Declare(TGUI
    GIT_REPOSITORY https://github.com/texus/TGUI.git
    GIT_TAG v1.10.0
    GIT_SHALLOW ON
)
set(TGUI_BACKEND SFML_GRAPHICS CACHE STRING "" FORCE)
set(TGUI_BUILD_FRAMEWORK OFF CACHE BOOL "" FORCE)
set(TGUI_USE_STATIC_STD_LIBS OFF CACHE BOOL "" FORCE)
set(TGUI_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(TGUI_BUILD_GUI_BUILDER OFF CACHE BOOL "" FORCE)
set(TGUI_BUILD_TESTS OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(TGUI)

add_executable(main src/main.cpp "src/main.cpp")
target_compile_features(main PRIVATE cxx_std_20)
target_link_libraries(main PRIVATE 
    SFML::Graphics
    SFML::Audio
    ImGui-SFML::ImGui-SFML
    TGUI::TGUI
)

add_custom_target(
  copy_assets ALL
  COMMAND ${CMAKE_COMMAND} -E remove_directory ${destination}
  COMMAND ${CMAKE_COMMAND} -E copy_directory ${source} ${destination}
  COMMENT "Copy assets from ${source} to ${destination}"
)
