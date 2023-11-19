#pragma once

#include "tictactoe.hpp"
#include "main_menu.hpp"

#include <SFML\Graphics.hpp>
#include <SFML\System\Clock.hpp>

#include <string>

class SFMLWindow
{
public:
	SFMLWindow();
	void Run();

private:
	void MouseEvent(sf::Event& event);
	void KeyboardEvent(sf::Event& event);
	void Update();
	void Draw();

private:
	sf::RenderWindow window;
	sf::Clock clock;
	MainMenu mainMenu;

	static constexpr int WINDOW_WIDTH = 800;
	static constexpr int WINDOW_HEIGHT = 600;
	float dt = 0.0f;
};