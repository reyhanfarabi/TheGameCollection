#include <SFML\Graphics.hpp>

class Board
{
public:
	Board(sf::RenderWindow& wnd);
	void DrawBoard();
	void DrawTile(sf::RectangleShape& tile);

private:
	int GetTileIndex(const sf::Vector2i& tilePos);
	bool IsInsideTile(const sf::RectangleShape& tile, const sf::Vector2i& target);
	void HoverTile(sf::RectangleShape& tile);

private:
	static constexpr int TILE_SIZE = 50;
	static constexpr int GRID_WIDTH = 3;
	static constexpr int GRID_HEIGHT = 3;
	static constexpr float X_OFFSET = 100;
	static constexpr float Y_OFFSET = 100;

	sf::RenderWindow& window;
	sf::RectangleShape tiles[GRID_WIDTH * GRID_HEIGHT];
};