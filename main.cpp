#include <raylib.h>

int main(void){
    const int windowWidth = 1280;
    const int windowHeight = 720;

    InitWindow(windowWidth, windowHeight, "Crazy Game!");
    SetTargetFPS(144);

    float xpos = GetScreenWidth()/2;
    float ypos = GetScreenHeight()/2;
    float ballRadius = 15;
    float ballSpeedX = 300;
    float ballSpeedY = 300;

    while(!WindowShouldClose()){

        xpos += ballSpeedX * GetFrameTime();
        ypos += ballSpeedY * GetFrameTime();

        if (ypos + ballRadius > GetScreenHeight() || ypos - ballRadius < 0){
            ballSpeedY *= -1;
        }
        if(xpos + ballRadius > GetScreenWidth() || xpos - ballRadius < 0){
            ballSpeedX *= -1;
        }

        BeginDrawing();

            ClearBackground(RAYWHITE);

            DrawFPS(10, 10);
            
            DrawCircle(xpos, ypos, ballRadius, BLACK);
            DrawRectangle(10, GetScreenHeight()/2 - 100, 25, 200, BLACK);
            DrawRectangle(GetScreenWidth() - 35, GetScreenHeight()/2 - 100, 25, 200, BLACK);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}