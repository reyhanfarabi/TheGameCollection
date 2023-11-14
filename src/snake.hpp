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
	void Update(sf::Event& event, float& dt) override;
	void Draw() override;

private:
	enum class State
	{
		Head,
		Body,
		Empty,
		Food
	};

private:
	void InitRectPlayArea();
	int GetTileIndex(sf::Vector2i loc);

private:
	static constexpr int TILE_SIZE = 20;
	static constexpr int GRID_WIDTH = 20;
	static constexpr int GRID_HEIGHT = 20;
	static constexpr int TILE_STATE_SIZE = GRID_WIDTH * GRID_HEIGHT;
	const float X_OFFSET;
	const float Y_OFFSET;

	sf::RenderWindow& window;
	Board board;
	sf::RectangleShape rectPlayArea;
	UI::Text txtTitle;

	float movePeriod = 0.4f;
	float moveCounter = 0.0f;
	const sf::Vector2i UP = sf::Vector2i(0, -1);
	const sf::Vector2i DOWN = sf::Vector2i(0, 1);
	const sf::Vector2i RIGHT = sf::Vector2i(1, 0);
	const sf::Vector2i LEFT = sf::Vector2i(-1, 0);
	sf::Vector2i currDirection = RIGHT;
	std::vector<sf::Vector2i> snakeBodyLoc;
	std::vector<State> tileState;
	sf::Vector2i foodLoc;
};