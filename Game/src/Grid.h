#pragma once

#include "raylib.h"

#include <cmath>
#include <vector>

struct Tale
{
	Vector2 Positon;
	Color Color;
};

class Grid
{
public:
	Grid(int width, int height, int cellSize);
	Grid(const Grid&) = delete;
	Grid(Grid&&) noexcept = delete;

	void Init();
	void Cleanup();

	void SetUpdateTime(float time);
	void SetHeadDirection(const Vector2& direction);

	inline Vector2 GetGridSize() const
	{
		return Vector2{ std::ceilf(m_Width / m_CellSize),
				std::ceilf(m_Height / m_CellSize) };
	}

	inline int GetWidth() const { return m_Width; }
	inline int GetHeight() const { return m_Height; }
	inline int GetCellSize() const { return m_CellSize; }

	inline Vector2 GetApplePosition() const { return m_ApplePosition; }
	inline const std::vector<Tale>& GetTales() const { return m_Tales; }

	void Update(float deltaTime);

	bool HasPlayerEatenTail() const;
private:
	bool HasPlayerPickedApple();

	void UpdateTalesPosition();
	void UpdateApplePosition();

	void AddTail();
private:
	std::vector<Tale> m_Tales;

	Vector2 m_HeadDirection = Up;
	Vector2 m_ApplePosition{};

	int m_Width;
	int m_Height;
	int m_CellSize;

	float m_UpdateTime = 0.16;
	float m_Timer = 0;

	Color m_TaleColor1{ 120, 0, 0, 255 };
	Color m_TaleColor2{ 193, 18, 31, 255 };
public:
	static const Vector2 Up;
	static const Vector2 Down;
	static const Vector2 Left;
	static const Vector2 Right;
};

class GridRenderer
{
public:
	GridRenderer(int width, int height, int cellSize)
		: m_Width(width), m_Height(height), m_CellSize(cellSize) {}
	GridRenderer(const GridRenderer&) = delete;
	GridRenderer(GridRenderer&&) noexcept = delete;

	~GridRenderer()
	{
		if (IsTextureValid(m_Background.texture))
		{
			UnloadRenderTexture(m_Background);
		}
	}

	void Draw(const Grid& grid);

	inline Vector2 GetGridSize() const 
	{ 
		return Vector2{ std::ceilf(m_Width / m_CellSize), std::ceilf(m_Height / m_CellSize) };
	}
private:
	void BakeBackground();

	void DrawBackground();
	void DrawAppleAt(const Vector2& position);
	void DrawTale(const Tale& tale);
private:
	int m_Width;
	int m_Height;
	int m_CellSize;

	Color m_Color1{ 83, 245, 83, 255 };
	Color m_Color2{ 63, 186, 63, 255 };

	RenderTexture2D m_Background;
};