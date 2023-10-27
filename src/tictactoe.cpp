#include "tictactoe.hpp"

TicTacToe::TicTacToe(sf::RenderWindow& window)
	:
	board(
		TILE_SIZE,
		GRID_WIDTH,
		GRID_HEIGHT,
		X_OFFSET,
		Y_OFFSET,
		window
	)
{
	for (int i = 0; i < TILE_STATE_SIZE; i++)
	{
		tileState[i] = State::Empty;
	}
}

void TicTacToe::Update()
{
}

void TicTacToe::Draw()
{
	for (int y = 0; y < GRID_HEIGHT; y++)
	{
		for (int x = 0; x < GRID_WIDTH; x++)
		{
			// set tile color base on current state of each tile
			switch (tileState[GRID_HEIGHT * y + x])
			{
			case State::Empty:
				board.SetTileColor({ x, y }, sf::Color::Black);
				break;
			case State::Cross:
				board.SetTileColor({ x, y }, sf::Color::Magenta);
				break;
			case State::Circle:
				board.SetTileColor({ x, y }, sf::Color::Cyan);
				break;
			default:
				break;
			}

			board.DrawTile({ x, y });
		}
	}
}
