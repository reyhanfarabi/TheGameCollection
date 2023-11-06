#include "minesweeper.hpp"

Minesweeper::Minesweeper(sf::RenderWindow& wnd)
	:
	window(wnd),
	X_OFFSET((wnd.getSize().x / 2) - (GRID_WIDTH * TILE_SIZE / 2)),
	Y_OFFSET((wnd.getSize().y / 2) - (GRID_HEIGHT * TILE_SIZE / 2)),
	board(TILE_SIZE, GRID_WIDTH, GRID_HEIGHT, X_OFFSET, Y_OFFSET, window),
	tileState(TILE_STATE_SIZE)
{
	SetAllStateDefault();
}

void Minesweeper::Update(sf::Event& event)
{
}

void Minesweeper::Draw()
{
	for (int y = 0; y < GRID_HEIGHT; y++)
	{
		for (int x = 0; x < GRID_WIDTH; x++)
		{
			// set tile color base on current state of each tile
			switch (tileState[GRID_HEIGHT * y + x])
			{
			case State::EmptyHidden:
				board.SetTileColor({ x, y }, sf::Color::Cyan);
				break;
			case State::EmptyShowed:
				board.SetTileColor({ x, y }, sf::Color::Black);
				break;
			case State::BombHidden:
				board.SetTileColor({ x, y }, sf::Color::Magenta);
				break;
			case State::BombShowed:
				board.SetTileColor({ x, y }, sf::Color::Red);
				break;
			case State::Flagged:
				board.SetTileColor({ x, y }, sf::Color::Yellow);
				break;
			default:
				break;
			}

			board.DrawTile({ x, y });
		}
	}
}

void Minesweeper::SetAllStateDefault()
{
	for (int i = 0; i < TILE_STATE_SIZE; i++)
	{
		tileState[i] = State::EmptyHidden;
	}
}
