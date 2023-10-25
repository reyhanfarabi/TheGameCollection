#include <SFML\Graphics.hpp>

class Board
{
public:
	Board(sf::RenderWindow& wnd);
	void DrawBoard();

private:
	int GetTileIndex(const sf::Vector2i tilePos);

private:
	static constexpr int TILE_SIZE = 50;
	static constexpr int GRID_WIDTH = 3;
	static constexpr int GRID_HEIGHT = 3;
	static constexpr float X_OFFSET = 100;
	static constexpr float Y_OFFSET = 100;

	sf::RenderWindow& window;
	sf::RectangleShape tiles[GRID_WIDTH * GRID_HEIGHT];
};