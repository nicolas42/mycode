// clang -framework CoreVideo -framework IOKit -framework Cocoa -framework GLUT -framework OpenGL libraylib.a -I raylib/src sobel.c && ./a.out 

#include "raylib.h"
#include "raymath.h"
#include <math.h>
#include <string.h>
#include <stdlib.h>

#define SOBEL_KERNEL_SIZE 3

void sobel_edge_detection(Color* original_image, int width, int height, Color* edge_image) {
    double *grey_image_floats = (double*)calloc(height * width, sizeof(double));
    
    // Convert to grayscale and center around zero
    for (int j = 0; j < height; j++) {
        for (int i = 0; i < width; i++) {
            Color pixel = original_image[j * width + i];
            double v = 0.212671 * pixel.r + 0.715160 * pixel.g + 0.072169 * pixel.b;
            grey_image_floats[j * width + i] = (double)(v - 127.0);  // "centered" around zero
        }
    }

    double *edge_image_floats = (double*)calloc(height * width, sizeof(double));

    // Apply Sobel filters
    for (int j = 1; j < height - 1; j++) {
        for (int i = 1; i < width - 1; i++) {
            int pos = j * width + i;

            // Sobel kernels
            double Gx[9] = { -1, 0, 1, -2, 0, 2, -1, 0, 1 };
            double Gy[9] = { 1, 2, 1, 0, 0, 0, -1, -2, -1 };

            double x = 0, y = 0;
            for (int ky = -1; ky <= 1; ky++) {
                for (int kx = -1; kx <= 1; kx++) {
                    int kernelPos = (ky + 1) * 3 + (kx + 1);
                    x += Gx[kernelPos] * grey_image_floats[pos + ky * width + kx];
                    y += Gy[kernelPos] * grey_image_floats[pos + ky * width + kx];
                }
            }

            edge_image_floats[pos] = sqrt(x * x + y * y);
        }
    }

    // Find min and max to normalize the output
    double minval = edge_image_floats[0];
    double maxval = edge_image_floats[0];
    for (int j = 1; j < height - 1; j++) {
        for (int i = 1; i < width - 1; i++) {
            int pos = j * width + i;
            if (edge_image_floats[pos] < minval) minval = edge_image_floats[pos];
            if (edge_image_floats[pos] > maxval) maxval = edge_image_floats[pos];
        }
    }

    // Convert back to Color format
    for (int j = 1; j < height - 1; j++) {
        for (int i = 1; i < width - 1; i++) {
            int pos = j * width + i;
            uint8_t v = (uint8_t)(255.0 * (edge_image_floats[pos] - minval) / (maxval - minval));
            edge_image[pos] = (Color){v, v, v, 255};
        }
    }

    free(grey_image_floats);
    free(edge_image_floats);
}

int main(void) {
    const int screenWidth = 800;
    const int screenHeight = 800;

    InitWindow(screenWidth, screenHeight, "Sobel Edge Detection with Raylib");

    // Load image
    Image img = LoadImage("valve-original.png");
    if (img.data == NULL) {
        TraceLog(LOG_ERROR, "Failed to load image");
        return 1;
    }

    ImageFormat(&img, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8);                                                     // Convert image data to desired format

    // Convert image to Color array
    Color* original_image = (Color*)img.data;
    Color* edge_image = (Color*)malloc(img.width * img.height * sizeof(Color));
    memcpy(edge_image, original_image, img.width * img.height * sizeof(Color)); // Initialize with original image color

    // Apply Sobel edge detection
    sobel_edge_detection(original_image, img.width, img.height, edge_image);

    // Create textures
    Texture2D textureOriginal = LoadTextureFromImage(img);
    Texture2D textureEdge = LoadTextureFromImage(img);
    UpdateTexture(textureEdge, edge_image);

    SetTargetFPS(60);

    bool showOriginal = true;
    while (!WindowShouldClose()) {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            showOriginal = !showOriginal;
        }

        BeginDrawing();
            ClearBackground(RAYWHITE);
            if (showOriginal) {
                DrawTexture(textureOriginal, 0, 0, WHITE);
            } else {
                DrawTexture(textureEdge, 0, 0, WHITE);
            }
        EndDrawing();
    }

    // Cleanup
    UnloadTexture(textureOriginal);
    UnloadTexture(textureEdge);
    UnloadImage(img);
    free(edge_image);
    CloseWindow();

    return 0;
}