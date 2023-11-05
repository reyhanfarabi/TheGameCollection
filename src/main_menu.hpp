#pragma once

#include "ui.hpp"
#include "base_game.hpp"
#include "tictactoe.hpp"
#include "minesweeper.hpp"

#include <SFML/Graphics.hpp>
#include <vector>

class MainMenu
{
public:
	MainMenu(sf::RenderWindow& wnd);
	void Update(sf::Event& event);
	void Draw();
	void DrawTitle();
	void DrawChooseMenu();

private:
	enum class GameState
	{
		Tictactoe,
		Minesweeper,
		NoGame
	};

private:
	void SetGame(const int& gameTitleIndex);

private:
	sf::RenderWindow& window;
	UI::Text title;
	UI::Text chooseGame;

	GameState currentGameState = GameState::NoGame;
	std::vector<std::unique_ptr<BaseGame>> currentGame;
	
	std::vector<std::string> gameTitles = { "Tic-tac-toe", "Minesweeper"};
	std::vector<UI::Button> gameTitlesButtons;
	const sf::Vector2f BTN_CHOOSE_SIZE = { 140.0f, 50.0f };

};