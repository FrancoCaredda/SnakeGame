#include "Game.h"

#include <chrono>

void Game::Init()
{
	InitWindow(m_Width, m_Height, "SnakeGame");
	m_WindowHandle = GetWindowHandle();
}

void Game::Update()
{
	while (!WindowShouldClose())
	{
		HandleInput();
		m_Grid.Update(GetDeltaTime());
		m_GridRenderer.Draw(m_Grid);
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

void Game::HandleInput()
{
	int keyCode = GetKeyPressed();
	if (keyCode == KEY_W)
	{
		m_Grid.SetHeadDirection(Grid::Up);
	}
	else if (keyCode == KEY_S)
	{
		m_Grid.SetHeadDirection(Grid::Down);
	}
	else if (keyCode == KEY_A)
	{
		m_Grid.SetHeadDirection(Grid::Left);
	}
	else if (keyCode == KEY_D)
	{
		m_Grid.SetHeadDirection(Grid::Right);
	}
}
