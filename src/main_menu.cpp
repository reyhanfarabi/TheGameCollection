#include "main_menu.hpp"

#include <iostream>

MainMenu::MainMenu(sf::RenderWindow& wnd)
	:
	window(wnd),
	title("The Game Collection", 40, sf::Color::White, sf::Vector2f(), window),
	chooseGame("Choose Game to Play", 18, sf::Color::White, sf::Vector2f(), window),
	buildVersion("v" + BUILD_NUMBER, 18, sf::Color::White, sf::Vector2f(), window),
	btnMainMenu(
		"Esc | Main Menu", 16,
		sf::Vector2f(),
		UI::Padding(14.0f, 8.0f),
		sf::Color::White, sf::Color::Black,
		sf::Color::Black, sf::Color::White,
		1, sf::Color::White, sf::Color::White,
		window),
	gradOverlay(sf::Quads, 4)
{
	gameTitlesButtons.reserve(gameTitles.size());

	// init main menu background
	InitBackground();

	// set title position
	title.SetPosition(sf::Vector2f(
		title.GetSize().x / 2 + 50,
		100
	));

	// set choose game text position
	chooseGame.SetPosition(sf::Vector2f(
		chooseGame.GetSize().x / 2 + 50,
		window.getSize().y / 2 - 15
	));

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
				(BTN_CHOOSE_SIZE.x * i) + (BTN_CHOOSE_SIZE.x / 2) + 50,
				window.getSize().y / 2 + 35
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

void MainMenu::InitBackground()
{
	// load all background image texture
	for (int i = 0; i < ASSETS::MAINMENU_BACKGROUND_SIZE; i++)
	{
		if (!bgImages[i].loadFromFile(ASSETS::MAINMENU_BACKGROUND[i]))
		{
			std::cout << "failed to load texture";
		}
		else
		{
			bgImages[i].setSmooth(true);
		}
	}

	// init game image rect container
	bgRect.setSize(sf::Vector2f(window.getSize().y, window.getSize().y));
	bgRect.setFillColor(sf::Color::White);
	bgRect.setPosition(window.getSize().x - bgRect.getSize().x, 0);
	bgRect.setTexture(&bgImages[1]);

	// init gradient overlay
	gradOverlay[0].position = sf::Vector2f(window.getSize().x - bgRect.getSize().x, 0);
	gradOverlay[0].color = sf::Color::Black;
	gradOverlay[1].position = sf::Vector2f(window.getSize().x - bgRect.getSize().x, window.getSize().y);
	gradOverlay[1].color = sf::Color::Black;
	gradOverlay[2].position = sf::Vector2f(window.getSize().x, window.getSize().y);
	gradOverlay[2].color = sf::Color(0, 0, 0, 100);
	gradOverlay[3].position = sf::Vector2f(window.getSize().x, 0);
	gradOverlay[3].color = sf::Color(0, 0, 0, 100);
}

void MainMenu::Update(sf::Event& event, float& dt)
{
	// change background image base on last hovered game button
	for (int i = 0; i < gameTitlesButtons.size(); i++)
	{
		if (gameTitlesButtons[i].IsTriggerable())
		{
			bgRect.setTexture(&bgImages[i], true);
		}
	}

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
		currentGame[0]->Update(event, dt);
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
		window.draw(bgRect);
		window.draw(gradOverlay);
		DrawTitle();
		DrawChooseMenu();
		buildVersion.Draw();
		break;
	case GameState::Tictactoe:
	case GameState::Minesweeper:
	case GameState::Snake:
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
	case 2:
		currentGameState = GameState::Snake;
		currentGame.emplace_back(std::make_unique<Snake>(window));
		break;
	default:
		currentGameState = GameState::NoGame;
		break;
	}
}
