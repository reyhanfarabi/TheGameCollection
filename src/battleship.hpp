#pragma once

#include "base_game.hpp"
#include "board.hpp"

#include <SFML\Graphics.hpp>

class Battleship : public BaseGame
{
public:
	Battleship(sf::RenderWindow& window);
	void Update(float& dt) override;
	void MouseEvent(sf::Event& event) override;
	void KeyboardEvent(sf::Event& event) override;
	void Draw() override;

private:
	static constexpr int TILE_SIZE = 30;
	static constexpr int GRID_WIDTH = 10;
	static constexpr int GRID_HEIGHT = 10;
	static constexpr int TILE_STATE_SIZE = GRID_WIDTH * GRID_HEIGHT;
	const float X_OFFSET;
	const float Y_OFFSET;

	sf::RenderWindow& window;
	Board board;
};