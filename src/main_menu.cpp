#include "main_menu.hpp"

MainMenu::MainMenu(sf::RenderWindow& wnd)
	:
	window(wnd),
	title("The Game Collection", 36, sf::Color::White, sf::Vector2f(
		window.getSize().x / 2,
		200
	), window),
	chooseGame("Choose Game to Play", 18, sf::Color::White, sf::Vector2f(), window)
{
	gameTitlesButtons.reserve(gameTitles.size());

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
}

void MainMenu::Draw()
{
	switch (currentGameState)
	{
	case GameState::NoGame:
		DrawTitle();
		DrawChooseMenu();
		break;
	case GameState::Tictactoe:
	case GameState::Minesweeper:
		currentGame[0]->Draw();
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
