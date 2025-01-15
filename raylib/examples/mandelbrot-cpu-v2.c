/*******************************************************************************************
*
*   CPU-based Mandelbrot Viewer with Zoom & Pan (adapted from your JS code)
*
*   Controls:
*     - Left Mouse Click: Recenter on click point & Zoom In (×2)
*     - Right Mouse Click: Recenter on click point & Zoom Out (÷2)
*
*   NOTE:
*     - This recalculates the entire fractal on every click, which can be slow
*       for large windows or very high iterations.
*     - No continuous drag-pan is included; it simply repositions to the clicked point,
*       just like your JavaScript snippet.
*
*   Compilation (Linux example):
*       gcc main.c -o mandelbrot -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
*
********************************************************************************************/

#include "raylib.h"
#include <math.h>   // For fmodf, etc.
#include <stdio.h>  // For printf, etc>
#include <stdbool.h>

//----------------------------------------------------------------------------------
// Helper: hue2rgb (used by HSLToRGB), mimicking the JS logic
//----------------------------------------------------------------------------------
static float hue2rgb(float p, float q, float t)
{
    if (t < 0.0f) t += 1.0f;
    if (t > 1.0f) t -= 1.0f;
    if (t < 1.0f/6.0f) return p + (q - p) * 6.0f * t;
    if (t < 1.0f/2.0f) return q;
    if (t < 2.0f/3.0f) return p + (q - p) * (2.0f/3.0f - t) * 6.0f;
    return p;
}

//----------------------------------------------------------------------------------
// Convert HSL to RGB (replicating the JavaScript hsl_to_rgb)
//   - h, s, l in [0..1]
//----------------------------------------------------------------------------------
static Color HSLToRGB(float h, float s, float l)
{
    float r, g, b;
    if (s == 0.0f)
    {
        // Achromatic (gray)
        r = g = b = 1.0f;
    }
    else
    {
        float q = (l < 0.5f) ? (l * (1.0f + s)) : (l + s - l * s);
        float p = 2.0f * l - q;
        r = hue2rgb(p, q, h + 1.0f/3.0f);
        g = hue2rgb(p, q, h);
        b = hue2rgb(p, q, h - 1.0f/3.0f);
    }

    return (Color){
        (unsigned char)(r * 255.0f),
        (unsigned char)(g * 255.0f),
        (unsigned char)(b * 255.0f),
        255
    };
}

//----------------------------------------------------------------------------------
// Holds our Mandelbrot parameters
//----------------------------------------------------------------------------------
typedef struct Mandelbrot {
    double x;       // Center X in mandelbrot space
    double y;       // Center Y in mandelbrot space
    double zoom;    // Zoom factor
    int maxIter;    // Max iterations
} Mandelbrot;

//----------------------------------------------------------------------------------
// Convert a screen (pixel) coordinate to a complex-plane coordinate
//   - This matches your JS function pixel_coordinates_to_mandelbrot_coordinate
//----------------------------------------------------------------------------------
static Vector2 PixelToMandelbrotCoord(int px, int py, int width, int height, const Mandelbrot *mb)
{
    float aspectRatio = (float)width / (float)height;

    // offset_x = ( x - (width/2) ) / (width/2) * (2 / zoom)
    float offsetX = (float)(px - width/2) / (width/2.0f) * (2.0f / (float)mb->zoom);

    // offset_y = ( y - (height/2) ) / (height/2) * (2 / zoom) / aspectRatio
    float offsetY = (float)(py - height/2) / (height/2.0f) * (2.0f / (float)mb->zoom) / aspectRatio;

    float cx = (float)mb->x + offsetX;
    float cy = (float)mb->y + offsetY;
    return (Vector2){ cx, cy };
}

//----------------------------------------------------------------------------------
// Generate a CPU-based Mandelbrot image using the same coloring logic
//   - If in set: black
//   - Else: color = HSL((numIter % 255)/255, 1.0, 0.5)
//----------------------------------------------------------------------------------
static Image GenMandelbrotImage(int width, int height, const Mandelbrot *mb)
{
    Image image = GenImageColor(width, height, BLACK);  // RGBA8
    Color *pixels = (Color *)image.data;

    for (int py = 0; py < height; py++)
    {
        for (int px = 0; px < width; px++)
        {
            // Convert (px, py) -> (cx, cy) in the fractal
            Vector2 c = PixelToMandelbrotCoord(px, py, width, height, mb);

            double zx = 0.0;
            double zy = 0.0;

            bool inSet = true;
            int numIterations = 0;
            for (; numIterations < mb->maxIter; numIterations++)
            {
                double zxTemp = zx * zx - zy * zy + c.x;
                zy = 2.0 * zx * zy + c.y;
                zx = zxTemp;

                if ((zx * zx + zy * zy) > 4.0)
                {
                    inSet = false;
                    break;
                }
            }

            int idx = py * width + px;

            if (inSet)
            {
                // Inside the set -> black
                pixels[idx] = (Color){ 0, 0, 0, 255 };
            }
            else
            {
                // same as in JS: hue = (num_iterations % 255)/255, s=1, l=0.5
                float hue = (float)(numIterations % 255) / 255.0f;
                Color col = HSLToRGB(hue, 1.0f, 0.5f);
                pixels[idx] = col;
            }
        }
    }

    return image;
}

int main(void)
{
    // Window size
    const int screenWidth = 800;
    const int screenHeight = 600;

    // Initialize raylib window
    InitWindow(screenWidth, screenHeight, "Mandelbrot - CPU (Click to Zoom In/Out)");

    // Mandelbrot parameters (you can customize these defaults)
    Mandelbrot mandel = {
        .x = 0.0,
        .y = 0.0,
        .zoom = 1.0,
        .maxIter = 1000
    };

    // Generate the initial fractal image
    Image mandelImage = GenMandelbrotImage(screenWidth, screenHeight, &mandel);
    Texture2D mandelTexture = LoadTextureFromImage(mandelImage);
    UnloadImage(mandelImage);

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        // Left-click = recenter & zoom in
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            Vector2 mp = GetMousePosition();
            Vector2 c = PixelToMandelbrotCoord((int)mp.x, (int)mp.y, screenWidth, screenHeight, &mandel);
            mandel.x = c.x;
            mandel.y = c.y;
            mandel.zoom *= 2.0;

            // Recalculate fractal
            UnloadTexture(mandelTexture);
            Image newImage = GenMandelbrotImage(screenWidth, screenHeight, &mandel);
            mandelTexture = LoadTextureFromImage(newImage);
            UnloadImage(newImage);
        }

        // Right-click = recenter & zoom out
        if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON))
        {
            Vector2 mp = GetMousePosition();
            Vector2 c = PixelToMandelbrotCoord((int)mp.x, (int)mp.y, screenWidth, screenHeight, &mandel);
            mandel.x = c.x;
            mandel.y = c.y;
            mandel.zoom /= 2.0;

            // Recalculate fractal
            UnloadTexture(mandelTexture);
            Image newImage = GenMandelbrotImage(screenWidth, screenHeight, &mandel);
            mandelTexture = LoadTextureFromImage(newImage);
            UnloadImage(newImage);
        }

        BeginDrawing();
            ClearBackground(BLACK);

            // Draw the mandelbrot texture
            DrawTexture(mandelTexture, 0, 0, WHITE);

            // Some info
            DrawText("Left click to zoom in, right click to zoom out", 10, 10, 20, RAYWHITE);
            DrawText(TextFormat("Center: (%.9g, %.9g)", mandel.x, mandel.y), 10, 40, 20, GRAY);
            DrawText(TextFormat("Zoom: %.3f", mandel.zoom), 10, 70, 20, GRAY);
        EndDrawing();
    }

    // Cleanup
    UnloadTexture(mandelTexture);
    CloseWindow();

    return 0;
}
