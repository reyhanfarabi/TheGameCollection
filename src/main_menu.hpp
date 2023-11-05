#pragma once

#include "ui.hpp"

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
		NoGame
	};

private:
	void SetGameState(const int& gameTitleIndex);

private:
	sf::RenderWindow& window;
	UI::Text title;
	UI::Text chooseGame;
	GameState currentGame = GameState::NoGame;
	
	std::vector<std::string> gameTitles = { "Tic-tac-toe" };
	std::vector<UI::Button> gameTitlesButtons;
};