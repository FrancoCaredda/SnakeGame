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
	void UpdateHeadDirection();
	void UpdateTalesPosition();
	void UpdateApplePosition();

	bool HasPlayerPickedApple();
	bool HasPlayerEatenTail();
private:
	void* m_WindowHandle = nullptr;
	Grid m_Grid{1200, 900, 50};
	std::vector<Tale> m_Tales;

	Vector2 m_HeadDirection;
	Vector2 m_ApplePosition;

	Color m_TaleColor1{ 120, 0, 0, 255 };
	Color m_TaleColor2{ 193, 18, 31, 255 };

	const Vector2 Up{ 0, -1 };
	const Vector2 Down{ 0, 1 };
	const Vector2 Left{ -1, 0 };
	const Vector2 Right{ 1, 0 };
};