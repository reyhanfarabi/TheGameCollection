#pragma once

#include "ui.hpp"

#include <SFML\Graphics.hpp>

class Board
{
public:
	Board(
		int tileSize,
		int gridWidth,
		int gridHeight,
		float xOffset,
		float yOffset,
		sf::RenderWindow& wnd,
		bool enableWithSymbol = false
	);
	void DrawTile(const sf::Vector2i& tilePos);
	void DrawTileWithSymbol(const sf::Vector2i& tilePos, const std::string& symbol);

	void SetTileColor(const sf::Vector2i& tilePos, const sf::Color color);
	int GetTileIndex(const sf::Vector2i& tilePos);
	sf::Vector2i GetHoveredTilePos();

private:
	bool IsInsideTile(const sf::RectangleShape& tile, const sf::Vector2i& target);
	void HoverTile(sf::RectangleShape& tile);
	sf::RectangleShape& GetTile(const sf::Vector2i tilePos);

private:
	const int TILE_SIZE;
	const int GRID_WIDTH;
	const int GRID_HEIGHT;
	const float X_OFFSET;
	const float Y_OFFSET;
	bool enableWithSymbol;

	sf::RenderWindow& window;
	std::vector<sf::RectangleShape> tiles;
	std::vector<UI::Text> tileSymbols;
};