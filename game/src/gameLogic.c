#include "raylib.h"
#include "drawGame.c"

void GameLogic(
    int *Screen,
    int *Quit,
    Block Map[MAP_HEIGHT][MAP_WIDTH],
    Entity *Player,
    Monster (*Monsters)[10]
) {
    float delta = GetFrameTime();
    float prex = Player->Body.x;
    float prey = Player->Body.y;

    if (Player->Energy < 500.0) {
        Player->Energy += 25 * delta;
    }
    if (Player->Health < 100) {
        Player->Health += 5 * delta;
    }

    if (IsKeyDown(KEY_LEFT_SHIFT) && Player->Energy > 0) {
        if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) {
            Player->Body.x += 400 * delta;
            Player->Energy -= 100 * delta;
            Player->FacingDirection = 1;
        }
    }
    if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) {
        Player->Body.x += 250 * delta;
        Player->FacingDirection = 1;
    }  
    

    if (IsKeyDown(KEY_LEFT_SHIFT) && Player->Energy > 0) {
        if (IsKeyDown(KEY_A) || IsKeyDown(KEY_RIGHT)) {
            Player->Body.x -= 400 * delta;
            Player->Energy -= 100 * delta;
            Player->FacingDirection = 3;
        }
    }
    if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) {
        Player->Body.x -= 250 * delta;
        Player->FacingDirection = 3;
    }

    if (IsKeyDown(KEY_LEFT_SHIFT) && Player->Energy > 0) {
        if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN)) {
            Player->Body.y += 400 * delta;
            Player->Energy -= 100 * delta;
            Player->FacingDirection = 2;
        }
    }
    if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN)) {
        Player->Body.y += 250 * delta;
        Player->FacingDirection = 2;
    }
        
    if (IsKeyDown(KEY_LEFT_SHIFT) && Player->Energy > 0) {
        if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)) {
            Player->Body.y -= 400 * delta;   
            Player->Energy -= 100 * delta;
            Player->FacingDirection = 0;
        }
    }
    if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)) {
        Player->Body.y -= 250 * delta;
        Player->FacingDirection = 0;
    }

    for (int i = 0; i < 10; i++) {
        float Mprex = Monsters[i]->Body.x;
        float Mprey = Monsters[i]->Body.y;
        if (Monsters[i]->Body.x > Player->Body.x) Monsters[i]->Body.x -= 250 * delta;
        if (Monsters[i]->Body.x < Player->Body.x) Monsters[i]->Body.x += 250 * delta;
        if (Monsters[i]->Body.y > Player->Body.y) Monsters[i]->Body.y -= 250 * delta;
        if (Monsters[i]->Body.y > Player->Body.y) Monsters[i]->Body.y += 250 * delta;

        if (CheckCollisionRecs(Monsters[i]->Body, Player->Body)) {
            Player->Health -= 10;
            Player->Body.y += 100 * delta;
        }
        

        for (int y = 0; y < MAP_HEIGHT; y++) {
            for (int x = 0; x < MAP_WIDTH; x++)
            {
                Block rectObj = Map[y][x];
                if (rectObj.value == 0)
                {
                    if (CheckCollisionRecs(Monsters[i]->Body, rectObj.rect)) {
                        Monsters[i]->Body.x = Mprex;
                        Monsters[i]->Body.y = Mprey;
                    }
                }
            }
        }
    }

    for (int y = 0; y < MAP_HEIGHT; y++)
    {
        for (int x = 0; x < MAP_WIDTH; x++)
        {
            Block rectObj = Map[y][x];
            if (rectObj.value == 0)
            {
                if (CheckCollisionRecs(Player->Body, rectObj.rect)) {
                    Player->Body.x = prex;
                    Player->Body.y = prey;
                }
            }
        }
    }

    if (*Screen == 0) {
        DrawMenu(Screen, Quit);
    }
    else if (*Screen == 1) {
        DrawGame(Map, *Player, Screen, Monsters);
    }
    else if (*Screen == 2) {
        DrawCredits(Screen);
    }

}