#pragma once

#include "base_game.hpp"
#include "board.hpp"

#include <SFML\Graphics.hpp>

class Minesweeper : public BaseGame
{
public:
	Minesweeper(sf::RenderWindow& wnd);
	void Update(sf::Event& event) override;
	void Draw() override;

private:
	static constexpr int TILE_SIZE = 50;
	static constexpr int GRID_WIDTH = 10;
	static constexpr int GRID_HEIGHT = 10;
	const float X_OFFSET;
	const float Y_OFFSET;

	sf::RenderWindow& window;
	Board board;
};