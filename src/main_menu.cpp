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

	for (std::string gameTitle : gameTitles)
	{
		gameTitlesButtons.emplace_back(
			gameTitle, 20,
			sf::Vector2f(
				window.getSize().x / 2,
				window.getSize().y / 2
			),
			sf::Vector2f(140.0f, 50.0f),
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
	for (int i = 0; i < gameTitlesButtons.size(); i++)
	{
		if (event.type == sf::Event::MouseButtonPressed)
		{
			if (event.mouseButton.button == sf::Mouse::Left &&
				gameTitlesButtons[i].IsTriggerable())
			{
				SetGameState(i);
			}
		}
	}
}

void MainMenu::Draw()
{
	switch (currentGame)
	{
	case GameState::NoGame:
		DrawTitle();
		DrawChooseMenu();
		break;
	case GameState::Tictactoe:
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
		gameTitlesButtons[i].SetButtonPosition(sf::Vector2f(
			window.getSize().x / 2,
			window.getSize().y / 2 + 50
		));
		gameTitlesButtons[i].Draw();
	}
}

void MainMenu::SetGameState(const int& gameTitleIndex)
{
	switch (gameTitleIndex)
	{
	case 0:
		currentGame = GameState::Tictactoe;
		break;
	default:
		currentGame = GameState::NoGame;
		break;
	}
}
