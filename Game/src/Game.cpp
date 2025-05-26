#include "Game.h"

#include <chrono>
#include <iostream>

void Game::Init()
{
	InitWindow(1200, 900, "SnakeGame");
	m_WindowHandle = GetWindowHandle();

	m_Tales.reserve(50);

	m_Tales.push_back(Tale{ {11, 8}, {-1, 0}, {255, 0, 255, 255} });
}

void Game::Update()
{
	float timer = 0;

	while (!WindowShouldClose())
	{
		
		timer += GetDeltaTime();

		UpdateHeadDirection();

		if (timer >= 0.5)
		{
			UpdateTalesPosition();
			timer = 0;
		}

		BeginDrawing();
		ClearBackground(Color{ 0, 0, 0, 1 });

		m_Grid.Draw();
		m_Grid.DrawAppleAt(Vector2{ 1,1 });


		for (const Tale& tale : m_Tales)
		{
			m_Grid.DrawTale(tale);
		}
		
		EndDrawing();
	}
}

void Game::Close()
{
	CloseWindow();
}

float Game::GetDeltaTime()
{
	static auto prev = std::chrono::high_resolution_clock::now();

	auto now = std::chrono::high_resolution_clock::now();
	std::chrono::duration<float> dt = now - prev;

	prev = now;

	return dt.count();
}

void Game::UpdateHeadDirection()
{
	Vector2 headDirection = m_Tales[0].Direction;

	int keyCode = GetKeyPressed();
	if (keyCode == KEY_W)
	{
		headDirection = Up;
	}
	else if (keyCode == KEY_S)
	{
		headDirection = Down;
	}
	else if (keyCode == KEY_A)
	{
		headDirection = Left;
	}
	else if (keyCode == KEY_D)
	{
		headDirection = Right;
	}

	m_Tales[0].Direction = headDirection;
}

void Game::UpdateTalesPosition()
{
	Vector2 GridSize = m_Grid.GetGridSize();

	for (Tale& tale : m_Tales)
	{
		tale.Positon.x += tale.Direction.x;
		tale.Positon.y += tale.Direction.y;

		if (tale.Positon.x < 0)
		{
			tale.Positon.x = GridSize.x;
		}
		else if (tale.Positon.x > GridSize.x)
		{
			tale.Positon.x = 0;
		}

		if (tale.Positon.y < 0)
		{
			tale.Positon.y = GridSize.y;
		}
		else if (tale.Positon.y > GridSize.y)
		{
			tale.Positon.y = 0;
		}
	}
}
