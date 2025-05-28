#pragma once

#include "Grid.h"
#include <vector>

class Game
{
public:
	Game() = default;
	Game(const Game&) = delete;
	Game(Game&&) noexcept = delete;

	void Init();
	void Update();

	void Close();
private:
	float GetDeltaTime();
	void HandleInput();
private:
	void* m_WindowHandle = nullptr;

	int m_Width = 1200, m_Height = 900, m_CellSize = 50;

	Grid m_Grid{ m_Width, m_Height, m_CellSize };
	GridRenderer m_GridRenderer{ m_Width, m_Height, m_CellSize };
};