#include "raylib.h"
#include "gameLogic.c"
#include <stdio.h>

int main() {
    SetConfigFlags(FLAG_VSYNC_HINT);
    InitWindow(1200, 800, "Run Run");

    SetExitKey(KEY_NULL);

    int GamePlaying = 0;
    int Quit = 0;
    float Energy = 500;
    Image Stone = LoadImage("resources/stone.png");
    Image Grass = LoadImage("resources/grass.png");

    Block Map[MAP_HEIGHT][MAP_WIDTH];

    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            Block rectObj;
            rectObj.rect.x = x * BLOCK_SIZE;
            rectObj.rect.y = y * BLOCK_SIZE;
            rectObj.rect.width = BLOCK_SIZE;
            rectObj.rect.height = BLOCK_SIZE;
            if (y == 0 || y == 1 || y == MAP_HEIGHT - 1 || y == MAP_HEIGHT - 2 || x == 0 || x == 1|| x == MAP_WIDTH - 1 || x == MAP_WIDTH - 2) {
                rectObj.value = 0;
                rectObj.Texture = LoadTextureFromImage(Stone);
            }
            else {
                rectObj.value = 1;
                rectObj.Texture = LoadTextureFromImage(Grass);
            }
            Map[y][x] = rectObj;
        }
    }

    Entity Player;
    Player.Body.width = BLOCK_SIZE * 2;
    Player.Body.height = BLOCK_SIZE * 4;
    Player.Body.x = (GetScreenWidth() / 2) - (Player.Body.width / 2);
    Player.Body.y = (GetScreenHeight() / 2);
    Player.Energy = 500;
    Player.Health = 100;
    Player.FacingDirection = 0;

    //Projectile Arrows[30];

    //for (int i = 0; i < 30; i++) {
    //    Arrows[i].Shot = false;
    //}

    Monster Monsters[10];

    for (int i = 0; i < 10; i++) {
        //Monsters[i].Body.x = GetRandomValue((BLOCK_SIZE * 2) + 20, (BLOCK_SIZE * 70));
        //Monsters[i].Body.y = GetRandomValue((BLOCK_SIZE * 2), (BLOCK_SIZE * 45));
        Monsters[i].Body.x = 350;
        Monsters[i].Body.y = 300;
        Monsters[i].Body.width = BLOCK_SIZE * 2;
        Monsters[i].Body.height = BLOCK_SIZE * 4;
        Monsters[i].Facing = 0;
        Monsters[i].Health = 100;
    }

    while (Quit == 0) {
        if (WindowShouldClose()) Quit = 1;

        GameLogic(
            &GamePlaying,
            &Quit,
            Map,
            &Player,
            &Monsters
        );
    }

    UnloadImage(Stone);
    UnloadImage(Grass);
    CloseWindow();

    return 0;
}
