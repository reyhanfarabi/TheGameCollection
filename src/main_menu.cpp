#include "main_menu.hpp"

MainMenu::MainMenu(sf::RenderWindow& wnd)
	:
	window(wnd),
	title("The Game Collection", 24, sf::Color::White, sf::Vector2f(
		window.getSize().x / 2,
		window.getSize().y / 2
	), window)
{}

void MainMenu::Draw()
{
	DrawTitle();
}

void MainMenu::DrawTitle()
{
	title.Draw();
}
