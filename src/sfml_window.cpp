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
	board(window)
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
		}

		window.clear();

		Update();
		Draw();

		window.display();
	}
}

void SFMLWindow::Update()
{
	// update game logic here
}

void SFMLWindow::Draw()
{
	// draw assets here
	board.DrawBoard();
}
