#include "raylib.h"
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#include "raymath.h"
#include "rlgl.h"

#define BLOCK_SIZE 16
#define MAP_WIDTH 75
#define MAP_HEIGHT 50

typedef struct RectangleObject // 0 = Stone, 1 = Grass
{
    Rectangle rect;
    int value;
    Texture2D Texture;
} RectangleObject;

typedef struct Entity {
    Rectangle Body;
    float Energy;
    float Health;
    int FacingDirection; // 0 = up, 1 = right, 2 = down, 3 = left
} Entity;

typedef struct Monster {
    Rectangle Body;
    float Health;
    int Facing;
} Monster;


//typedef struct Projectile {
//    Vector2 position;
//    Vector2 velocity;
//    bool Shot;
//} Projectile;

void DrawMap(RectangleObject map[MAP_HEIGHT][MAP_WIDTH])
{
    for (int y = 0; y < MAP_HEIGHT; y++)
    {
        for (int x = 0; x < MAP_WIDTH; x++)
        {
            RectangleObject rectObj = map[y][x];
            if (rectObj.value == 1)
            {
                DrawTextureRec(rectObj.Texture, rectObj.rect, (Vector2){rectObj.rect.x, rectObj.rect.y}, WHITE);
            }
            else
            {
                DrawTextureRec(rectObj.Texture, rectObj.rect, (Vector2){rectObj.rect.x, rectObj.rect.y}, WHITE);
            }
        }
    }
}

void DrawCredits(int *Screen) {
    if (IsKeyPressed(KEY_ESCAPE)) *Screen = 0;

    Rectangle MenuButton = (Rectangle){0, (GetScreenHeight() / 2) + 175, 175, 75};
    MenuButton.x = (GetScreenWidth() / 2) - (MenuButton.width / 2);
    GuiSetStyle(DEFAULT, TEXT_SIZE, 35);
    int StoneCreditX = (MeasureText("Stone Texture Made by Bagas Aditya Winata on Itch.io", 30) / 4);
    int StoneCreditY = (GetScreenHeight() / 2) + 50;

    int GrassCredX = (MeasureText("Grass Texture Made by octoshrimpy on Itch.io", 30) / 4) + (StoneCreditX / 2);
    int GrassCredY = (GetScreenHeight() / 2) + 100;

    BeginDrawing();
    ClearBackground(WHITE);

    DrawText("Credits", (GetScreenWidth() / 2) - (MeasureText("Credits", 40) / 2), (GetScreenHeight() / 2) - 5, 40, BLACK);

    DrawText("Stone Texture Made by Bagas Aditya Winata on Itch.io", StoneCreditX, StoneCreditY, 30, BLACK);

    DrawText("Grass Texture Made by octoshrimpy on Itch.io", GrassCredX, GrassCredY, 30, BLACK);

    if (GuiButton(MenuButton, "Main Menu")) *Screen = 0;

    EndDrawing();
}

void DrawMenu(int *Screen, int *Quit) {
    Rectangle PlayButton = (Rectangle){0, (GetScreenHeight() / 2), 150, 75};
    PlayButton.x = (GetScreenWidth() / 2) - (PlayButton.width / 2);
    Rectangle CreditsButton = (Rectangle){0, (PlayButton.height + PlayButton.y) + 30, 150, 75};
    CreditsButton.x = (GetScreenWidth() / 2) - (CreditsButton.width / 2);
    Rectangle QuitButton = (Rectangle){0, (CreditsButton.height + CreditsButton.y) + 30, 150, 75};
    QuitButton.x = (GetScreenWidth() / 2) - (QuitButton.width / 2);
    
    int TitleTextSize = MeasureText("RUN RUN", 50);
    BeginDrawing();
    ClearBackground(WHITE);

    DrawText("RUN RUN", (GetScreenWidth() / 2) - (TitleTextSize / 2), (GetScreenHeight() / 2) - 100, 50, BLACK);

    GuiSetStyle(DEFAULT, TEXT_SIZE, 35);
    if (GuiButton(PlayButton, "Play")) {
        *Screen = 1;
    }
    if (GuiButton(CreditsButton, "Credits")) {
        *Screen = 2;
    }
    if (GuiButton(QuitButton, "Quit") || IsKeyPressed(KEY_ESCAPE)) {
        *Quit = 1;
    }
    EndDrawing();
}

void DrawGame(RectangleObject Map[MAP_HEIGHT][MAP_WIDTH], Entity Player, int *Screen, Monster (*Monsters)[10]) {
    if (IsKeyPressed(KEY_ESCAPE)) *Screen = 0;

    Rectangle EnergyBar = {0, 0, 100, 25};
    EnergyBar.x = (GetScreenWidth() / 10) + 50;
    EnergyBar.y = (GetScreenHeight() / 10);
    Rectangle HealthBar = {0, 0, 100, 25};
    HealthBar.x = ((GetScreenWidth() / 10) * 8) + 50;
    HealthBar.y = (GetScreenHeight() / 10);

    BeginDrawing();
    ClearBackground(WHITE);

    DrawMap(Map);

    DrawRectangleRec(Player.Body, BLACK);

    for (int i = 0; i < 10; i++) {
        DrawRectangleRec(Monsters[i]->Body, RED);
    }

    GuiProgressBar(EnergyBar, "", "", Player.Energy, 0, 500);
    DrawText("Energy", EnergyBar.x - (MeasureText("Energy", 30) + 10), EnergyBar.y, 30, WHITE);

    GuiProgressBar(HealthBar, "", "", Player.Health, 0, 100);
    DrawText("Health", HealthBar.x - (MeasureText("Health", 30) + 10), HealthBar.y, 30, WHITE);

    EndDrawing();
}