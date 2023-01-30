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

    RectangleObject Map[MAP_HEIGHT][MAP_WIDTH];

    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            RectangleObject rectObj;
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
    Player.Body.width = 32;
    Player.Body.height = 64;
    Player.Body.x = (GetScreenWidth() / 2) - (Player.Body.width / 2);
    Player.Body.y = (GetScreenHeight() / 2);
    Player.Energy = 500;
    Player.Health = 100;
    Player.FacingDirection = 0;

    //Projectile Arrows[30];

    //for (int i = 0; i < 30; i++) {
    //    Arrows[i].Shot = false;
    //}

    Entity Monsters[10];

    for (int i = 0; i < 10; i++) {
        Monsters[i].Body.x = GetRandomValue(100, 300);
        Monsters[i].Body.y = GetRandomValue(100, 300);
        Monsters[i].Body.width = 32;
        Monsters[i].Body.height = 64;
        Monsters[i].Energy = 0;
        Monsters[i].FacingDirection = 0;
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
