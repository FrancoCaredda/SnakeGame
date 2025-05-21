#pragma once

#include "raylib.h"

class Grid
{
public:
	Grid(int width, int height, int cellSize)
		: m_Width(width), m_Height(height), m_CellSize(cellSize) {}
	Grid(const Grid&) = delete;
	Grid(Grid&&) noexcept = delete;

	void Draw() noexcept;
	void DrawAppleAt(const Vector2& position) noexcept;
private:
	int m_Width;
	int m_Height;
	int m_CellSize;

	Color m_Color1{ 83, 245, 83, 255 };
	Color m_Color2{ 63, 186, 63, 255 };
};