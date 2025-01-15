#include "raylib.h"
#include "raymath.h"
#include <stdio.h>


int main()
{
  int W=800,H=600;
  InitWindow(W,H, "Hello Raylib");
  SetTargetFPS(60);

  // position, radius, velocity, delta-time, time.
  Vector2 p = { W / 2.0f, H / 2.0f };
  int r = 40;
  Vector2 v = { 100, 200 };
  float dt,t;

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(GetColor(0x181818));

    dt = GetFrameTime();
    t += dt;
    // p += v * dt
    p = Vector2Add(p, Vector2Scale(v, dt)); 
    DrawCircleV(p, r, RED);

    // collisions
    // Basically if the x coordinate goes outside of the screen then reverse v.x. Going outside means going below zero or above W. Same for y.
    if ( p.x < (0+r) || (W-r) < p.x ) v.x = -v.x;
    if ( p.y < (0+r) || (H-r) < p.y ) v.y = -v.y;

    char s[100];
    sprintf(s, "Hello %f", t);
    DrawText(s, 40,40,20,WHITE);
    
    EndDrawing();
  }
  CloseWindow();
  return 0;
}
