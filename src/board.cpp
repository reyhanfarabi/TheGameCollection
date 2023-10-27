#include "board.hpp"

Board::Board(sf::RenderWindow& wnd)
	:
	window(wnd)
{
	for (int y = 0; y < GRID_HEIGHT; y++)
	{
		for (int x = 0; x < GRID_WIDTH; x++)
		{
			tiles[GetTileIndex({ x, y })].setSize({ TILE_SIZE, TILE_SIZE });
			tiles[GetTileIndex({ x, y })].setPosition(
				static_cast<float>(x * TILE_SIZE + X_OFFSET),
				static_cast<float>(y * TILE_SIZE + Y_OFFSET)
			);

			tiles[GetTileIndex({ x, y })].setFillColor(sf::Color::Black);
			tiles[GetTileIndex({ x, y })].setOutlineThickness(1);
			tiles[GetTileIndex({ x, y })].setOutlineColor(sf::Color::White);
		}
	}
}

void Board::DrawBoard()
{
	for (int y = 0; y < GRID_HEIGHT; y++)
	{
		for (int x = 0; x < GRID_WIDTH; x++)
		{
			DrawTile(tiles[GetTileIndex({ x, y })]);
		}
	}
}

void Board::DrawTile(sf::RectangleShape& tile)
{
	// highlight tile when hover
	HoverTile(tile);

	// draw tile
	window.draw(tile);
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
	else
	{
		tile.setFillColor(sf::Color::Black);
	}
}
