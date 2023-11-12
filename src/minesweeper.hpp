#pragma once

#include "base_game.hpp"
#include "board.hpp"
#include "ui.hpp"

#include <SFML\Graphics.hpp>
#include <random>

class Minesweeper : public BaseGame
{
public:
	Minesweeper(sf::RenderWindow& wnd);
	void Update(sf::Event& event) override;
	void Draw() override;

private:
	enum class State
	{
		Hidden,	// this is default state when game start
		Opened,
		Flagged
	};

private:
	void SetAllStateDefault();
	void PlaceBombToTiles(const int& clickedTileIndex);
	void SetTilesAdjoiningBombCount();
	void AutoOpenTile();
	void TriggerGameOver();
	void TriggerRestart();
	bool IsAllEmptyTileOpen();
	int GetHoveredTileIndex();

private:
	static constexpr int TILE_SIZE = 30;
	static constexpr int GRID_WIDTH = 12;
	static constexpr int GRID_HEIGHT = 12;
	static constexpr int TILE_STATE_SIZE = GRID_WIDTH * GRID_HEIGHT;
	int clickedBombIndex = -1;
	const float X_OFFSET;
	const float Y_OFFSET;
	bool isGameOver = false;
	bool isBombPlaced = false;

	sf::RenderWindow& window;
	Board board;
	UI::Button btnRestart;
	UI::Text txtEndGame;
	UI::Text txtTitle;

	std::vector<State> tileState;
	std::vector<bool> bombLoc;
	std::vector<int> tileAdjoiningBombCount;

	std::random_device rd;
	std::mt19937 gen;
	std::uniform_int_distribution<int> dist;
};
