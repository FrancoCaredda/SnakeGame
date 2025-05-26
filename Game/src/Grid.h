#pragma once

#include "Tale.h"

#include <cmath>

class Grid
{
public:
	Grid(int width, int height, int cellSize)
		: m_Width(width), m_Height(height), m_CellSize(cellSize) {}
	Grid(const Grid&) = delete;
	Grid(Grid&&) noexcept = delete;

	void Draw();
	void DrawAppleAt(const Vector2& position);
	void DrawTale(const Tale& tale);

	inline Vector2 GetGridSize() const 
	{ 
		return Vector2{ std::ceilf(m_Width / m_CellSize), std::ceilf(m_Height / m_CellSize) };
	}
private:
	int m_Width;
	int m_Height;
	int m_CellSize;

	Color m_Color1{ 83, 245, 83, 255 };
	Color m_Color2{ 63, 186, 63, 255 };
};