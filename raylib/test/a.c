#include "raylib.h"
#include <string.h>

#define MAX_TEXT_LENGTH 1024

int main(void) {
    // Initialization
    const int screenWidth = 800;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "Simple Text Editor");
    SetTargetFPS(60);

    char text[MAX_TEXT_LENGTH] = ""; // Store the editable text
    int textLength = 0;             // Current length of the text
    bool hasFocus = true;           // Focus for editing

    while (!WindowShouldClose()) {
        // Input handling
        if (hasFocus) {
            int key = GetCharPressed();

            // Handle character input
            while (key > 0) {
                if (textLength < MAX_TEXT_LENGTH - 1) {
                    text[textLength++] = (char)key;
                    text[textLength] = '\0';
                }
                key = GetCharPressed();
            }

            // Handle backspace
            if (IsKeyPressed(KEY_BACKSPACE) && textLength > 0) {
                text[--textLength] = '\0';
            }
        }

        // Draw the interface
        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawText("Simple Text Editor", 10, 10, 20, GRAY);
        DrawRectangle(10, 50, screenWidth - 20, screenHeight - 100, LIGHTGRAY);
        DrawRectangleLines(10, 50, screenWidth - 20, screenHeight - 100, DARKGRAY);
        DrawText(text, 15, 55, 20, BLACK);

        if (!hasFocus) {
            DrawText("Click to focus", 15, 55 + 30, 20, DARKGRAY);
        }

        EndDrawing();

        // Handle focus by clicking the editor area
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            Vector2 mouse = GetMousePosition();
            hasFocus = CheckCollisionPointRec(mouse, (Rectangle){10, 50, screenWidth - 20, screenHeight - 100});
        }
    }

    // Cleanup
    CloseWindow();

    return 0;
}
