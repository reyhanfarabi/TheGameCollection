#include "battleship.hpp"

Battleship::Battleship(sf::RenderWindow& window)
	:
	window(window),
	board(
		TILE_SIZE,
		GRID_WIDTH,
		GRID_HEIGHT,
		1,
		X_OFFSET,
		Y_OFFSET,
		window,
		Board::TileType::Empty
	),
	X_OFFSET((window.getSize().x / 2) - (GRID_WIDTH * TILE_SIZE / 2)),
	Y_OFFSET((window.getSize().y / 2) - (GRID_HEIGHT * TILE_SIZE / 2))
{}

void Battleship::Update(float& dt)
{
}

void Battleship::MouseEvent(sf::Event& event)
{
}

void Battleship::KeyboardEvent(sf::Event& event)
{
}

void Battleship::Draw()
{
	for (int y = 0; y < GRID_HEIGHT; y++)
	{
		for (int x = 0; x < GRID_WIDTH; x++)
		{
			board.SetTileColor({ x, y }, sf::Color::Black);
			board.DrawTile({ x, y });
		}
	}
}
