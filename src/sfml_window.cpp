#include "sfml_window.hpp"

SFMLWindow::SFMLWindow()
	:
	window(
		sf::VideoMode(
			WINDOW_WIDTH,
			WINDOW_HEIGHT
		),
		WINDOW_NAME,
		sf::Style::Titlebar | sf::Style::Close
	),
	tictactoe(window)
{}

void SFMLWindow::Run()
{
	while (window.isOpen())
	{
		dt = clock.restart().asSeconds();

		sf::Event event;
		while (window.pollEvent(event))
		{
			// handle close window
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}

			Update(event);
		}

		window.clear();

		Draw();

		window.display();
	}
}

void SFMLWindow::Update(sf::Event& event)
{
	// update game logic here
	tictactoe.Update(event);
}

void SFMLWindow::Draw()
{
	// draw assets here
	tictactoe.Draw();
}
