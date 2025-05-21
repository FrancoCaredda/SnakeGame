#pragma once

#include "Grid.h"

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
	void* m_WindowHandle = nullptr;
	Grid m_Grid{1200, 900, 50};
};