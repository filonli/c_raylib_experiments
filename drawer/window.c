#include <stdio.h>
#include <stdlib.h>
#include "raylib.h"
#include "raymath.h"

#include "game.h"

int main()
{
    InitWindow(600,600,"Draw_me");

    SetTargetFPS(24);

    load();

    while(!WindowShouldClose())
    {
        update(GetFrameTime());

        
        BeginDrawing();
        ClearBackground(BLACK);
        draw();
        
        EndDrawing();

        
    }
    

    unload();
    CloseWindow();
    return 0;
}

