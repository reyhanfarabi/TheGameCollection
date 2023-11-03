#include <SFML\Graphics.hpp>

#include "board.hpp"
#include "ui.hpp"

class TicTacToe
{
public:
	enum class State
	{
		Empty,
		Cross,
		Circle
	};

public:
	TicTacToe(sf::RenderWindow& window);
	void Update(sf::Event& event);
	void Draw();

private:
	void SetTileState(const int tileIndex);
	void SetGameFinishText(const sf::Vector2f& position);
	void EventRestartGame();
	void ResetTileState();
	void DrawEndScreen(const sf::Vector2f& position);
	bool IsAllTilesFilled();
	bool IsPatternMet(const State state);

private:
	static constexpr int TILE_SIZE = 100;
	static constexpr int GRID_WIDTH = 3;
	static constexpr int GRID_HEIGHT = 3;
	static constexpr int TILE_STATE_SIZE = GRID_WIDTH * GRID_HEIGHT;
	const float X_OFFSET;
	const float Y_OFFSET;
	bool isPlayerTurn = true;
	bool isGameOver = false;
	State winState = State::Empty;

	sf::RenderWindow& window;
	Board board;
	std::vector<State> tileState;

	UI::Text txtPlayerTurn;
	UI::Text txtOpponentTurn;
	UI::Text txtGameFinish;
	const std::string tGF_DRAW = "GAME FINISH! DRAW";
	const std::string tGF_PLAYER = "GAME FINISH! PLAYER WINS";
	const std::string tGF_OPPONENT = "GAME FINISH! OPPONENT WINS";

	UI::Button btnRestart;
};