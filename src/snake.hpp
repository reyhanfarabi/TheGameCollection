#pragma once

#include "base_game.hpp"
#include "board.hpp"
#include "constants.hpp"
#include "ui.hpp"

#include <SFML\Graphics.hpp>
#include <deque>
#include <random>

class Snake : public BaseGame
{
public:
	Snake(sf::RenderWindow& wnd);
	void Update(float& dt) override;
	void MouseEvent(sf::Event& event) override;
	void KeyboardEvent(sf::Event& event) override;
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
	void DrawScore();
	void TriggerRestart();
	void SetGameStartCondition();
	int GetTileIndex(sf::Vector2i loc);
	sf::Vector2i GetRandomDirection();
	sf::Vector2i GenerateNewFoodLocation();
	bool IsNextLocInsidePlayArea(const sf::Vector2i& nextLoc);
	bool IsNextLocNotSelf(const sf::Vector2i& nextLoc);		// check if next loc is not to snake itself

private:
	static constexpr int TILE_SIZE = 20;
	static constexpr int GRID_WIDTH = 20;
	static constexpr int GRID_HEIGHT = 20;
	static constexpr int TILE_STATE_SIZE = GRID_WIDTH * GRID_HEIGHT;
	static constexpr int FOOD_POINT = 200;
	const float X_OFFSET;
	const float Y_OFFSET;
	bool isGameOver = false;
	int score = 0;

	sf::RenderWindow& window;
	Board board;
	sf::RectangleShape rectPlayArea;
	UI::Text txtTitle;
	UI::Text txtEndGame;
	UI::Text txtScore;
	UI::Button btnRestart;

	float movePeriod = 0.4f;
	float movePeriodMin = 0.1f;
	float movePeriodReduceFactor = 0.02f;
	float moveCounter = 0.0f;
	const sf::Vector2i UP = sf::Vector2i(0, -1);
	const sf::Vector2i DOWN = sf::Vector2i(0, 1);
	const sf::Vector2i RIGHT = sf::Vector2i(1, 0);
	const sf::Vector2i LEFT = sf::Vector2i(-1, 0);
	sf::Vector2i currDirection = RIGHT;
	std::deque<sf::Vector2i> snakeBodyLoc;
	std::vector<State> tileState;
	sf::Vector2i foodLoc;

	std::random_device rd;
	std::mt19937 gen;
	std::uniform_int_distribution<int> xDist;
	std::uniform_int_distribution<int> yDist;
	std::uniform_int_distribution<int> dirDist;
};