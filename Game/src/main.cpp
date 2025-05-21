#include "raylib.h"

int main(int argc, char** argv)
{
    InitWindow(1200, 900, "SnakeGame");

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(Color{ 0, 0, 0, 1 });

        EndDrawing();
    }

    CloseWindow();

    return 0;
}