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
		txtGameFinish.setString("GAME FINISH!");
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

	// check if the game is over
	if (isGameOver)
	{
		// show game over text
		window.draw(txtGameFinish);
	}
	else
	{
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

bool TicTacToe::IsAllTilesFilled()
{
	return std::all_of(tileState.begin(), tileState.end(), [](State state) {
		return state != State::Empty;
	});
}
