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
			window.draw(tiles[GetTileIndex({ x, y })]);
		}
	}
}

int Board::GetTileIndex(const sf::Vector2i tilePos)
{
	return GRID_HEIGHT * tilePos.y + tilePos.x;
}
