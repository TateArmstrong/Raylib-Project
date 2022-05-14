#include <raylib.h>

struct Ball
{
    float x, y, speedX, speedY, radius;
    
    void Draw(){
        DrawCircle(x, y, radius, BLACK);
    }
};

struct Paddle
{
    float x, y, speed, width, height;

    void Draw(Color color){
        DrawRectangle(x - width/2, y - height/2,  width, height, color);
    }
};

int main(void){

    const int windowWidth = 1280;
    const int windowHeight = 720;

    InitWindow(windowWidth, windowHeight, "Crazy Game!");
    SetTargetFPS(144);

    Ball ball;
    ball.x = GetScreenWidth()/2;
    ball.y = GetScreenHeight()/2;
    ball.radius = 15;
    ball.speedX = 300;
    ball.speedY = 300;

    Paddle leftPaddle;
    leftPaddle.x = 30;
    leftPaddle.y = GetScreenHeight()/2;
    leftPaddle.speed = 300;
    leftPaddle.width = 25;
    leftPaddle.height = 200;

    Paddle rightPaddle;
    rightPaddle.x = GetScreenWidth() - 30;
    rightPaddle.y = GetScreenHeight()/2;
    rightPaddle.speed = 300;
    rightPaddle.width = 25;
    rightPaddle.height = 200;

    while(!WindowShouldClose()){

        ball.x += ball.speedX * GetFrameTime();
        ball.y += ball.speedY * GetFrameTime();

        if (ball.y + ball.radius > GetScreenHeight() || ball.y - ball.radius < 0){
            ball.speedY *= -1;
        }
        if(ball.x + ball.radius > GetScreenWidth() || ball.x - ball.radius < 0){
            ball.speedX *= -1;
        }

        BeginDrawing();

            ClearBackground(RAYWHITE);

            DrawFPS(10, 10);
            
            ball.Draw();
            leftPaddle.Draw(BLACK);
            rightPaddle.Draw(BLACK);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}