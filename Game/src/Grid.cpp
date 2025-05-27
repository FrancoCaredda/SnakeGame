#include "Grid.h"

void Grid::BakeBackground()
{
	if (!IsTextureValid(m_Background.texture))
	{
		m_Background = LoadRenderTexture(m_Width, m_Height);
	}

	BeginTextureMode(m_Background);
	ClearBackground(Color{});

	Draw();

	EndTextureMode();
}

void Grid::Draw()
{
	int cols = m_Width / m_CellSize;
	int rows = m_Height / m_CellSize;

	Color color1 = m_Color1;
	Color color2 = m_Color2;

	for (int j = 0; j < cols; j++)
	{
		Color currentColor = color1;

		for (int i = 0; i < rows; i++)
		{
			DrawRectangle(j * m_CellSize, i * m_CellSize, m_CellSize, m_CellSize, currentColor);

			if ((i + 1) % 2 != 0)
				currentColor = color2;
			else
				currentColor = color1;
		}
	
		color1 = color2;
		color2 = currentColor;
	}
}

void Grid::DrawBackground()
{
	DrawTextureRec(m_Background.texture,
		Rectangle{ 0, 0, (float)m_Width, (float)m_Height },
		Vector2{}, Color{ 255, 255, 255, 255 });
}

void Grid::DrawAppleAt(const Vector2& position)
{
	int halfSize = m_CellSize / 2;
	DrawCircle(position.x * m_CellSize + halfSize, position.y * m_CellSize + halfSize, halfSize / 2, Color{ 255, 0, 0, 255 });
}

void Grid::DrawTale(const Tale& tale)
{
	DrawRectangle(tale.Positon.x * m_CellSize,
		tale.Positon.y * m_CellSize, m_CellSize, m_CellSize, tale.Color);
}
