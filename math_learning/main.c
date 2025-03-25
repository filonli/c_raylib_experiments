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


bool is_point_in_triangle(Vector2 tpa,Vector2 tpb,Vector2 tpc,Vector2 point);

bool is_point_projection_in_line_spectre_below(Vector2 lstart,Vector2 lend,Vector2 point);


bool is_point_projection_in_line_spectre_below(Vector2 lstart,Vector2 lend,Vector2 point)
{
    Vector2 origin = lstart;
    float angle = Vector2Angle((Vector2){1,0},Vector2Normalize(Vector2Subtract(lend,lstart)));

    Vector2 local_end = Vector2Rotate(Vector2Subtract(lend,origin),-angle);
    Vector2 local_point = Vector2Rotate(Vector2Subtract(point,origin),-angle);

    return local_point.x >0 && local_point.x < local_end.x&&local_point.y>0;
}


bool is_point_in_triangle(Vector2 tpa,Vector2 tpb,Vector2 tpc,Vector2 point)
{
    bool is_ab = is_point_projection_in_line_spectre_below(a,b,(Vector2){mx,my});
    bool is_bc = is_point_projection_in_line_spectre_below(b,c,(Vector2){mx,my});
    bool is_ca = is_point_projection_in_line_spectre_below(c,a,(Vector2){mx,my});

    //if(is_ab&&is_bc&&is_ca)
}




int mx = 0;
int my = 0;

Vector2 a = {0};
Vector2 b = {0};

Vector2 c = {0};

void load()
{   
    a.x = 50;
    a.y = 300;

    b.x = 400;
    b.y = 50;

    c.x = 550;
    c.y = 500;
    
}

void unload()
{
    
}

void update()
{
    mx = GetMouseX();
    my = GetMouseY();

    
    

    
}

void draw()
{
    
    DrawTriangleLines(a,b,c,GREEN);
    
    DrawText("a",a.x,a.y,22,WHITE);
    DrawText("b",b.x,b.y,22,WHITE);
    DrawText("c",c.x,c.y,22,WHITE);
    
    bool is_ab = is_point_projection_in_line_spectre_below(a,b,(Vector2){mx,my});
    bool is_bc = is_point_projection_in_line_spectre_below(b,c,(Vector2){mx,my});
    bool is_ca = is_point_projection_in_line_spectre_below(c,a,(Vector2){mx,my});

    if(is_ab&&is_bc&&is_ca)
    {
        DrawCircleLines(mx,my,5,BLUE);
    }
    else
    {
        DrawCircleLines(mx,my,5,RED);
    }

}