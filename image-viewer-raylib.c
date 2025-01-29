// clang -framework CoreVideo -framework IOKit -framework Cocoa -framework GLUT -framework OpenGL libraylib.a -Iraylib/src ../image-viewer-raylib.c
// ./a.out <dirr>
// deep reads a directory for images. 

#include "raylib.h"
#include "raymath.h"
#include <dirent.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_FILES 1000
#define MAX_FILE_NAME_LENGTH 256
#define MAX_PATH_LENGTH 1024

// Function to check if file is an image
bool is_image_file(const char* file) {
    const char* extensions[] = {".png", ".jpg", ".jpeg", ".gif", ".bmp", ".tiff"};
    for (int i = 0; i < sizeof(extensions) / sizeof(extensions[0]); ++i) {
        if (strstr(file, extensions[i])) return true;
    }
    return false;
}

// Load all image files from a directory
int load_images_from_directory(const char* directory, char images[MAX_FILES][MAX_FILE_NAME_LENGTH]) {
    DIR *dir;
    struct dirent *ent;
    int file_count = 0;

    if ((dir = opendir(directory)) != NULL) {
        while ((ent = readdir(dir)) != NULL && file_count < MAX_FILES) {
            if (is_image_file(ent->d_name)) {
                snprintf(images[file_count], MAX_FILE_NAME_LENGTH, "%s/%s", directory, ent->d_name);
                file_count++;
            }
        }
        closedir(dir);
    } else {
        fprintf(stderr, "Could not open directory: %s\n", directory);
        return 0;
    }
    return file_count;
}


// Helper function to check if a path is a directory
bool is_directory(const char *path) {
    DIR* dir = opendir(path);
    if (dir != NULL) {
        closedir(dir);
        return true;
    }
    return false;
}

// Recursive function to load images from directories
int load_images_recursively(const char* directory, char images[MAX_FILES][MAX_FILE_NAME_LENGTH], int index) {
    DIR *dir;
    struct dirent *ent;
    char path[MAX_PATH_LENGTH];

    if ((dir = opendir(directory)) == NULL) {
        fprintf(stderr, "Could not open directory: %s\n", directory);
        return index;
    }

    // First, process all files in the current directory
    while ((ent = readdir(dir)) != NULL && index < MAX_FILES) {
        if (strcmp(ent->d_name, ".") != 0 && strcmp(ent->d_name, "..") != 0) {
            snprintf(path, sizeof(path), "%s/%s", directory, ent->d_name);
            
            if (!is_directory(path) && is_image_file(ent->d_name)) {
                snprintf(images[index], MAX_FILE_NAME_LENGTH, "%s", path);
                index++;
            }
        }
    }

    // Reset directory stream to start from the beginning
    rewinddir(dir);

    // Now handle subdirectories
    while ((ent = readdir(dir)) != NULL && index < MAX_FILES) {
        if (strcmp(ent->d_name, ".") != 0 && strcmp(ent->d_name, "..") != 0) {
            snprintf(path, sizeof(path), "%s/%s", directory, ent->d_name);
            
            if (is_directory(path)) {
                index = load_images_recursively(path, images, index); // Recursively go into subdirectories
            }
        }
    }

    closedir(dir);
    return index;
}


// Constants for key repeat
#define KEY_REPEAT_DELAY 0.5f // Delay before key starts repeating in seconds
#define KEY_REPEAT_INTERVAL 0.01f // Interval between repeats in seconds

int main(int argc, char *argv[]) {
    const int screenWidth = 800;
    const int screenHeight = 600;

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(screenWidth, screenHeight, "Image Display");

    SetTargetFPS(60);

    if (argc < 2) {
        fprintf(stderr, "Usage: %s <directory_path>\n", argv[0]);
        return 1;
    }
    char *directory = argv[1];  // Directory path passed as the first argument
    // char directory[] = ".";  // Current directory for simplicity


    char images[MAX_FILES][MAX_FILE_NAME_LENGTH];
    int imageCount = load_images_recursively(directory, images, 0);
    if (imageCount == 0) {
        fprintf(stderr, "No images found in the directory or its subdirectories.\n");
        return 1;
    }

    int currentImageIndex = 0;
    Image img = LoadImage(images[currentImageIndex]);
    Texture2D texture = LoadTextureFromImage(img);
    UnloadImage(img); // Unload image data after loading into texture

    bool fullSize = true;
    float zoomScale = 1.0f;
    Vector2 imageOffset = {0, 0};

    // Variables for handling key repeat
    float keyRepeatTimer = 0.0f;
    bool keyRepeatStarted = false;

    while (!WindowShouldClose()) {
        float deltaTime = GetFrameTime(); // Time since last frame

        // Check for key press or key repeat
        if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_J)) {
            if (!keyRepeatStarted) {
                // First press or after release
                keyRepeatTimer = KEY_REPEAT_DELAY;
                keyRepeatStarted = true;
            } else {
                keyRepeatTimer -= deltaTime;
                if (keyRepeatTimer <= 0.0f) {
                    // Time to repeat the action
                    keyRepeatTimer = KEY_REPEAT_INTERVAL;
                    currentImageIndex = (currentImageIndex + 1) % imageCount;
                    UnloadTexture(texture);
                    img = LoadImage(images[currentImageIndex]);
                    texture = LoadTextureFromImage(img);
                    UnloadImage(img);
                    zoomScale = 1.0f;
                    imageOffset.x = imageOffset.y = 0;
                }
            }
        } else if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_K)) {
            if (!keyRepeatStarted) {
                // First press or after release
                keyRepeatTimer = KEY_REPEAT_DELAY;
                keyRepeatStarted = true;
            } else {
                keyRepeatTimer -= deltaTime;
                if (keyRepeatTimer <= 0.0f) {
                    // Time to repeat the action
                    keyRepeatTimer = KEY_REPEAT_INTERVAL;
                    currentImageIndex = (currentImageIndex - 1 + imageCount) % imageCount;
                    UnloadTexture(texture);
                    img = LoadImage(images[currentImageIndex]);
                    texture = LoadTextureFromImage(img);
                    UnloadImage(img);
                    zoomScale = 1.0f;
                    imageOffset.x = imageOffset.y = 0;
                }
            }
        } else {
            // Reset repeat conditions when keys are released
            keyRepeatStarted = false;
        }


        if (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_F)) {
            fullSize = !fullSize;
            zoomScale = 1.0f;
            imageOffset.x = imageOffset.y = 0;
        }
        if (IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_J)) {
            currentImageIndex = (currentImageIndex + 1) % imageCount;
            UnloadTexture(texture);
            img = LoadImage(images[currentImageIndex]);
            texture = LoadTextureFromImage(img);
            UnloadImage(img);
            zoomScale = 1.0f;
            imageOffset.x = imageOffset.y = 0;
        }
        if (IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_K)) {
            currentImageIndex = (currentImageIndex - 1 + imageCount) % imageCount;
            UnloadTexture(texture);
            img = LoadImage(images[currentImageIndex]);
            texture = LoadTextureFromImage(img);
            UnloadImage(img);
            zoomScale = 1.0f;
            imageOffset.x = imageOffset.y = 0;
        }
        
        float wheel = GetMouseWheelMove();
        if (IsKeyDown(KEY_LEFT_SUPER) || IsKeyDown(KEY_RIGHT_SUPER)) {
            if (wheel != 0) zoomScale += (wheel > 0 ? -0.1f : 0.1f);
            zoomScale = Clamp(zoomScale, 0.1f, 5.0f); // Limit zoom
        } else if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            Vector2 mouseDelta = GetMouseDelta();
            imageOffset.x -= mouseDelta.x;
            imageOffset.y -= mouseDelta.y;
        }

        // Handle window resizing
        if (IsWindowResized()) {
            // You might want to adjust zoom or image position here based on new dimensions
            zoomScale = 1.0f;
            imageOffset.x = imageOffset.y = 0;
        }

        BeginDrawing();
            ClearBackground(BLACK);

            Rectangle sourceRec = { 0, 0, (float)texture.width, (float)texture.height };
            Rectangle destRec;
            if (fullSize) {
                destRec = (Rectangle){ GetScreenWidth()/2 - (texture.width*zoomScale)/2 + imageOffset.x, 
                                       GetScreenHeight()/2 - (texture.height*zoomScale)/2 + imageOffset.y, 
                                       texture.width * zoomScale, texture.height * zoomScale };
            } else {
                float scale = fminf((float)GetScreenWidth()/texture.width, (float)GetScreenHeight()/texture.height);
                destRec = (Rectangle){ GetScreenWidth()/2 - (texture.width*scale*zoomScale)/2 + imageOffset.x, 
                                       GetScreenHeight()/2 - (texture.height*scale*zoomScale)/2 + imageOffset.y, 
                                       texture.width * scale * zoomScale, texture.height * scale * zoomScale };
            }
            Vector2 origin = {0, 0};
            DrawTexturePro(texture, sourceRec, destRec, origin, 0.0f, WHITE);
        EndDrawing();
    }

    UnloadTexture(texture);
    CloseWindow();

    return 0;
}