#include <stdio.h>
#include <stdlib.h>
#include "raylib.h"
#include "raymath.h"

void load();
void unload();
void update();
void draw();

int main ()
{

    InitWindow(600,600,"EDITR");
    load();

    while(!WindowShouldClose())
    {
        update();
        ClearBackground(BLACK);
        BeginDrawing();
        draw();
        EndDrawing();
    }
    unload();
    CloseWindow();
    return 0;
}


int mx = 0;
int my = 0;
float rad = 15;

typedef struct Object
{
    bool exist;
    int x;
    int y;
    float radius;
}obj,Object,OBJ;

int max_objects = 99;
obj *objects;

obj* create_object(int x,int y,float radius);
void destroy_object(obj* o);
void destroy_objects_in_area(int pos_x,int pos_y,float radius);

obj* create_object(int x,int y,float radius)
{
    for(int i = 0;i<max_objects;i++)
    {
        if(!objects[i].exist)
        {
            objects[i].exist = true;
            objects[i].x = x;
            objects[i].y = y;
            objects[i].radius = radius;
            
            return &objects[i];
        }
    }
}

void destroy_object(obj* o)
{
    o->exist =false;
}

void destroy_objects_in_area(int pos_x,int pos_y,float radius)
{
    for(int i = 0;i<max_objects;i++)
    {
        if(objects[i].exist)
        {
            obj o = objects[i];
            if(Vector2Distance((Vector2){pos_x,pos_y},(Vector2){o.x,o.y})<radius)
            {
                objects[i].exist = false;
            }
        }
    }
}

const char* save_path = "save.data";

void load()
{   
    if(FileExists(save_path))
    {
        int data_size = 0;
        objects = (obj*)LoadFileData(save_path,&data_size);
        printf("data_size: %i\n",data_size);

        max_objects = data_size/sizeof(obj);

        printf("max_objects: %i\n",max_objects);
    }
    else
    {
        objects = malloc(sizeof(obj)*max_objects);
    }
    
}

void unload()
{
    SaveFileData(save_path,objects,sizeof(obj)*max_objects);
    free(objects);
}

void update()
{
    mx = GetMouseX();
    my = GetMouseY();

    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        create_object(mx,my,rad);
    }
    if(IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
    {
        destroy_objects_in_area(mx,my,rad);
    }

    rad += GetMouseWheelMove();
}

void draw()
{
    
    for(int i = 0;i<max_objects;i++)
    {
        if(objects[i].exist)
        {
            obj o = objects[i];
            DrawCircle(o.x,o.y,o.radius,WHITE);
        }
    }
    DrawCircleLines(mx,my,rad,RED);

}