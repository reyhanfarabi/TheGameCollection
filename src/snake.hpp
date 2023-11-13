#pragma once

#include "base_game.hpp"
#include "board.hpp"
#include "constants.hpp"
#include "ui.hpp"

#include <SFML\Graphics.hpp>

class Snake : public BaseGame
{
public:
	Snake(sf::RenderWindow& wnd);
	void Update(sf::Event& event) override;
	void Draw() override;

private:
	static constexpr int TILE_SIZE = 20;
	static constexpr int GRID_WIDTH = 20;
	static constexpr int GRID_HEIGHT = 20;
	static constexpr int TILE_STATE_SIZE = GRID_WIDTH * GRID_HEIGHT;
	const float X_OFFSET;
	const float Y_OFFSET;

	sf::RenderWindow& window;
	Board board;
	UI::Text txtTitle;
};