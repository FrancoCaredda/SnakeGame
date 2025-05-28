#include "Grid.h"

#include <cstdlib>
#include <ctime>

const Vector2 Grid::Up{ 0, -1 };
const Vector2 Grid::Down{ 0, 1 };
const Vector2 Grid::Left{ -1, 0 };
const Vector2 Grid::Right{ 1, 0 };

Grid::Grid(int width, int height, int cellSize)
	: m_Width(width), m_Height(height), m_CellSize(cellSize)
{
	srand(time(0));
	m_Tales.reserve(50);

}

void Grid::Init()
{
	Vector2 gridSize = GetGridSize();

	Vector2 position{
		static_cast<float>(rand() % (int)gridSize.x),
		static_cast<float>(rand() % (int)gridSize.y)
	};

	m_Tales.push_back(Tale{ position, m_TaleColor2});
}

void Grid::Cleanup()
{
	m_Tales.clear();
}

void Grid::SetUpdateTime(float time)
{
	m_UpdateTime = time;
}

void Grid::SetHeadDirection(const Vector2& direction)
{
	m_HeadDirection = direction;
}

void Grid::Update(float deltaTime)
{
	if (HasPlayerEatenTail())
		return;

	m_Timer += deltaTime;

	if (m_Timer >= m_UpdateTime)
	{
		UpdateTalesPosition();
		m_Timer = 0;
	}

	if (HasPlayerPickedApple())
	{
		UpdateApplePosition();
		AddTail();
	}
}

bool Grid::HasPlayerPickedApple()
{
	return m_Tales[0].Positon.x == m_ApplePosition.x &&
		m_Tales[0].Positon.y == m_ApplePosition.y;
}

bool Grid::HasPlayerEatenTail() const
{
	const Tale& head = m_Tales[0];

	for (int i = 1; i < m_Tales.size(); i++)
	{
		if (head.Positon.x == m_Tales[i].Positon.x &&
			head.Positon.y == m_Tales[i].Positon.y)
		{
			return true;
		}
	}

	return false;
}

void Grid::UpdateTalesPosition()
{
	Vector2 gridSize = GetGridSize();

	for (int i = m_Tales.size() - 1; i >= 1; i--)
	{
		m_Tales[i].Positon = m_Tales[i - 1].Positon;
	}

	Tale& head = m_Tales[0];

	head.Positon.x += m_HeadDirection.x;
	head.Positon.y += m_HeadDirection.y;

	if (head.Positon.x < 0)
	{
		head.Positon.x = gridSize.x - 1;
	}
	else if (head.Positon.x >= gridSize.x)
	{
		head.Positon.x = 0;
	}

	if (head.Positon.y < 0)
	{
		head.Positon.y = gridSize.y - 1;
	}
	else if (head.Positon.y >= gridSize.y)
	{
		head.Positon.y = 0;
	}
}

void Grid::UpdateApplePosition()
{
	Vector2 gridSize = GetGridSize();

	m_ApplePosition.x = rand() % (int)gridSize.x;
	m_ApplePosition.y = rand() % (int)gridSize.y;
}

void Grid::AddTail()
{
	Color color = ((m_Tales.size() + 1) % 2) ? m_TaleColor2 : m_TaleColor1;
	m_Tales.push_back(Tale{ {-1, -1}, color });
}

void GridRenderer::BakeBackground()
{
	if (IsTextureValid(m_Background.texture))
	{
		return;
	}

	m_Background = LoadRenderTexture(m_Width, m_Height);

	BeginTextureMode(m_Background);
	ClearBackground(Color{});

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

	EndTextureMode();
}

void GridRenderer::Draw(const Grid& grid)
{
	const std::vector<Tale>& tales = grid.GetTales();

	BakeBackground();

	BeginDrawing();
	ClearBackground(Color{ 0, 0, 0, 1 });

	DrawBackground();
	DrawAppleAt(grid.GetApplePosition());

	for (const Tale& tale : tales)
	{
		DrawTale(tale);
	}

	if (!grid.HasPlayerEatenTail())
	{
		DrawText(TextFormat("Score: %i", tales.size() - 1), 0, 0, 24, Color{ 0, 0, 0, 255 });
	}
	else
	{
		DrawText(TextFormat("Your score is %i\nPress SPACE to play again", tales.size() - 1), (m_Width - 12 * 24) / 2, (m_Height - 24) / 2, 24, Color{ 0, 0, 0, 255 });
	}

	EndDrawing();
}

void GridRenderer::DrawBackground()
{
	DrawTextureRec(m_Background.texture,
		Rectangle{ 0, 0, (float)m_Width, (float)m_Height },
		Vector2{}, Color{ 255, 255, 255, 255 });
}

void GridRenderer::DrawAppleAt(const Vector2& position)
{
	int halfSize = m_CellSize / 2;
	DrawCircle(position.x * m_CellSize + halfSize, position.y * m_CellSize + halfSize, halfSize / 2, Color{ 255, 0, 0, 255 });
}

void GridRenderer::DrawTale(const Tale& tale)
{
	DrawRectangle(tale.Positon.x * m_CellSize,
		tale.Positon.y * m_CellSize, m_CellSize, m_CellSize, tale.Color);
}
