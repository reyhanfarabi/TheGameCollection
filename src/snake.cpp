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
	tileState(TILE_STATE_SIZE)
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
	snakeBodyLoc.emplace_back(sf::Vector2i(3, 8));
	tileState[GetTileIndex(snakeBodyLoc[0])] = State::Head;
}

void Snake::Update(sf::Event& event, float& dt)
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

	// update tile state
	std::fill(tileState.begin(), tileState.end(), State::Empty);
	tileState[GetTileIndex(snakeBodyLoc[0])] = State::Head;	

	// update snake position
	moveCounter += dt;
	if (moveCounter >= movePeriod)
	{
		moveCounter = 0.0f;
		snakeBodyLoc[0] += currDirection;
	}
}

void Snake::Draw()
{
	txtTitle.Draw();

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

int Snake::GetTileIndex(sf::Vector2i loc)
{
	return board.GetTileIndex(loc);
}
