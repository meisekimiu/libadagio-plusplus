#include "raylib.h"
#include <iostream>

#include "graphics/SpriteBatch.h"

int main() {
    InitWindow(640, 480, "Raylib Test");
    Texture2D leona = LoadTexture("assets/leona_smile.png");
    SetTargetFPS(60);
    Vector2 leonaPos{0, 0};
    Adagio::SpriteBatch spriteBatch;
    spriteBatch.clearColor = BLUE;
    while (!WindowShouldClose()) {
        spriteBatch.begin();
        auto txt = spriteBatch.drawText("Lookit Leona", {0, 0}, 10);
        txt->fontSize = 36;
        spriteBatch.draw(leona, leonaPos, 0);
        leonaPos.x++;
        spriteBatch.end();
    }
    UnloadTexture(leona);
    CloseWindow();
    return EXIT_SUCCESS;
}
