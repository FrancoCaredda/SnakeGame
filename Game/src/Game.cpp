#include "Game.h"

#include <chrono>
#include <iostream>
#include <cstdlib>

void Game::Init()
{
	InitWindow(1200, 900, "SnakeGame");
	m_WindowHandle = GetWindowHandle();

	m_Tales.reserve(50);
	m_Tales.push_back(Tale{ {11, 8}, m_TaleColor2});

	UpdateApplePosition();
	m_HeadDirection = Up;
}

void Game::Update()
{
	float timer = 0;

	while (!WindowShouldClose())
	{
		timer += GetDeltaTime();

		UpdateHeadDirection();
		if (timer >= 0.25)
		{
			UpdateTalesPosition();
			timer = 0;
		}

		if (HasPlayerPickedApple())
		{
			UpdateApplePosition();

			const Tale& lastTail = m_Tales[m_Tales.size() - 1];
			Color color = ((m_Tales.size() + 1) % 2) ? m_TaleColor2 : m_TaleColor1;

			m_Tales.push_back(Tale{ lastTail.Positon, color });
		}

		BeginDrawing();
		ClearBackground(Color{ 0, 0, 0, 1 });

		m_Grid.Draw();
		m_Grid.DrawAppleAt(m_ApplePosition);

		for (const Tale& tale : m_Tales)
		{
			m_Grid.DrawTale(tale);
		}
		DrawFPS(100, 100);

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
	int keyCode = GetKeyPressed();
	if (keyCode == KEY_W)
	{
		m_HeadDirection = Up;
	}
	else if (keyCode == KEY_S)
	{
		m_HeadDirection = Down;
	}
	else if (keyCode == KEY_A)
	{
		m_HeadDirection = Left;
	}
	else if (keyCode == KEY_D)
	{
		m_HeadDirection = Right;
	}
}
void Game::UpdateTalesPosition()
{
	Vector2 GridSize = m_Grid.GetGridSize();

	for (int i = m_Tales.size() - 1; i >= 1; i--)
	{
		m_Tales[i].Positon = m_Tales[i - 1].Positon;
	}

	m_Tales[0].Positon.x += m_HeadDirection.x;
	m_Tales[0].Positon.y += m_HeadDirection.y;
}

void Game::UpdateApplePosition()
{
	srand(time(0));

	Vector2 gridSize = m_Grid.GetGridSize();

	m_ApplePosition.x = rand() % (int)gridSize.x;
	m_ApplePosition.y = rand() % (int)gridSize.y;
}

bool Game::HasPlayerPickedApple()
{
	return m_Tales[0].Positon.x == m_ApplePosition.x &&
		   m_Tales[0].Positon.y == m_ApplePosition.y;
}
