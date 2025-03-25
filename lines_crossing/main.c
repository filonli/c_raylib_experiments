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

    InitWindow(600,600,"LEARN");
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

bool is_lines_crossing(Vector2 a, Vector2 b,Vector2 c, Vector2 d,Vector2* out_croos_point);



int mx = 0;
int my = 0;

Vector2 ta = {0};
Vector2 tb = {0};

Vector2 tc = {0};
Vector2 td = {0};


bool is_lines_crossing(Vector2 a, Vector2 b,Vector2 c, Vector2 d,Vector2* out_croos_point)
{
    Vector2 origin = c;

    Vector2 al = Vector2Subtract(a,origin);
    Vector2 bl = Vector2Subtract(b,origin);
    Vector2 cl = Vector2Subtract(c,origin);
    Vector2 dl = Vector2Subtract(d,origin);

    float angle = Vector2LineAngle(c,d);

    al = Vector2Rotate(al,angle);
    bl = Vector2Rotate(bl,angle);
    cl = Vector2Rotate(cl,angle);
    dl = Vector2Rotate(dl,angle);
    
    Vector2 botom_point = al.y<bl.y?al:bl;
    Vector2 top_point = al.y<bl.y?bl:al;
    Vector2 local_cross = botom_point;

    Vector2 top_dir = Vector2Normalize(Vector2Subtract(bl,al));

    local_cross.y = 0;
    local_cross.x = botom_point.x+(1-((top_dir.x/top_dir.y)*botom_point.y));

    bool in_spectre = false;
    if(dl.x > 0)
    {
        in_spectre = local_cross.x>0&&local_cross.x<dl.x;
    }
    else
    {
        in_spectre = local_cross.x<0&&local_cross.x>dl.x;
    }

    
    bool is_crossing = (botom_point.y<0&&top_point.y>0)&&in_spectre;
    
    Vector2 gl_cross = Vector2Add(Vector2Rotate(local_cross,-angle),origin);

    out_croos_point[0] = gl_cross;

    return is_crossing;
}

void load()
{   
    tc.x = 100;
    tc.y = 500;

    td.x = 400;
    td.y = 400;
    
}

void unload()
{
    
}

void update()
{
    mx = GetMouseX();
    my = GetMouseY();

    if(IsKeyDown(KEY_LEFT_SHIFT))
    {
        if(IsMouseButtonDown(MOUSE_BUTTON_LEFT))
        {
            tc.x = mx;
            tc.y = my;
        }
        if(IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
        {
            td.x = mx;
            td.y = my;
        }
    }
    else
    {
        if(IsMouseButtonDown(MOUSE_BUTTON_LEFT))
        {
            ta.x = mx;
            ta.y = my;
        }
        if(IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
        {
            tb.x = mx;
            tb.y = my;
        }
    }
    

    
}

void draw()
{
    
    DrawLineV(ta,tb,RED);
    DrawLineV(tc,td,GREEN);
    //DrawCircleLines(mx,my,5,RED);

    Vector2 cross_point = {0};

    if(is_lines_crossing(ta,tb,tc,td,&cross_point))
    {
        DrawCircleLinesV(cross_point,5,YELLOW);
    }

}