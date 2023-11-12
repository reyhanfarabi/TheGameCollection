#pragma once

#include <string>

static const std::string BUILD_NUMBER = "1.1.2";

namespace STR_CONST
{
	const std::string YOUR_TURN = "YOUR TURN";
	const std::string OPPONENT_TURN = "OPPONENT TURN";
	const std::string GAME_FINISH = "GAME FINISH!";
	const std::string RESTART_GAME = "RESTART GAME";
	const std::string YOU_LOSE = "YOU LOSE";
	const std::string YOU_WIN = "YOU WIN";
}

namespace ASSETS
{
	//
	// Main Menu Assets
	//
	const int MAINMENU_BACKGROUND_SIZE = 2;
	const std::string MAINMENU_BACKGROUND[MAINMENU_BACKGROUND_SIZE] = {
		"assets/pics/tictactoe.png",
		"assets/pics/minesweeper.png"
	};

	//
	// Minesweeper Assets
	//
	const std::string MINESWEEPER_SPRITES = "assets/sprites/minesweeper-tiles-64x64.png";
	const sf::Vector2i MINESWEEPER_TILE_SIZE = sf::Vector2i(64, 64);

	namespace MS_SPRITE_POS
	{
		const sf::Vector2i HIDDEN = sf::Vector2i(64, 0);
		const sf::Vector2i FLAGGED = sf::Vector2i(128, 0);
		const sf::Vector2i BOMB_EXPLODE = sf::Vector2i(192, 0);
		const sf::Vector2i BOMB_HIDDEN = sf::Vector2i(256, 0);
		const sf::Vector2i TILE_0 = sf::Vector2i(0, 0);
		const sf::Vector2i TILE_1 = sf::Vector2i(0, 64);
		const sf::Vector2i TILE_2 = sf::Vector2i(64, 64);
		const sf::Vector2i TILE_3 = sf::Vector2i(128, 64);
		const sf::Vector2i TILE_4 = sf::Vector2i(192, 64);
		const sf::Vector2i TILE_5 = sf::Vector2i(0, 128);
		const sf::Vector2i TILE_6 = sf::Vector2i(64, 128);
		const sf::Vector2i TILE_7 = sf::Vector2i(128, 128);
		const sf::Vector2i TILE_8 = sf::Vector2i(192, 128);
	}
}