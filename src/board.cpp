#include "board.hpp"

Board::Board(
	int tileSize, 
	int gridWidth,
	int gridHeight,
	float xOffset,
	float yOffset,
	sf::RenderWindow& window
)	:
	TILE_SIZE(tileSize),
	GRID_WIDTH(gridWidth),
	GRID_HEIGHT(gridHeight),
	X_OFFSET(xOffset),
	Y_OFFSET(yOffset),
	window(window),
	tiles(GRID_WIDTH * GRID_HEIGHT)
{
	for (int y = 0; y < GRID_HEIGHT; y++)
	{
		for (int x = 0; x < GRID_WIDTH; x++)
		{
			GetTile({ x, y }).setSize(sf::Vector2f(TILE_SIZE, TILE_SIZE));
			GetTile({ x, y }).setPosition(
				static_cast<float>(x * TILE_SIZE + X_OFFSET),
				static_cast<float>(y * TILE_SIZE + Y_OFFSET)
			);

			GetTile({ x, y }).setFillColor(sf::Color::Black);
			GetTile({ x, y }).setOutlineThickness(1);
			GetTile({ x, y }).setOutlineColor(sf::Color::White);
		}
	}
}

void Board::DrawTile(const sf::Vector2i& tilePos)
{
	// highlight tile when hover
	HoverTile(GetTile(tilePos));

	// draw tile
	window.draw(GetTile(tilePos));
}

void Board::SetTileColor(const sf::Vector2i& tilePos, const sf::Color color)
{
	GetTile(tilePos).setFillColor(color);
}

sf::Vector2i Board::GetHoveredTilePos()
{
	for (int y = 0; y < GRID_HEIGHT; y++)
	{
		for (int x = 0; x < GRID_WIDTH; x++)
		{
			if (IsInsideTile(GetTile({ x, y }), sf::Mouse::getPosition(window)))
			{
				return sf::Vector2i(x, y);
			}
		}
	}

	return sf::Vector2i();
}

int Board::GetTileIndex(const sf::Vector2i& tilePos)
{
	return GRID_HEIGHT * tilePos.y + tilePos.x;
}

bool Board::IsInsideTile(const sf::RectangleShape& tile, const sf::Vector2i& target)
{
	return
		target.x >= tile.getPosition().x &&
		target.x <= tile.getPosition().x + TILE_SIZE &&
		target.y >= tile.getPosition().y &&
		target.y <= tile.getPosition().y + TILE_SIZE;
}

void Board::HoverTile(sf::RectangleShape& tile)
{
	if (IsInsideTile(tile, sf::Mouse::getPosition(window)))
	{
		tile.setFillColor(sf::Color::White);
	}
}

sf::RectangleShape& Board::GetTile(const sf::Vector2i tilePos)
{
	return tiles[GetTileIndex(tilePos)];
}
