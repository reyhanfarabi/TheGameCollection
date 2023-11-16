#pragma once

#include "ui.hpp"

#include <SFML\Graphics.hpp>

class Board
{
public:
	enum class TileType
	{
		Empty,
		Sprite
	};

public:
	Board(
		int tileSize,
		int gridWidth,
		int gridHeight,
		int outlineThickness,
		float xOffset,
		float yOffset,
		sf::RenderWindow& wnd,
		TileType type
	);
	Board(
		int tileSize,
		int gridWidth,
		int outlineThickness,
		int gridHeight,
		float xOffset,
		float yOffset,
		sf::RenderWindow& wnd,
		TileType type,
		std::string spriteFile,
		sf::Vector2i spritePosition,
		sf::Vector2i spriteSize
	);
	void DrawTile(const sf::Vector2i& tilePos);

	void SetTileColor(const sf::Vector2i& tilePos, const sf::Color color);
	void SetTileTextureRect(const sf::Vector2i& tilePos, const sf::IntRect& textureRect);
	void SetEnableTileHover(bool isEnable);
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
	TileType tileType;
	bool isTileHoverEnable = true;

	sf::RenderWindow& window;
	std::vector<sf::RectangleShape> tiles;

	sf::Texture texture;
};