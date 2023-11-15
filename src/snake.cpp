#include "snake.hpp"

Snake::Snake(sf::RenderWindow& wnd)
	:
	X_OFFSET((wnd.getSize().x / 2) - (GRID_WIDTH * TILE_SIZE / 2)),
	Y_OFFSET((wnd.getSize().y / 2) - (GRID_HEIGHT * TILE_SIZE / 2)),
	window(wnd),
	board(
		TILE_SIZE,
		GRID_WIDTH, GRID_HEIGHT,
		0,
		X_OFFSET, Y_OFFSET,
		window,
		Board::TileType::Empty
	),
	txtTitle("SNAKE", 18, sf::Color::White, sf::Vector2f(0.0f, 0.0f), window),
	txtEndGame(STR_CONST::GAME_OVER, 24, sf::Color::White, sf::Vector2f(
		window.getSize().x / 2,
		window.getSize().y / 2 - 20
	), window),
	txtScore(std::to_string(score), 18, sf::Color::White, sf::Vector2f(0.0f, 0.0f), window),
	tileState(TILE_STATE_SIZE),
	gen(rd()),
	xDist(0, GRID_WIDTH - 1),
	yDist(0, GRID_HEIGHT - 1)
{
	// disable board tile hover
	board.SetEnableTileHover(false);

	// set position to text title
	txtTitle.SetPosition(sf::Vector2f(
		// subtract 10 for spacing
		txtTitle.GetSize().x / 2 + 10,
		// add 10 for spacing
		txtTitle.GetSize().y / 2 + 10
	));

	// init play area rect
	InitRectPlayArea();

	// init tile state
	for (int i = 0; i < TILE_STATE_SIZE; i++)
	{
		tileState[i] = State::Empty;
	}

	// set snake head location
	snakeBodyLoc.emplace_front(sf::Vector2i(3, 8));
	tileState[GetTileIndex(snakeBodyLoc[0])] = State::Head;

	// set food location
	foodLoc = GenerateNewFoodLocation();
}

void Snake::Update(sf::Event& event, float& dt)
{
	if (!isGameOver)
	{
		// keyboard event
		if (event.type == sf::Event::KeyPressed)
		{
			// set move direction base on pressed key
			switch (event.key.scancode)
			{
			case sf::Keyboard::Scan::Up:
				if (currDirection != DOWN) { currDirection = UP; }
				break;
			case sf::Keyboard::Scan::Down:
				if (currDirection != UP) { currDirection = DOWN; }
				break;
			case sf::Keyboard::Scan::Right:
				if (currDirection != LEFT) { currDirection = RIGHT; }
				break;
			case sf::Keyboard::Scan::Left:
				if (currDirection != RIGHT) { currDirection = LEFT; }
				break;
			}
		}

		// update snake position
		moveCounter += dt;
		if (moveCounter >= movePeriod)
		{
			moveCounter = 0.0f;
			sf::Vector2i nextLoc = snakeBodyLoc[0] + currDirection;
			if (IsNextLocInsidePlayArea(nextLoc) && IsNextLocNotSelf(nextLoc))
			{
				snakeBodyLoc.push_front(nextLoc);
				if (nextLoc == foodLoc)
				{
					// generate new food location
					foodLoc = GenerateNewFoodLocation();

					// speed up snake movement
					if (movePeriod > movePeriodMin) { movePeriod -= movePeriodReduceFactor; }

					// add score
					score += FOOD_POINT;
				}
				else
				{
					snakeBodyLoc.pop_back();
				}
			}
			else
			{
				isGameOver = true;
				return;
			}
		}

		// update tile state
		std::fill(tileState.begin(), tileState.end(), State::Empty);
		tileState[GetTileIndex(foodLoc)] = State::Food;
		tileState[GetTileIndex(snakeBodyLoc[0])] = State::Head;
		for (int i = 1; i < snakeBodyLoc.size(); i++)
		{
			tileState[GetTileIndex(snakeBodyLoc[i])] = State::Body;
		}
	}
	else
	{
		// TODO: add trigger to restart game
	}
}

void Snake::Draw()
{
	txtTitle.Draw();

	if (!isGameOver)
	{
		DrawScore();

		for (int y = 0; y < GRID_HEIGHT; y++)
		{
			for (int x = 0; x < GRID_WIDTH; x++)
			{
				switch (tileState[GetTileIndex(sf::Vector2i(x, y))])
				{
				case State::Head:
					board.SetTileColor({ x, y }, sf::Color::White);
					break;
				case State::Body:
					board.SetTileColor({ x, y }, sf::Color(255, 255, 255, 200));
					break;
				case State::Food:
					board.SetTileColor({ x, y }, sf::Color::Green);
					break;
				case State::Empty:
				default:
					board.SetTileColor({ x, y }, sf::Color::Black);
					break;
				}

				board.DrawTile(sf::Vector2i(x, y));
			}
		}

		window.draw(rectPlayArea);
	}
	else
	{
		txtEndGame.Draw();
		DrawScore();
		// TODO: add button to restart game
	}
}

void Snake::InitRectPlayArea()
{
	// set play area rect configuration
	rectPlayArea.setSize(sf::Vector2f(
		TILE_SIZE * GRID_WIDTH,
		TILE_SIZE * GRID_HEIGHT
	));
	rectPlayArea.setPosition(sf::Vector2f(X_OFFSET, Y_OFFSET));
	rectPlayArea.setOutlineThickness(1);
	rectPlayArea.setOutlineColor(sf::Color::White);
	rectPlayArea.setFillColor(sf::Color::Transparent);
}

void Snake::DrawScore()
{
	if (!isGameOver)
	{
		// set position on top right corner when game is still ongoing
		txtScore.SetPosition(sf::Vector2f(
			// subtract 10 for spacing
			window.getSize().x - txtScore.GetSize().x / 2 - 10,
			// add 10 for spacing
			txtScore.GetSize().y / 2 + 10
		));
		txtScore.SetString(std::to_string(score));
	}
	else
	{
		// set position on center below game over text when game is over
		txtScore.SetPosition(sf::Vector2f(
			window.getSize().x / 2,
			window.getSize().y / 2 + 20
		));
		txtScore.SetString("Your Final Score is " + std::to_string(score));
	}
	
	txtScore.Draw();
}

sf::Vector2i Snake::GenerateNewFoodLocation()
{
	sf::Vector2i newLoc = sf::Vector2i(xDist(gen), yDist(gen));
	auto itr = std::find(snakeBodyLoc.begin(), snakeBodyLoc.end(), newLoc);

	while (itr != snakeBodyLoc.end())
	{
		newLoc = sf::Vector2i(xDist(gen), yDist(gen));
	}

	return newLoc;
}

bool Snake::IsNextLocInsidePlayArea(const sf::Vector2i& nextLoc)
{
	return 
		nextLoc.x >= 0 &&
		nextLoc.x < GRID_WIDTH &&
		nextLoc.y >= 0 &&
		nextLoc.y < GRID_HEIGHT;
}

bool Snake::IsNextLocNotSelf(const sf::Vector2i& nextLoc)
{
	auto itr = std::find(snakeBodyLoc.begin(), snakeBodyLoc.end(), nextLoc);

	if (itr != snakeBodyLoc.end())
	{
		return false;
	}

	return true;
}

int Snake::GetTileIndex(sf::Vector2i loc)
{
	return board.GetTileIndex(loc);
}
