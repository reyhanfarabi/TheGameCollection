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
	enum class State
	{
		EmptyHidden,	// this is default state when game start
		EmptyShowed,
		BombHidden,
		BombShowed,
		Flagged
	};

private:
	void SetAllStateDefault();

private:
	static constexpr int TILE_SIZE = 30;
	static constexpr int GRID_WIDTH = 12;
	static constexpr int GRID_HEIGHT = 12;
	static constexpr int TILE_STATE_SIZE = GRID_WIDTH * GRID_HEIGHT;
	const float X_OFFSET;
	const float Y_OFFSET;

	sf::RenderWindow& window;
	Board board;
	std::vector<State> tileState;
};