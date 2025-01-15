/*******************************************************************************************
*   raygui + raylib: Simple Menu Bar Demo
*
*   Compile example (macOS):
*       clang -o menubar menubar_demo.c -I/path/to/raylib/include -I/path/to/raygui \
*             -L/path/to/raylib/lib -lraylib -framework Cocoa -framework IOKit -framework OpenGL
*
*   On Windows (using MinGW as an example):
*       gcc -o menubar menubar_demo.c -I.\raylib\include -I.\raygui \
*           -L.\raylib\lib -lraylib -lopengl32 -lgdi32 -lwinmm
********************************************************************************************/

#include "raylib.h"

// Include raygui just after raylib
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

int main(void)
{
    // Initialization
    const int screenWidth = 800;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "raygui: Simple Menu Bar Demo");
    SetTargetFPS(60);

    // Variables to track which panel is active
    bool showInfo = false;
    bool showSettings = false;
    bool showHelp = false;

    while (!WindowShouldClose())    // Main game loop
    {
        //----------------------------------------------------------------------------------
        // Update: Handle menu button clicks
        //----------------------------------------------------------------------------------
        // We'll handle the button logic in one pass, then draw them in BeginDrawing().
        if (GuiButton((Rectangle){ 10, 10, 60, 30 }, "Info")) {
            showInfo = true;
            showSettings = false;
            showHelp = false;
        }
        if (GuiButton((Rectangle){ 80, 10, 80, 30 }, "Settings")) {
            showInfo = false;
            showSettings = true;
            showHelp = false;
        }
        if (GuiButton((Rectangle){ 170, 10, 60, 30 }, "Help")) {
            showInfo = false;
            showSettings = false;
            showHelp = true;
        }

        //----------------------------------------------------------------------------------
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
            ClearBackground(RAYWHITE);

            // Draw a rectangle for the top "menu bar" background
            DrawRectangle(0, 0, screenWidth, 50, LIGHTGRAY);

            // We already triggered button logic above, but immediate-mode expects
            // we call them each frame for consistent styling/hover states. 
            // (This effectively re-draws the same three buttons.)
            GuiButton((Rectangle){ 10, 10, 60, 30 }, "Info");
            GuiButton((Rectangle){ 80, 10, 80, 30 }, "Settings");
            GuiButton((Rectangle){ 170, 10, 60, 30 }, "Help");

            // Show the currently active panel
            if (showInfo) {
                DrawText("INFO PANEL: You clicked Info!", 20, 70, 20, BLACK);
                DrawText("- Here you might show application details", 20, 100, 18, DARKGRAY);
            }
            else if (showSettings) {
                DrawText("SETTINGS PANEL: Configure your stuff here!", 20, 70, 20, BLACK);
                DrawText("- Possible config sliders, checkboxes, etc.", 20, 100, 18, DARKGRAY);
            }
            else if (showHelp) {
                DrawText("HELP PANEL: Show instructions here.", 20, 70, 20, BLACK);
                DrawText("- e.g. how to navigate, usage tips...", 20, 100, 18, DARKGRAY);
            }
            else {
                DrawText("Please select an option from the menu bar above.", 20, 70, 20, DARKGRAY);
            }

        EndDrawing();
    }

    CloseWindow();  // De-initialize
    return 0;
}
