cmake_minimum_required(VERSION 3.11) # FetchContent is available in 3.11+
project(Hyper-Paddle)

# Generate compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Dependencies
set(RAYLIB_VERSION 5.5)
find_package(raylib ${RAYLIB_VERSION} QUIET) # QUIET or REQUIRED
if (NOT raylib_FOUND) # If there's none, fetch and build raylib
  include(FetchContent)
  FetchContent_Declare(
    raylib
    DOWNLOAD_EXTRACT_TIMESTAMP OFF
    URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
  )
  FetchContent_GetProperties(raylib)
  if (NOT raylib_POPULATED) # Have we downloaded raylib yet?
    set(FETCHCONTENT_QUIET NO)
    FetchContent_MakeAvailable(raylib)
    set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
  endif()
endif()

# Our Project

add_executable(${PROJECT_NAME} src/main.c
        src/Screens/screens.h
        src/Screens/screen_logo.c
        src/Screens/screen_manager.c
        src/Screens/screen_menu.c
        include/UI/UIButton/button.h
        src/UI/UIButton/button.c
        src/Screens/screen_main_game.c
        include/GameObjects/Paddle/Paddle.h
        src/GameObjects/Paddle/Paddle.c
        src/GameManager/Game_Manager.h
        src/GameManager/Main_Game.c
        include/Systems/deltaTime.h
        include/Systems/KeybordManager/KeybordManager.h
        src/Systems/KeybordManager.c
        src/Systems/deltaTime.c
        include/GameObjects/Ball/Ball.h
        src/GameObjects/Ball/Ball.c
)
# Ensure project headers under include/ are discoverable
target_include_directories(${PROJECT_NAME} PRIVATE include)
#set(raylib_VERBOSE 1)
target_link_libraries(${PROJECT_NAME} raylib)

# Copy assets to build directory
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:${PROJECT_NAME}>/assets)

# Web Configurations
if (${PLATFORM} STREQUAL "Web")
    set_target_properties(${PROJECT_NAME} PROPERTIES SUFFIX ".html") # Tell Emscripten to build an example.html file.
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -s USE_GLFW=3 -s ASSERTIONS=1 -s WASM=1 -s ASYNCIFY -s GL_ENABLE_GET_PROC_ADDRESS=1")
endif()

# Checks if OSX and links appropriate frameworks (Only required on MacOS)
if (APPLE)
    target_link_libraries(${PROJECT_NAME} "-framework IOKit")
    target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
    target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
endif()
