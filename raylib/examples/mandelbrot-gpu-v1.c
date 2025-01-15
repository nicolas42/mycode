#include "raylib.h"
#include <stdlib.h> // For NULL definition

/*******************************************************************************************
*
*   Minimal raylib + GLSL example (self-contained, single file)
*   - Draws a Mandelbrot set using a fragment shader
*   - Uses OpenGL 3.3 and #version 330 core
*
********************************************************************************************/

const char *fragmentShaderCode = 
    "#version 330 core\n"
    "in vec2 fragTexCoord;\n"
    "out vec4 finalColor;\n"
    "uniform vec2 resolution;\n"
    "\n"
    "void main()\n"
    "{\n"
    "    // Normalize coordinates to range [-2.0, 1.0] x [-1.0, 1.0]\n"
    "    vec2 c = vec2(\n"
    "        (fragTexCoord.x * resolution.x / resolution.y - 1.5),\n"
    "        (fragTexCoord.y - 0.5) * 2.0\n"
    "    );\n"
    "\n"
    "    vec2 z = vec2(0.0);\n"
    "    int maxIterations = 1000;\n"
    "    int iterations = 0;\n"
    "\n"
    "    while (dot(z, z) < 4.0 && iterations < maxIterations)\n"
    "    {\n"
    "        z = vec2(z.x * z.x - z.y * z.y, 2.0 * z.x * z.y) + c;\n"
    "        iterations++;\n"
    "    }\n"
    "\n"
    "    // Color based on iterations (gradient from black to white)\n"
    "    float colorValue = float(iterations) / float(maxIterations);\n"
    "    finalColor = vec4(vec3(colorValue), 1.0);\n"
    "}\n";

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth  = 800;
    const int screenHeight = 450;

    SetConfigFlags(FLAG_MSAA_4X_HINT);  // Enable MSAA (if available)
    InitWindow(screenWidth, screenHeight, "raylib + GLSL Mandelbrot example");

    // Load shader from embedded GLSL code
    Shader mandelbrotShader = LoadShaderFromMemory(NULL, fragmentShaderCode);
    int resolutionLoc = GetShaderLocation(mandelbrotShader, "resolution");

    Vector2 resolution = { (float)screenWidth, (float)screenHeight };
    SetShaderValue(mandelbrotShader, resolutionLoc, &resolution, SHADER_UNIFORM_VEC2);

    SetTargetFPS(60); // Limit to 60 frames per second
    //--------------------------------------------------------------------------------------

    // Main loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
            ClearBackground(RAYWHITE);

            BeginShaderMode(mandelbrotShader);
                DrawRectangle(0, 0, screenWidth, screenHeight, WHITE);
            EndShaderMode();

            DrawText("Mandelbrot Set (GLSL)", 10, 10, 20, DARKGRAY);
        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-initialization
    //--------------------------------------------------------------------------------------
    UnloadShader(mandelbrotShader); // Unload shader
    CloseWindow();             // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
