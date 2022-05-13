#include <raylib.h>

int main(void){
    const int windowWidth = 1280;
    const int windowHeight = 720;

    InitWindow(windowWidth, windowHeight, "Crazy Game!");
    SetTargetFPS(FLAG_VSYNC_HINT);

    while(!WindowShouldClose()){
        BeginDrawing();

            ClearBackground(RAYWHITE);

            DrawFPS(10, 10);
            
            DrawCircle(xpos, ypos, 25, BLACK);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}