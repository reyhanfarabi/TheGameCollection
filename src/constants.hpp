#pragma once

#include <string>

namespace STR_CONST
{
	const std::string YOUR_TURN = "YOUR TURN";
	const std::string OPPONENT_TURN = "OPPONENT TURN";
	const std::string GAME_FINISH = "GAME FINISH!";
	const std::string RESTART_GAME = "RESTART GAME";
}

namespace ASSETS
{
	// Minesweeper Assets
	const std::string MINESWEEPER_TILES = "assets/sprites/minesweeper-tiles-64x64.png";
	const sf::Vector2i MINESWEEPER_TILE_SIZE = sf::Vector2i(64, 64);
}