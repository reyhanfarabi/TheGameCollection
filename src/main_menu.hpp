#pragma once

#include "ui.hpp"
#include "base_game.hpp"
#include "tictactoe.hpp"
#include "minesweeper.hpp"
#include "snake.hpp"
#include "battleship.hpp"

#include <SFML/Graphics.hpp>
#include <vector>

class MainMenu
{
public:
	MainMenu(sf::RenderWindow& wnd);
	void InitBackground();
	void Update(float& dt);
	void MouseEvent(sf::Event& event);
	void KeyboardEvent(sf::Event& event);
	void Draw();
	void DrawTitle();
	void DrawChooseMenu();

private:
	enum class GameState
	{
		Tictactoe,
		Minesweeper,
		Snake,
		BattleShip,
		NoGame
	};

private:
	void SetGame(const int& gameTitleIndex);
	void GoBackToMainMenu();
	void ChooseButtonEvents();

private:
	sf::RenderWindow& window;
	UI::Text title;
	UI::Text chooseGame;
	UI::Text buildVersion;
	UI::Button btnMainMenu;

	GameState currentGameState = GameState::NoGame;
	std::vector<std::unique_ptr<BaseGame>> currentGame;
	
	std::vector<std::string> gameTitles = {
		"TIC-TAC-TOE",
		"MINESWEEPER",
		"SNAKE",
		"BATTLESHIP"
	};
	std::vector<UI::Button> gameTitlesButtons;
	const sf::Vector2f BTN_CHOOSE_SIZE = { 175.0f, 50.0f };

	sf::VertexArray gradOverlay;
	sf::RectangleShape bgRect;
	sf::Texture bgImages[ASSETS::MAINMENU_BACKGROUND_SIZE];
};