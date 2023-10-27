#include <SFML\Graphics.hpp>

#include "board.hpp"

class TicTacToe
{
public:
	enum State
	{
		Empty,
		Cross,
		Circle
	};

public:
	TicTacToe(sf::RenderWindow& window);
	void Update();
	void Draw();

private:
	static constexpr int TILE_SIZE = 100;
	static constexpr int GRID_WIDTH = 3;
	static constexpr int GRID_HEIGHT = 3;
	static constexpr int TILE_STATE_SIZE = GRID_WIDTH * GRID_HEIGHT;
	static constexpr float X_OFFSET = 100;
	static constexpr float Y_OFFSET = 100;

	Board board;
	State tileState[TILE_STATE_SIZE];
};