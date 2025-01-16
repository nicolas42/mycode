#include "raylib.h"
#include <string.h>
#include <stdlib.h>

#define MAX_TEXT_SIZE 1024
#define FONT_SIZE 20

typedef struct {
    char text[MAX_TEXT_SIZE];
    int cursor;
} TextEditor;

void initTextEditor(TextEditor *editor) {
    memset(editor->text, 0, sizeof(editor->text));
    editor->cursor = 0;
}

void drawTextEditor(TextEditor *editor) {
    ClearBackground(RAYWHITE);
    DrawText(editor->text, 10, 10, FONT_SIZE, BLACK);

    // Draw cursor
    int cursorX = 10 + MeasureText(editor->text, FONT_SIZE);
    DrawRectangle(cursorX, 10, 2, FONT_SIZE, BLACK);
}

void updateTextEditor(TextEditor *editor) {
    if (IsKeyPressed(KEY_BACKSPACE) && editor->cursor > 0) {
        editor->cursor--;
        editor->text[editor->cursor] = '\0';
    } else if (IsKeyPressed(KEY_ENTER) && editor->cursor < MAX_TEXT_SIZE - 1) {
        editor->text[editor->cursor++] = '\n';
        editor->text[editor->cursor] = '\0';
    } else if (IsKeyPressed(KEY_LEFT) && editor->cursor > 0) {
        editor->cursor--;
    } else if (IsKeyPressed(KEY_RIGHT) && editor->cursor < (int)strlen(editor->text)) {
        editor->cursor++;
    } else if (editor->cursor < MAX_TEXT_SIZE - 1) {
        int key = GetCharPressed();
        while (key > 0) {
            if ((key >= 32) && (key <= 125)) {
                editor->text[editor->cursor++] = (char)key;
                editor->text[editor->cursor] = '\0';
            }
            key = GetCharPressed();  // Check next character in the queue
        }
    }
}

int main(void) {
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Simple Text Editor");

    TextEditor editor;
    initTextEditor(&editor);

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
        updateTextEditor(&editor);
        drawTextEditor(&editor);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
