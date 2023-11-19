#include "sfml_window.hpp"

SFMLWindow::SFMLWindow()
	:
	window(
		sf::VideoMode(
			WINDOW_WIDTH,
			WINDOW_HEIGHT
		),
		"The Game Collection",
		sf::Style::Titlebar | sf::Style::Close
	),
	mainMenu(window)
{}

void SFMLWindow::Run()
{
	while (window.isOpen())
	{
		dt = clock.restart().asSeconds();

		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			// handle close window
			case sf::Event::Closed:
				window.close();
				break;
			// handle mouse event
			case sf::Event::MouseButtonPressed:
				MouseEvent(event);
				break;
			// handle keyboard event
			case sf::Event::KeyPressed:
				KeyboardEvent(event);
				break;
			default:
				break;
			}
		}

		Update();

		window.clear();

		Draw();

		window.display();
	}
}

void SFMLWindow::MouseEvent(sf::Event& event)
{
	mainMenu.MouseEvent(event);
}

void SFMLWindow::KeyboardEvent(sf::Event& event)
{
	mainMenu.KeyboardEvent(event);
}

void SFMLWindow::Update()
{
	// update game logic here
	mainMenu.Update(dt);
}

void SFMLWindow::Draw()
{
	// draw assets here
	mainMenu.Draw();
}
