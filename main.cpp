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

    // Returns a centered paddle(rectangle type)
    Rectangle GetRect(){
        return Rectangle {x - width/2, y - height/2, width, height};
    }

    void Draw(Color color){
        DrawRectangleRec(GetRect(), color);
    }
};

int main(void){

    const int windowWidth = 1280;
    const int windowHeight = 720;
    bool gameOver = false;
    const char* winner = nullptr;

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
    leftPaddle.speed = 600;
    leftPaddle.width = 25;
    leftPaddle.height = 200;

    Paddle rightPaddle;
    rightPaddle.x = GetScreenWidth() - 30;
    rightPaddle.y = GetScreenHeight()/2;
    rightPaddle.speed = 600;
    rightPaddle.width = 25;
    rightPaddle.height = 200;

    while(!WindowShouldClose()){

        ball.x += ball.speedX * GetFrameTime();
        ball.y += ball.speedY * GetFrameTime();

        // Ball Wall Bouncing
        if (ball.y + ball.radius > GetScreenHeight() || ball.y - ball.radius < 0){
            ball.speedY *= -1;
        }
        // Bounces ball of the left and right walls
        /*if(ball.x + ball.radius > GetScreenWidth() || ball.x - ball.radius < 0){
            ball.speedX *= -1;
        }*/

        // Left Paddle Movement
        if(IsKeyDown(KEY_W) && leftPaddle.y >= 100){
            leftPaddle.y -= leftPaddle.speed * GetFrameTime();
        }
        if(IsKeyDown(KEY_S) && leftPaddle.y <= GetScreenHeight() - 100){
            leftPaddle.y += leftPaddle.speed * GetFrameTime();
        }

        // Right Paddle Movement
        if(IsKeyDown(KEY_UP) && rightPaddle.y > 100){
            rightPaddle.y -= rightPaddle.speed * GetFrameTime();
        }
        if(IsKeyDown(KEY_DOWN) && rightPaddle.y < GetScreenHeight() - 100){
            rightPaddle.y += rightPaddle.speed * GetFrameTime();
        }

        // Checks Collision for paddle and ball
        if(CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius, leftPaddle.GetRect())){
            if(ball.speedX < 0){
                ball.speedX *= -1.1f;
                ball.speedY = (ball.y - leftPaddle.y) / (leftPaddle.height/2) * ball.speedX;
            }
        }
        if(CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius, rightPaddle.GetRect())){
            if(ball.speedX > 0){
                ball.speedX *= -1.1f;
                ball.speedY = (ball.y - rightPaddle.y) / (rightPaddle.height/2) * -ball.speedX;
            }
        }

        // Win conditions
        if(ball.x > GetScreenWidth()){
            gameOver = true;
            winner = "Left Player Wins!";
        }
        if(ball.x < 0){
            gameOver = true;
            winner = "Right Player Wins!";
        }

        // Resets the game
        if(gameOver && IsKeyPressed(KEY_SPACE)){
            gameOver = false;
            ball.y = GetScreenHeight()/2;
            ball.x = GetScreenWidth()/2;
            ball.speedX = 300;
            ball.speedY = 300;
            leftPaddle.x = 30;
            leftPaddle.y = GetScreenHeight()/2;
            rightPaddle.x = GetScreenWidth() - 30;
            rightPaddle.y = GetScreenHeight()/2;
        }

        BeginDrawing();

            ClearBackground(RAYWHITE);

            DrawFPS(10, 10);
            // Draws text when the game is over
            if(gameOver){
                int winnerTextWidth = MeasureText(winner, 50);
                int resetTextWidth = MeasureText("Press space to restart", 30);
                DrawText(winner, GetScreenWidth()/2 - winnerTextWidth/2, GetScreenHeight()/2 - 50, 50, BLACK);
                DrawText("Press space to restart", GetScreenWidth()/2 - resetTextWidth/2, GetScreenHeight()/2 + 20, 30, BLACK);
            }
            
            ball.Draw();
            leftPaddle.Draw(BLACK);
            rightPaddle.Draw(BLACK);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}