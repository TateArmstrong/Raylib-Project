#include <raylib.h>
#include <rlgl.h>
#include <iostream>

struct Player{
    float x, y, speed, radius, rotation;
    Texture2D sprite;
    
    void initPlayer(float x_, float y_, float speed_, float radius_, float rotation, Texture sprite_){
        x = x_;
        y = y_;
        speed = speed_;
        radius = radius_;
        sprite = sprite_;
    }

    Vector2 GetOrigin2(){
        return {x, y};
    }

    Vector2 GetOrigin(){
        return {x - 66.0f, y - 77.0f};
    }
};

void PlayerInput(Player &player){
    if(IsKeyDown(KEY_W)){
        player.y -= player.speed * GetFrameTime();
    }
    if(IsKeyDown(KEY_S)){
        player.y += player.speed * GetFrameTime();
    }
    if(IsKeyDown(KEY_A)){
        player.x -= player.speed * GetFrameTime();
    }
    if(IsKeyDown(KEY_D)){
        player.x += player.speed * GetFrameTime();
    }
}

int main(void){
    
    const int windowWidth = 1280;
    const int windowHeight = 720;

    InitWindow(windowWidth, windowHeight, "Top Down Shooter Test");
    SetTargetFPS(144);

    Player player; 
    player.initPlayer((float)GetScreenWidth()/2, (float)GetScreenHeight()/2,
         300.0f, 40.0f, 180.0f, LoadTexture("rsrc/top_down_man.png"));

    Rectangle soruceRect = {0.0f, 0.0f, player.sprite.width, player.sprite.height};
    Rectangle destRect = {player.x, player.y, player.sprite.width, player.sprite.height};

    int rotation = 0;

    while(!WindowShouldClose()){

        // Player Inputs
        PlayerInput(player);

        //rotation++;

        ClearBackground(RAYWHITE);

        BeginDrawing();

            DrawRectangleRec(soruceRect, BLACK);
            DrawRectangleRec(destRect, BLACK);
            DrawTexturePro(player.sprite, soruceRect, destRect, player.GetOrigin2(), rotation, WHITE);
            //DrawTextureEx(player.sprite, (Vector2){0.0f, 0.0f}, player.rotation, 300, WHITE);
            DrawCircleV(player.GetOrigin2(), player.radius, BLACK);

        EndDrawing();
    }

    UnloadTexture(player.sprite);

    CloseWindow();

    return 0;
}