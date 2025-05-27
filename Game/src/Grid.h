#pragma once

#include "raylib.h"

#include <cmath>

struct Tale
{
	Vector2 Positon;
	Color Color;
};

class Grid
{
public:
	Grid(int width, int height, int cellSize)
		: m_Width(width), m_Height(height), m_CellSize(cellSize) {}
	Grid(const Grid&) = delete;
	Grid(Grid&&) noexcept = delete;

	~Grid()
	{
		if (IsTextureValid(m_Background.texture))
		{
			UnloadRenderTexture(m_Background);
		}
	}


	void BakeBackground();

	void Draw();
	void DrawBackground();
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

	RenderTexture2D m_Background;
};