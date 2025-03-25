#include <stdio.h>
#include <stdlib.h>
#include "raylib.h"
#include "raymath.h"

#include "game.h"

Image img;
Texture texture;
void load()
{   
    printf("loading_game\n");

    img = GenImageColor(600,600,WHITE);
    texture = LoadTextureFromImage(img);

}

void unload()
{
    UnloadTexture(texture);
    UnloadImage(img);
}
bool lmb = false;

float lastx;
float lasty;

void update(float dt)
{   
    lmb = IsMouseButtonDown(MOUSE_BUTTON_LEFT);
    if(lmb)
    {
        
        ImageDrawLineV(&img,(Vector2){lastx,lasty},(Vector2){GetMouseX(),GetMouseY()},GREEN);
        
        UnloadTexture(texture);
        texture = LoadTextureFromImage(img);
    }
    if(IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
    {
        //UnloadTexture(texture);
        //texture = LoadTextureFromImage(img);
    }


    lastx = GetMouseX();
    lasty = GetMouseY();
}
void draw()
{
    
    DrawTexture(texture,0,0,WHITE);
    
    DrawCircleLines(GetMouseX(),GetMouseY(),16,RED);

    if(lmb)
    {
        DrawCircle(GetMouseX(),GetMouseY(),5,RED);
    }
}

