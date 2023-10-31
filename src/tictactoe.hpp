#include <SFML\Graphics.hpp>

#include "board.hpp"

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
	bool IsAllTilesFilled();

private:
	static constexpr int TILE_SIZE = 100;
	static constexpr int GRID_WIDTH = 3;
	static constexpr int GRID_HEIGHT = 3;
	static constexpr int TILE_STATE_SIZE = GRID_WIDTH * GRID_HEIGHT;
	const float X_OFFSET;
	const float Y_OFFSET;
	bool isPlayerTurn = true;
	bool isGameOver = false;

	sf::RenderWindow& window;
	Board board;
	std::vector<State> tileState;

	sf::Font font;
	sf::Text txtPlayerTurn;
	sf::Text txtOpponentTurn;
	sf::Text txtGameFinish;
};