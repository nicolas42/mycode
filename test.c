#include "raylib.h"

int main() {
    InitWindow(800, 450, "raylib [core] example - basic window");
    
    SetTargetFPS(60);
    
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Hello, World!", 190, 200, 20, LIGHTGRAY);
        EndDrawing();
    }
    
    CloseWindow();
    return 0;
}
