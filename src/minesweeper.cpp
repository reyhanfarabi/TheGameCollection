#include "minesweeper.hpp"

Minesweeper::Minesweeper(sf::RenderWindow& wnd)
	:
	window(wnd),
	X_OFFSET((window.getSize().x / 2) - (GRID_WIDTH * TILE_SIZE / 2)),
	Y_OFFSET((window.getSize().y / 2) - (GRID_HEIGHT * TILE_SIZE / 2)),
	board(TILE_SIZE, GRID_WIDTH, GRID_HEIGHT, X_OFFSET, Y_OFFSET, window)
{}

void Minesweeper::Update(sf::Event& event)
{
}

void Minesweeper::Draw()
{
	for (int y = 0; y < GRID_HEIGHT; y++)
	{
		for (int x = 0; x < GRID_WIDTH; x++)
		{
			board.DrawTile({ x, y });
		}
	}
}
