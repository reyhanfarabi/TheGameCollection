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

void TicTacToe::Update(sf::Event& event)
{
	if (event.type == sf::Event::MouseButtonPressed)
	{
		if (event.mouseButton.button == sf::Mouse::Left)
		{
			if (tileState[board.GetTileIndex(board.GetHoveredTilePos())] == State::Empty)
			{
				SetTileState(board.GetTileIndex(board.GetHoveredTilePos()));
				isPlayerTurn = !isPlayerTurn;
			}
		}
	}
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

void TicTacToe::SetTileState(const int tileIndex)
{
	if (isPlayerTurn)
	{
		tileState[tileIndex] = State::Circle;
	}
	else
	{
		tileState[tileIndex] = State::Cross;
	}
}
