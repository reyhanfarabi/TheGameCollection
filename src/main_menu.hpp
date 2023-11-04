#pragma once

#include "ui.hpp"

#include <SFML/Graphics.hpp>

class MainMenu
{
public:
	MainMenu(sf::RenderWindow& wnd);
	void Draw();
	void DrawTitle();

private:
	sf::RenderWindow& window;
	UI::Text title;
};