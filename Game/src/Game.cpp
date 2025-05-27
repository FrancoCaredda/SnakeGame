#include "Game.h"

#include <chrono>
#include <iostream>

void Game::Init()
{
	InitWindow(1200, 900, "SnakeGame");
	m_WindowHandle = GetWindowHandle();

	m_Tales.reserve(50);
	m_Tales.push_back(Tale{ {11, 8}, {120, 0, 0, 255} });
	m_Tales.push_back(Tale{ {12, 8}, {193, 18, 31, 255} });
	m_Tales.push_back(Tale{ {13, 8}, {120, 0, 0, 255} });
	m_Tales.push_back(Tale{ {14, 8}, {193, 18, 31, 255} });


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
