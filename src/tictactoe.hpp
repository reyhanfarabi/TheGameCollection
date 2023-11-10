#pragma once

#include "base_game.hpp"
#include "constants.hpp"
#include "board.hpp"
#include "ui.hpp"

#include <SFML\Graphics.hpp>

class TicTacToe : public BaseGame
{
public:
	TicTacToe(sf::RenderWindow& window);
	void Update(sf::Event& event) override;
	void Draw() override;

private:
	enum class State
	{
		Empty,
		Cross,
		Circle
	};

	enum class Player
	{
		You,
		Opponent
	};

	struct Score
	{
		int you = 0;
		int opponent = 0;

		std::string GetFormattedScore()
		{
			return "You: " + std::to_string(you) + " | " + "Opponent: " + std::to_string(opponent);
		}
	};

private:
	void SetTileState(const int tileIndex);
	void SetGameFinishText(const sf::Vector2f& position);
	void EventRestartGame();
	void ResetTileState();
	void DrawEndScreen(const sf::Vector2f& position);
	void DrawScores();
	void SwitchCurrentPlayer();
	bool IsAllTilesFilled();
	bool IsPatternMet(const State state);

private:
	static constexpr int TILE_SIZE = 100;
	static constexpr int GRID_WIDTH = 3;
	static constexpr int GRID_HEIGHT = 3;
	static constexpr int TILE_STATE_SIZE = GRID_WIDTH * GRID_HEIGHT;
	const float X_OFFSET;
	const float Y_OFFSET;
	bool isGameOver = false;
	Player currentPlayer = Player::You;
	State winState = State::Empty;
	Score score;

	sf::RenderWindow& window;
	Board board;
	std::vector<State> tileState;

	UI::Text txtYourTurn;
	UI::Text txtOpponentTurn;
	UI::Text txtGameFinish;
	UI::Text txtScore;
	UI::Text txtTitle;
	const std::string tGF_DRAW = STR_CONST::GAME_FINISH + " DRAW";
	const std::string tGF_YOU = STR_CONST::GAME_FINISH + " YOU WIN";
	const std::string tGF_OPPONENT = STR_CONST::GAME_FINISH + " OPPONENT WIN";

	UI::Button btnRestart;
};