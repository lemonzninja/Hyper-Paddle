# Project Guidelines
    
Project Overview
Hyper-Paddle is a small retro arcade game (a Pong-like clone) written in C using the Raylib library. The project is organized into clear modules:
•
GameObjects (e.g., Ball, Paddle)
•
Systems (e.g., keyboard input)
•
GameManager (game loop, orchestration)
It builds as a single executable target: Hyper-Paddle, linking to raylib (and glfw where applicable).
Repository Structure (high level)
•
src/
◦
main.c — entry point
◦
GameManager/ — core game management and loop
◦
GameObjects/
▪
Ball/ — ball logic (Ball.c)
▪
Paddle/ — paddle logic (Paddle.c)
◦
Systems/ — input and other systems (e.g., KeybordManager.c)
•
include/ — public headers mirroring the src layout (e.g., Ball.h, Paddle.h, KeybordManager.h)
•
.junie/ — Junie automation and project guidelines
•
CMake files — project build configuration
Build and Run
•
Do not create new CMake build directories. Always use the CLion-configured active profile.
•
Prefer building specific targets.
•
Active profile: Debug
◦
Build directory: E:\Projects\CodingProjects\RayLib-Projects\Games\Retro-Clones\Hyper-Paddle\cmake-build-debug
◦
Toolchain kind: local MinGW
•
Available CMake targets:
◦
Hyper-Paddle (executable)
◦
raylib (library)
◦
glfw
◦
update_mappings
◦
uninstall
Recommended build commands (Junie should use the workspace helper):
# Build the main game executable
bash_with_cmake_profile "cmake --build E:\Projects\CodingProjects\RayLib-Projects\Games\Retro-Clones\Hyper-Paddle\cmake-build-debug --target Hyper-Paddle"

# Run the built game (adjust path if CLion uses a different configuration)
bash_with_cmake_profile "& 'E:\\Projects\\CodingProjects\\RayLib-Projects\\Games\\Retro-Clones\\Hyper-Paddle\\cmake-build-debug\\Hyper-Paddle.exe'"
Notes:
•
Use Windows PowerShell-compatible paths and quoting.
•
If you need to build a dependency explicitly: repl
ace the target name in the command with raylib or glfw.
Testing
•
There are currently no automated tests defined for this project.
•
If a test target is added later, prefer building that specific target and running it in a single command via bash_with_cmake_profile.
Coding Style and Conventions
•
Language: C (C11/C99 idioms depending on compiler flags).
•
Headers live under include/, source in src/, with matching folder names.
•
Keep module boundaries clear (e.g., GameObjects/Ball exposes its API via include/GameObjects/Ball/Ball.h).
•
Favor small, single-responsibility functions and keep game-loop logic in the GameManager.
•
Naming: use descriptive names; keep file and directory names consistent (Paddle.c ↔ Paddle.h).
How Junie Should Work With This Project
•
Exploration:
◦
Use search_project to find symbols, filenames, or exact text; keep queries short (1–2 words).
◦
Use get_file_structure to understand file contents before opening.
◦
Use open to view specific sections of files (avoid opening entire large files unless necessary).
•
Building/Running:
◦
Always use bash_with_cmake_profile for building and running artifacts.
◦
Do not create or switch to new build directories.
◦
Prefer target-specific builds (e.g., --target Hyper-Paddle).
•
Constraints:
◦
Do not run interactive tools (like vim).
◦
When providing changes, output diffs or file snippets for a human to apply; do not attempt to create/modify files directly if in read-only mode.
Troubleshooting
•
If the executable fails to run, verify that Raylib and GLFW targets were built without errors.
•
Ensure the run path matches your active CLion profile’s build directory.
•
If build errors mention missing headers, verify the include directory structure mirrors src and that CMake includes the correct include paths.
