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
	Y_OFFSET((window.getSize().y / 2) - (GRID_HEIGHT * TILE_SIZE / 2)),
	txtYourTurn(STR_CONST::YOUR_TURN, 24, sf::Color::Cyan, sf::Vector2f(
		window.getSize().x / 2,
		Y_OFFSET / 2
	), window),
	txtOpponentTurn(STR_CONST::OPPONENT_TURN, 24, sf::Color::Magenta, sf::Vector2f(
		window.getSize().x / 2,
		Y_OFFSET / 2
	), window),
	txtGameFinish(tGF_DRAW, 24, sf::Color::White, sf::Vector2f(
		window.getSize().x / 2,
		window.getSize().y / 2
	), window),
	txtScore(score.GetFormattedScore(), 18, sf::Color::White, sf::Vector2f(0.0f, 0.0f), window),
	btnRestart(
		STR_CONST::RESTART_GAME, 20,
		sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2),
		UI::Padding(14.0f, 0.0f),
		sf::Color::White, sf::Color::Black, 
		sf::Color::Black, sf::Color::White,
		1, sf::Color::White, sf::Color::White,
		window)
{
	ResetTileState();
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
	else
	{
		if (event.type == sf::Event::MouseButtonPressed)
		{
			if (event.mouseButton.button == sf::Mouse::Left &&
				btnRestart.IsTriggerable())
			{
				EventRestartGame();
			}
		}
	}
}

void TicTacToe::Draw()
{
	DrawScores();

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
			txtYourTurn.Draw();
		}
		else
		{
			txtOpponentTurn.Draw();
		}
	}
	else
	{
		DrawEndScreen(sf::Vector2f(
			window.getSize().x / 2,
			window.getSize().y / 2 - 50	// subtract 50 to offset endscreen content
		));
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

void TicTacToe::SetGameFinishText(const sf::Vector2f& position)
{
	if (winState == State::Circle)
	{
		txtGameFinish.SetString(tGF_YOU);
		txtGameFinish.SetFillColor(sf::Color::Cyan);
	}
	else if (winState == State::Cross)
	{
		txtGameFinish.SetString(tGF_OPPONENT);
		txtGameFinish.SetFillColor(sf::Color::Magenta);
	}
	else
	{
		txtGameFinish.SetString(tGF_DRAW);
		txtGameFinish.SetFillColor(sf::Color::White);
	}

	// recalculate text position after changing string
	txtGameFinish.SetPosition(position);
}

void TicTacToe::EventRestartGame()
{
	switch (winState)
	{
	case State::Circle:
		score.you++;
		break;
	case State::Cross:
		score.opponent++;
		break;
	}

	isGameOver = false;
	isPlayerTurn = true;
	winState = State::Empty;
	ResetTileState();
}

void TicTacToe::ResetTileState()
{
	for (int i = 0; i < TILE_STATE_SIZE; i++)
	{
		tileState[i] = State::Empty;
	}
}

void TicTacToe::DrawEndScreen(const sf::Vector2f& position)
{
	// set finish game text
	SetGameFinishText(position);

	// show game over text
	txtGameFinish.Draw();

	btnRestart.SetButtonPosition(sf::Vector2f(
		position.x,
		position.y + 50		// add 50 for spacing
	));

	// show restart button
	btnRestart.Draw();
}

void TicTacToe::DrawScores()
{
	txtScore.SetPosition(sf::Vector2f(
		// subtract 10 for spacing
		window.getSize().x - txtScore.GetSize().x / 2 - 10,
		// add 10 for spacing
		txtScore.GetSize().y /2 + 10
	));
	txtScore.SetString(score.GetFormattedScore());
	txtScore.Draw();
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
