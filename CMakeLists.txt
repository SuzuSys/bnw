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

add_executable(main src/main.cpp "src/main.cpp")
target_compile_features(main PRIVATE cxx_std_20)
target_link_libraries(main PRIVATE 
    SFML::Graphics
    SFML::Audio
    ImGui-SFML::ImGui-SFML
)

add_custom_target(
  copy_assets ALL
  COMMAND ${CMAKE_COMMAND} -E copy_directory ${source} ${destination}
  COMMENT "Copy assets from ${source} to ${destination}"
)
