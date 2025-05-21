#include "Game.h"
#include "raylib.h"

void Game::Init()
{
	InitWindow(1200, 900, "SnakeGame");

	m_WindowHandle = GetWindowHandle();
}

void Game::Update()
{
	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(Color{ 0, 0, 0, 1 });

		m_Grid.Draw();
		m_Grid.DrawAppleAt(Vector2{ 1,1 });

		EndDrawing();
	}
}

void Game::Close()
{
	CloseWindow();
}
