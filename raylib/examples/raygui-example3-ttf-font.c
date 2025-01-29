#include "raylib.h"

// Include raygui
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

#define FONT_PATH "fonts/Roboto-Medium.ttf"

int main(void)
{
    const int screenWidth = 800;
    const int screenHeight = 600;
    InitWindow(screenWidth, screenHeight, "raygui scaling + custom font");
    SetTargetFPS(60);

    // 1) Load a custom TTF font at size 32
    Font myFont = LoadFontEx(FONT_PATH, 100, NULL, 0);
    SetTextureFilter(myFont.texture, TEXTURE_FILTER_TRILINEAR); // also bilinear
    
    // 2) Tell raygui to use that font
    GuiSetFont(myFont);

    // 3) Optionally set style for default text size (if the TTF is designed smaller/larger than expected).
    //    Note: The actual rendering size also depends on how the TTF was loaded.
    GuiSetStyle(DEFAULT, TEXT_SIZE, 32);

    // For demonstration, a bigger rectangle for a button
    Rectangle bigButtonRect = { 50, 100, 300, 80 };

    while (!WindowShouldClose())
    {
        BeginDrawing();
            ClearBackground(RAYWHITE);

            // Button using the bigger rectangle (80px high)
            if (GuiButton(bigButtonRect, "BIG BUTTON")) {
                // ...
            }

            DrawTextEx(myFont, "Hello with a bigger font!", (Vector2){50,50}, 32,2, BLACK);
            DrawTextEx(myFont, "Hello with a bigger font!", (Vector2){50,500}, 32,2, BLACK);	    
	    // DrawTextEx(myFont, "Hello!", (Vector2){50, 50}, 32, 2, RAYWHITE);
	    
        EndDrawing();
    }

    // Unload the font
    UnloadFont(myFont);
    CloseWindow();
    return 0;
}
