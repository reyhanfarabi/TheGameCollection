#include "board.hpp"

#include <iostream>

Board::Board(
	int tileSize, 
	int gridWidth,
	int gridHeight,
	int outlineThickness,
	float xOffset,
	float yOffset,
	sf::RenderWindow& window,
	TileType type = Board::TileType::Empty
)	:
	TILE_SIZE(tileSize),
	GRID_WIDTH(gridWidth),
	GRID_HEIGHT(gridHeight),
	X_OFFSET(xOffset),
	Y_OFFSET(yOffset),
	tileType(type),
	window(window),
	tiles(GRID_WIDTH * GRID_HEIGHT)
{
	for (int y = 0; y < GRID_HEIGHT; y++)
	{
		for (int x = 0; x < GRID_WIDTH; x++)
		{
			// set tile properties
			GetTile({ x, y }).setSize(sf::Vector2f(TILE_SIZE, TILE_SIZE));
			GetTile({ x, y }).setPosition(
				static_cast<float>(x * TILE_SIZE + X_OFFSET),
				static_cast<float>(y * TILE_SIZE + Y_OFFSET)
			);

			GetTile({ x, y }).setFillColor(sf::Color::Black);
			GetTile({ x, y }).setOutlineThickness(outlineThickness);
			GetTile({ x, y }).setOutlineColor(sf::Color::White);
		}
	}
}

Board::Board(
	int tileSize,
	int gridWidth,
	int gridHeight,
	int outlineThickness,
	float xOffset,
	float yOffset,
	sf::RenderWindow& wnd,
	TileType type,
	std::string spriteFile,
	sf::Vector2i spritePosition,
	sf::Vector2i spriteSize
)	:
	Board(
		tileSize,
		gridWidth, gridHeight,
		outlineThickness,
		xOffset, yOffset,
		wnd, type
	)
{
	if (!texture.loadFromFile(spriteFile))
	{
		std::cout << "Failed to load texture file\n";
	}
	else
	{
		texture.setSmooth(true);

		for (int y = 0; y < GRID_HEIGHT; y++)
		{
			for (int x = 0; x < GRID_WIDTH; x++)
			{
				// set tile texture properties
				GetTile({ x, y }).setFillColor(sf::Color::White);
				GetTile({ x, y }).setOutlineThickness(outlineThickness);
				GetTile({ x, y }).setTexture(&texture, true);
				GetTile({ x, y }).setTextureRect(sf::IntRect(
					spritePosition,
					spriteSize
				));
			}
		}
	}
}

void Board::DrawTile(const sf::Vector2i& tilePos)
{
	if (isTileHoverEnable)
	{
		// highlight tile when hover
		HoverTile(GetTile(tilePos));
	}

	// draw tile
	window.draw(GetTile(tilePos));
}

void Board::SetTileColor(const sf::Vector2i& tilePos, const sf::Color color)
{
	GetTile(tilePos).setFillColor(color);
}

void Board::SetTileTextureRect(const sf::Vector2i& tilePos, const sf::IntRect& textureRect)
{
	GetTile(tilePos).setTextureRect(textureRect);
}

void Board::SetEnableTileHover(bool isEnable)
{
	isTileHoverEnable = isEnable;
}

sf::Vector2i Board::GetHoveredTilePos()
{
	for (int y = 0; y < GRID_HEIGHT; y++)
	{
		for (int x = 0; x < GRID_WIDTH; x++)
		{
			if (IsInsideTile(GetTile({ x, y }), sf::Mouse::getPosition(window)))
			{
				return sf::Vector2i(x, y);
			}
		}
	}

	return sf::Vector2i();
}

int Board::GetTileIndex(const sf::Vector2i& tilePos)
{
	return GRID_HEIGHT * tilePos.y + tilePos.x;
}

bool Board::IsInsideTile(const sf::RectangleShape& tile, const sf::Vector2i& target)
{
	return
		target.x >= tile.getPosition().x &&
		target.x <= tile.getPosition().x + TILE_SIZE &&
		target.y >= tile.getPosition().y &&
		target.y <= tile.getPosition().y + TILE_SIZE;
}

void Board::HoverTile(sf::RectangleShape& tile)
{
	if (IsInsideTile(tile, sf::Mouse::getPosition(window)))
	{
		tile.setFillColor(sf::Color(255, 255, 255, 225));
	}
	// do not add else condition, color is intended to be stuck after hover
	// stuck issue should be fix on game module by setting color to it
	// see example on tictactoe update method
}

sf::RectangleShape& Board::GetTile(const sf::Vector2i tilePos)
{
	return tiles[GetTileIndex(tilePos)];
}
