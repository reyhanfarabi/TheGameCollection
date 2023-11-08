#include "board.hpp"

Board::Board(
	int tileSize, 
	int gridWidth,
	int gridHeight,
	float xOffset,
	float yOffset,
	sf::RenderWindow& window,
	bool enableWithSymbol
)	:
	TILE_SIZE(tileSize),
	GRID_WIDTH(gridWidth),
	GRID_HEIGHT(gridHeight),
	X_OFFSET(xOffset),
	Y_OFFSET(yOffset),
	enableWithSymbol(enableWithSymbol),
	window(window),
	tiles(GRID_WIDTH * GRID_HEIGHT)
{
	if (enableWithSymbol)
	{
		tileSymbols.reserve(GRID_WIDTH * GRID_HEIGHT);
	}

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
			GetTile({ x, y }).setOutlineThickness(1);
			GetTile({ x, y }).setOutlineColor(sf::Color::White);

			if (enableWithSymbol)
			{
				tileSymbols.emplace_back("", 14, sf::Color::White, sf::Vector2f(
					GetTile({ x, y }).getPosition().x + TILE_SIZE / 3,
					GetTile({ x, y }).getPosition().y + TILE_SIZE / 4
				), window);
			}
		}
	}
}

void Board::DrawTile(const sf::Vector2i& tilePos)
{
	// highlight tile when hover
	HoverTile(GetTile(tilePos));

	// draw tile
	window.draw(GetTile(tilePos));
}

void Board::DrawTileWithSymbol(const sf::Vector2i& tilePos, const std::string& symbol)
{
	DrawTile(tilePos);

	tileSymbols[GetTileIndex(tilePos)].SetString(symbol);
	tileSymbols[GetTileIndex(tilePos)].Draw();
}

void Board::SetTileColor(const sf::Vector2i& tilePos, const sf::Color color)
{
	GetTile(tilePos).setFillColor(color);
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
		tile.setFillColor(sf::Color::White);
	}
	// do not add else condition, color is intended to be stuck after hover
	// stuck issue should be fix on game module by setting color to it
	// see example on tictactoe update method
}

sf::RectangleShape& Board::GetTile(const sf::Vector2i tilePos)
{
	return tiles[GetTileIndex(tilePos)];
}
