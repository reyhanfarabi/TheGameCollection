#pragma once

#include "ui.hpp"

#include <SFML/Graphics.hpp>
#include <vector>

class MainMenu
{
public:
	MainMenu(sf::RenderWindow& wnd);
	void Draw();
	void DrawTitle();
	void DrawChooseMenu();

private:
	sf::RenderWindow& window;
	UI::Text title;
	UI::Text chooseGame;
	
	std::vector<std::string> gameTitles = { "Tic-tac-toe" };
	std::vector<UI::Button> gameTitlesButtons;
};