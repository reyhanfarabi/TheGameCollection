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
	shape(100.0f)
{
	shape.setFillColor(sf::Color::Magenta);
	shape.setOrigin(100.0f, 100.0f);
	shape.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
}

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
	window.draw(shape);
}
