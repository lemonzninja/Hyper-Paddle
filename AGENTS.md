# AGENTS.md

## Project Summary
**Hyper-Paddle** is a retro Pong-like arcade game developed in C using the **Raylib** library.
The project targets Windows (MinGW/MSVC), macOS, and Linux.
It uses **CMake** for build configuration and dependency management (fetching Raylib 5.5).

## Build, Test, and Run

### Prerequisites
- **CMake** 3.11 or higher.
- C Compiler (GCC, Clang, or MSVC).
- **PowerShell** (recommended for Windows commands).

### Build Commands
The project does not use a separate `build/` folder by default in scripts; it uses `cmake-build-debug` for development.

1.  **Configure Project**:
    ```powershell
    cmake -S . -B cmake-build-debug
    ```

2.  **Build Executable**:
    ```powershell
    cmake --build cmake-build-debug --target Hyper-Paddle
    ```

3.  **Run Game**:
    ```powershell
    .\cmake-build-debug\Hyper-Paddle.exe
    ```

4.  **Clean Build** (if needed):
    ```powershell
    cmake --build cmake-build-debug --target clean
    ```

### Testing
**Current Status**: There are **NO automated tests** in this repository.
- Agents should not attempt to run `ctest` or `make test` unless they have implemented tests.
- **Adding Tests**: If instructed to add tests, use `ctest` infrastructure.
    - Create a `tests/` directory.
    - Add `enable_testing()` to `CMakeLists.txt`.
    - Register tests with `add_test()`.
- **Single Test Command** (Hypothetical - for reference only):
    ```powershell
    ctest --test-dir cmake-build-debug -R <TestNameRegex> --verbose
    ```

### Linting and Formatting
- **Linter**: None configured.
- **Formatter**: None configured.
- **Rule**: Strict manual adherence to the existing style is required. Do not reformat existing code unless modifying it.

## Code Style & Conventions

### General C Guidelines
- **Standard**: C99/C11.
- **Extensions**: Avoid compiler-specific extensions unless wrapped in macros.
- **Safety**:
    - Use `snprintf` instead of `sprintf`.
    - Check pointers before use if they can be NULL.
    - Initialize variables (especially pointers and structs).

### Naming Conventions
- **Files**: `PascalCase` (e.g., `GameManager.c`, `Ball.h`). Match source and header names.
- **Functions**: `PascalCase` (e.g., `InitBall`, `UpdateGame`).
    - Private/Static functions: `PascalCase` or `lower_snake_case` (be consistent with file).
- **Variables**: `camelCase` (e.g., `ballSpeed`, `playerScore`).
- **Structs/Enums**: `PascalCase` (e.g., `Ball`, `GameScreen`).
- **Enum Members**: `UPPER_SNAKE_CASE` with prefix (e.g., `SCREEN_LOGO`, `BALL_GOAL_LEFT`).
- **Macros/Constants**: `UPPER_SNAKE_CASE` (e.g., `SCREEN_WIDTH`).

### Formatting Rules
- **Indentation**: 4 spaces. **NO TABS**.
- **Braces**: K&R / 1TBS style (opening brace on the same line).
    ```c
    void UpdateBall(Ball *ball) {
        if (ball->x > 100) {
            // ...
        }
    }
    ```
- **Spacing**:
    - Space after control keywords (`if`, `while`, `for`, `switch`).
    - Space around binary operators (`=`, `+`, `==`).
    - No space between function name and parenthesis.

### File Structure
- **Headers (`.h`)**:
    - Must use include guards: `#ifndef PROJECT_PATH_FILE_H` / `#define ...`.
    - Include necessary dependencies (e.g., `raylib.h`).
    - Declare public structs and functions.
- **Sources (`.c`)**:
    - Include the corresponding header first.
    - Use `static` for internal helper functions and file-scope global variables.
- **Directories**:
    - `src/`: Implementation files.
    - `include/`: Header files (mirrors `src/` structure).
    - `assets/`: Runtime assets.

## Architecture & Raylib Usage

### Game Loop
- Controlled in `src/main.c`.
- `InitGame()` -> `UpdateDrawFrame()` loop -> `Unload()`.
- **Update**: Logic only. Update positions, states, input.
- **Draw**: Rendering only. Must be inside `BeginDrawing()` / `EndDrawing()`.

### Screen Management
- The game uses a `ScreenManager` (`src/Screens/screen_manager.c`).
- Screens are defined in `src/Screens/screens.h`.
- To add a new screen:
    1. Create `src/Screens/screen_new.c`.
    2. Define `Init`, `Update`, `Draw`, `Unload` functions.
    3. Register it in `screen_manager.c`.
    4. Add to `CMakeLists.txt`.

### Game Objects
- Entities like `Ball` and `Paddle` are structs with their own Init/Update/Draw functions.
- Pass pointers to these objects to avoid copying large structs.
- Use `Vector2` (Raylib) for positions/velocities.

### CMake Management
- **CRITICAL**: When adding a new `.c` file, you **MUST** add it to the `add_executable` list in `CMakeLists.txt`.
- The build system does not use globs; files are listed explicitly.

### Resource Management
- **Loading**: Load assets (Textures, Sounds) in `Init` functions.
- **Unloading**: Always call `UnloadTexture` / `UnloadSound` in the corresponding `Unload` function to prevent memory leaks.
- **Path**: Assets are loaded from `assets/`. The build copies this folder next to the executable.

## Development Workflow for Agents
1.  **Explore**: Read `src/main.c` and `CMakeLists.txt` first to ground yourself in the project structure.
2.  **Plan**: Identify which module (GameObject, System, Screen) needs modification. State your plan clearly.
3.  **Edit**:
    - If modifying existing code: Preserve style strictly.
    - If adding new files: Create file -> Add to CMake -> Build.
4.  **Verify**:
    - Run `cmake --build cmake-build-debug --target Hyper-Paddle`.
    - Fix any compilation errors immediately.
    - Since there are no tests, visual verification/logic review is key.
5.  **Commit**: Create a concise commit message describing the "why" and "what".

## Rules Sources
- `.cursor/rules/`: *None found.*
- `.cursorrules`: *None found.*
- `.github/copilot-instructions.md`: *None found.*
