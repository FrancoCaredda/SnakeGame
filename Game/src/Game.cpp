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

	m_Grid.BakeBackground();

	m_HeadDirection = Up;

	srand(time(0));
}

void Game::Update()
{
	float timer = 0;

	while (!WindowShouldClose())
	{
		timer += GetDeltaTime();

		if (!HasPlayerEatenTail())
		{
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

				m_Tales.push_back(Tale{ {-1, -1}, color });
			}
		}

		BeginDrawing();
		ClearBackground(Color{ 0, 0, 0, 1 });

		m_Grid.DrawBackground();
		m_Grid.DrawAppleAt(m_ApplePosition);

		for (const Tale& tale : m_Tales)
		{
			m_Grid.DrawTale(tale);
		}
		DrawText(TextFormat("Score: %i", m_Tales.size() - 1), 0, 0, 24, Color{0, 0, 0, 255});

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
	Vector2 gridSize = m_Grid.GetGridSize();

	for (int i = m_Tales.size() - 1; i >= 1; i--)
	{
		m_Tales[i].Positon = m_Tales[i - 1].Positon;
	}

	Tale& head = m_Tales[0];

	head.Positon.x += m_HeadDirection.x;
	head.Positon.y += m_HeadDirection.y;

	if (head.Positon.x < 0)
	{
		head.Positon.x = gridSize.x - 1;
	}
	else if (head.Positon.x >= gridSize.x)
	{
		head.Positon.x = 0;
	}

	if (head.Positon.y < 0)
	{
		head.Positon.y = gridSize.y - 1;
	}
	else if (head.Positon.y >= gridSize.y)
	{
		head.Positon.y = 0;
	}
}

void Game::UpdateApplePosition()
{
	Vector2 gridSize = m_Grid.GetGridSize();

	m_ApplePosition.x = rand() % (int)gridSize.x;
	m_ApplePosition.y = rand() % (int)gridSize.y;
}

bool Game::HasPlayerPickedApple()
{
	return m_Tales[0].Positon.x == m_ApplePosition.x &&
		   m_Tales[0].Positon.y == m_ApplePosition.y;
}

bool Game::HasPlayerEatenTail()
{
	const Tale& head = m_Tales[0];

	for (int i = 1; i < m_Tales.size(); i++)
	{
		if (head.Positon.x == m_Tales[i].Positon.x &&
			head.Positon.y == m_Tales[i].Positon.y)
		{
			return true;
		}
	}

	return false;
}
