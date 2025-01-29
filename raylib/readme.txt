Compile in macos
clang -framework CoreVideo -framework IOKit -framework Cocoa -framework GLUT -framework OpenGL libraylib.a -Iraylib/src main.c && ./a.out

I built raylib as a static library in macos using this guide from https://github.com/raysan5/raylib/wiki/Working-on-macOS.  There should be a make-raylib.sh file which has the commands.





The importance of BeginDrawing and EndDrawing
-------------------------------------------------------------

You gotta call BeginDrawing() and EndDrawing() or else weird stuff might happen.
I wasn't calling them during some loops and it was causing a key to appear to be getting pressed twice when it was being pressed once.

# The Importance of BeginDrawing and EndDrawing by Chatgpt
Frame Initialization and Finalization:

BeginDrawing() signals the start of a new frame. It prepares the rendering context for drawing operations.
EndDrawing() completes the rendering of the frame and presents it on the screen. Without it, the drawing commands won't be finalized or displayed.
Input Handling:

Raylib integrates input polling (keyboard, mouse, etc.) into the rendering loop. If BeginDrawing() or EndDrawing() is skipped, input states may not update correctly for that frame.
Buffer Management:

Skipping EndDrawing() can leave the render buffer in an undefined state. The GPU will not know when to swap buffers, leading to missed or partial renders.
Internal Timing Mechanisms:

GetFrameTime() and related timing functions rely on BeginDrawing() and EndDrawing() to calculate the time elapsed between frames. Skipping them can result in incorrect frame timing and inconsistent behavior.
Your Initial Code's Issue



