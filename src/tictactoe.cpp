#include "tictactoe.hpp"

#include <iostream>

TicTacToe::TicTacToe(sf::RenderWindow& window)
	:
	window(window),
	board(
		TILE_SIZE,
		GRID_WIDTH,
		GRID_HEIGHT,
		X_OFFSET,
		Y_OFFSET,
		window
	),
	tileState(TILE_STATE_SIZE),
	X_OFFSET((window.getSize().x / 2) - (GRID_WIDTH * TILE_SIZE / 2)),
	Y_OFFSET((window.getSize().y / 2) - (GRID_HEIGHT * TILE_SIZE / 2))
{
	for (int i = 0; i < TILE_STATE_SIZE; i++)
	{
		tileState[i] = State::Empty;
	}

	// configure font and text
	if (!font.loadFromFile("assets/fonts/Roboto-Regular.ttf"))
	{
		std::cerr << ".Error while loading font" << std::endl;
	}
	else
	{
		txtPlayerTurn.setFont(font);
		txtPlayerTurn.setString("PLAYER TURN!");
		txtPlayerTurn.setCharacterSize(24);
		txtPlayerTurn.setFillColor(sf::Color::Cyan);
		txtPlayerTurn.setStyle(sf::Text::Bold);

		txtOpponentTurn.setFont(font);
		txtOpponentTurn.setString("OPPONENT TURN!");
		txtOpponentTurn.setCharacterSize(24);
		txtOpponentTurn.setFillColor(sf::Color::Magenta);
		txtOpponentTurn.setStyle(sf::Text::Bold);
		
		txtGameFinish.setFont(font);
		txtGameFinish.setString(tGF_DEFAULT);
		txtGameFinish.setCharacterSize(24);
		txtGameFinish.setFillColor(sf::Color::White);
		txtGameFinish.setStyle(sf::Text::Bold);
	}
}

void TicTacToe::Update(sf::Event& event)
{
	if (!isGameOver)
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

		// set game over if all tile is filled
		isGameOver = IsAllTilesFilled();

		// set winstate if win condition is met
		if (IsPatternMet(State::Circle))
		{
			isGameOver = true;
			winState = State::Circle;
		}
		if (IsPatternMet(State::Cross))
		{
			isGameOver = true;
			winState = State::Cross;
		}
	}
}

void TicTacToe::Draw()
{
	if (!isGameOver)
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

		// show text base on whose turn
		if (isPlayerTurn)
		{
			window.draw(txtPlayerTurn);
		}
		else
		{
			window.draw(txtOpponentTurn);
		}
	}
	else
	{
		// set finish game text
		SetGameFinishText();

		// show game over text
		window.draw(txtGameFinish);
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

void TicTacToe::SetGameFinishText()
{
	if (winState == State::Circle)
	{
		txtGameFinish.setString(tGF_PLAYER);
		txtGameFinish.setFillColor(sf::Color::Cyan);
	}
	else if (winState == State::Cross)
	{
		txtGameFinish.setString(tGF_OPPONENT);
		txtGameFinish.setFillColor(sf::Color::Magenta);
	}
	else
	{
		txtGameFinish.setString(tGF_DEFAULT);
		txtGameFinish.setFillColor(sf::Color::White);
	}
}

bool TicTacToe::IsAllTilesFilled()
{
	return std::all_of(tileState.begin(), tileState.end(), [](State state) {
		return state != State::Empty;
	});
}

bool TicTacToe::IsPatternMet(const State state)
{
	// horizontal pattern
	for (int i = 0; i < GRID_HEIGHT; i++)
	{
		if (tileState[0 + i] == state &&
			tileState[3 + i] == state &&
			tileState[6 + i] == state)
		{
			return true;
		}
	}

	// vertical pattern
	for (int i = 0; i < 3; i++)
	{
		if (tileState[(GRID_WIDTH * i) + 0] == state &&
			tileState[(GRID_WIDTH * i) + 1] == state &&
			tileState[(GRID_WIDTH * i) + 2] == state)
		{
			return true;
		}
	}

	// diagonal pattern
	if (tileState[0] == state &&
		tileState[4] == state &&
		tileState[8] == state)
	{
		return true;
	}

	if (tileState[2] == state &&
		tileState[4] == state &&
		tileState[6] == state)
	{
		return true;
	}

	return false;
}
