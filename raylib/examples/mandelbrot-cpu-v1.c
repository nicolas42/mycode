/*******************************************************************************************
*
*   Minimal Mandelbrot Viewer in raylib (CPU-based)
*
*   This code:
*   1) Calculates a static Mandelbrot image on the CPU.
*   2) Displays that image in a window.
*
*   No zooming, no panning. Just a basic image.
*
*   Compile example (Linux):
*       gcc main.c -o main -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
*
********************************************************************************************/

#include "raylib.h"
#include <math.h>    // for fabsf, fminf, etc.

// Helper function to quickly map iteration count to a color
static Color GetMandelbrotColor(int iteration, int maxIter)
{
    if (iteration >= maxIter) {
        // Inside the set: black
        return BLACK;
    } else {
        // Outside the set: simple coloring (grayscale)
        int c = 255 * iteration / maxIter;
        return (Color){ c, c, c, 255 };
    }
}

int main(void)
{
    // Window dimensions
    const int screenWidth  = 800;
    const int screenHeight = 600;

    // Initialize raylib window
    InitWindow(screenWidth, screenHeight, "Mandelbrot - Minimal CPU Example");

    // Define our region in the complex plane:
    // Typically, the Mandelbrot set is nicely viewed from:
    //   Real axis (x) range: [-2.5, 1.0]
    //   Imag axis (y) range: [-1.0, 1.0]
    // We'll keep that aspect ratio with our 800x600 window.
    double minReal = -2.5;
    double maxReal = 1.0;
    double minImag = -1.0;
    // We figure out maxImag so that the aspect ratio matches our screen.
    double realRange = maxReal - minReal;
    double imagRange = realRange * (double)screenHeight / (double)screenWidth;
    double maxImag = minImag + imagRange;

    // Mandelbrot iteration parameters
    int maxIter = 256;

    // Create an empty Image to hold the pixels
    Image mandelbrotImage = GenImageColor(screenWidth, screenHeight, BLACK);
    Color *pixels = (Color *)mandelbrotImage.data; // Access raw pixel data

    // Calculate the Mandelbrot set, store in `pixels`
    for (int py = 0; py < screenHeight; py++)
    {
        // Map pixel Y to imaginary coordinate
        double imagCoord = minImag + ((double)py / (screenHeight - 1)) * (maxImag - minImag);

        for (int px = 0; px < screenWidth; px++)
        {
            // Map pixel X to real coordinate
            double realCoord = minReal + ((double)px / (screenWidth - 1)) * (maxReal - minReal);

            // Start z = 0
            double zReal = 0.0;
            double zImag = 0.0;
            int iteration = 0;

            // Mandelbrot iteration: z = z^2 + c
            while (iteration < maxIter)
            {
                // z^2 = (zReal + i zImag)^2 = zReal^2 - zImag^2 + 2i zReal zImag
                double zReal2 = zReal*zReal - zImag*zImag + realCoord;
                double zImag2 = 2.0*zReal*zImag + imagCoord;
                zReal = zReal2;
                zImag = zImag2;

                // If magnitude of z is large (e.g. > 2), we assume it will diverge
                if ((zReal*zReal + zImag*zImag) > 4.0) break;

                iteration++;
            }

            // Choose a color based on how many iterations we took
            pixels[py*screenWidth + px] = GetMandelbrotColor(iteration, maxIter);
        }
    }

    // Convert the Image into a Texture
    Texture2D mandelbrotTexture = LoadTextureFromImage(mandelbrotImage);

    // Unload the image from CPU, not needed anymore after we have the texture
    UnloadImage(mandelbrotImage);

    SetTargetFPS(60);

    // Main loop
    while (!WindowShouldClose())
    {
        BeginDrawing();
            ClearBackground(BLACK);

            // Draw the entire Mandelbrot texture at (0,0)
            DrawTexture(mandelbrotTexture, 0, 0, WHITE);

            // Simple instructions on screen
            DrawText("Minimal Mandelbrot (CPU)", 10, 10, 20, YELLOW);
            DrawText("No zoom/pan. Close window to exit.", 10, 40, 20, RAYWHITE);

        EndDrawing();
    }

    // Cleanup
    UnloadTexture(mandelbrotTexture);
    CloseWindow();

    return 0;
}
