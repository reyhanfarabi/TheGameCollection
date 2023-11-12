#include "main_menu.hpp"

MainMenu::MainMenu(sf::RenderWindow& wnd)
	:
	window(wnd),
	title("The Game Collection", 36, sf::Color::White, sf::Vector2f(
		window.getSize().x / 2,
		200
	), window),
	chooseGame("Choose Game to Play", 18, sf::Color::White, sf::Vector2f(), window),
	buildVersion("v" + BUILD_NUMBER, 18, sf::Color::White, sf::Vector2f(), window),
	btnMainMenu(
		"Esc | Main Menu", 16,
		sf::Vector2f(),
		UI::Padding(14.0f, 8.0f),
		sf::Color::White, sf::Color::Black,
		sf::Color::Black, sf::Color::White,
		1, sf::Color::White, sf::Color::White,
		window)
{
	gameTitlesButtons.reserve(gameTitles.size());

	// set btnMainMenu position
	btnMainMenu.SetButtonPosition(sf::Vector2f(
		// both subtract by 10 for spacing
		window.getSize().x - btnMainMenu.GetButtonSize().x / 2 - 10,
		window.getSize().y - btnMainMenu.GetButtonSize().y / 2 - 10
	));

	// set build version text position
	buildVersion.SetPosition(sf::Vector2f(
		buildVersion.GetSize().x / 2 + 10,
		window.getSize().y - buildVersion.GetSize().y / 2 - 15
	));

	for (int i = 0; i < gameTitles.size(); i++)
	{
		gameTitlesButtons.emplace_back(
			gameTitles[i], 20,
			sf::Vector2f(
				window.getSize().x / 2 + (BTN_CHOOSE_SIZE.x * i) - (BTN_CHOOSE_SIZE.x / 2),
				// add 50 for spacing on y-axis
				window.getSize().y / 2 + 50
			),
			BTN_CHOOSE_SIZE,
			UI::Padding(0.0f, 0.0f),
			sf::Color::White, sf::Color::Black,
			sf::Color::Black, sf::Color::White,
			1, sf::Color::White, sf::Color::White,
			window
		);
	}
}

void MainMenu::Update(sf::Event& event)
{
	if (currentGameState == GameState::NoGame)
	{
		for (int i = 0; i < gameTitlesButtons.size(); i++)
		{
			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == sf::Mouse::Left &&
					gameTitlesButtons[i].IsTriggerable())
				{
					SetGame(i);
				}
			}
		}
	}
	else
	{
		currentGame[0]->Update(event);
	}

	// game module event
	if (currentGameState != GameState::NoGame)
	{
		// mouse event
		if (event.type == sf::Event::MouseButtonPressed)
		{
			// go back to menu when button main menu is clicked
			if (event.mouseButton.button == sf::Mouse::Left && btnMainMenu.IsTriggerable())
			{
				GoBackToMainMenu();
			}
		}

		// keyboard event
		if (event.type == sf::Event::KeyPressed)
		{
			// go back to menu when escape key is pressed 
			if (event.key.scancode == sf::Keyboard::Scan::Escape)
			{
				GoBackToMainMenu();
			}
		}
	}
}

void MainMenu::Draw()
{
	switch (currentGameState)
	{
	case GameState::NoGame:
		DrawTitle();
		DrawChooseMenu();
		buildVersion.Draw();
		break;
	case GameState::Tictactoe:
	case GameState::Minesweeper:
		currentGame[0]->Draw();
		btnMainMenu.Draw();
		break;
	default:
		DrawTitle();
		DrawChooseMenu();
		break;
	}
}

void MainMenu::DrawTitle()
{
	title.Draw();
}

void MainMenu::DrawChooseMenu()
{
	chooseGame.SetPosition(sf::Vector2f(
		window.getSize().x / 2,
		window.getSize().y / 2
	));
	chooseGame.Draw();

	for (int i = 0; i < gameTitlesButtons.size(); i++)
	{
		gameTitlesButtons[i].Draw();
	}
}

void MainMenu::GoBackToMainMenu()
{
	currentGameState = GameState::NoGame;
	currentGame.clear();
}

void MainMenu::SetGame(const int& gameTitleIndex)
{
	currentGame.clear();
	switch (gameTitleIndex)
	{
	case 0:
		currentGameState = GameState::Tictactoe;
		currentGame.emplace_back(std::make_unique<TicTacToe>(window));
		break;
	case 1:
		currentGameState = GameState::Minesweeper;
		currentGame.emplace_back(std::make_unique<Minesweeper>(window));
		break;
	default:
		currentGameState = GameState::NoGame;
		break;
	}
}
