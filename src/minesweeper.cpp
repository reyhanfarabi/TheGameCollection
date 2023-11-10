#include "minesweeper.hpp"
#include "constants.hpp"

#include <set>

Minesweeper::Minesweeper(sf::RenderWindow& wnd)
	:
	window(wnd),
	X_OFFSET((wnd.getSize().x / 2) - (GRID_WIDTH * TILE_SIZE / 2)),
	Y_OFFSET((wnd.getSize().y / 2) - (GRID_HEIGHT * TILE_SIZE / 2)),
	board(
		TILE_SIZE,
		GRID_WIDTH, GRID_HEIGHT,
		X_OFFSET, Y_OFFSET,
		window,
		Board::TileType::Sprite,
		ASSETS::MINESWEEPER_SPRITES,
		sf::Vector2i(64, 0),
		ASSETS::MINESWEEPER_TILE_SIZE
	),
	btnRestart(
		STR_CONST::RESTART_GAME, 20,
		sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2 + 210),
		UI::Padding(14.0f, 8.0f),
		sf::Color::White, sf::Color::Black,
		sf::Color::Black, sf::Color::White,
		1, sf::Color::White, sf::Color::White,
		window),
	tileState(TILE_STATE_SIZE),
	bombLoc(TILE_STATE_SIZE),
	tileAdjoiningBombCount(TILE_STATE_SIZE),
	gen(rd()),
	dist(0, 3)	// max set to 3 is to generate more true value instead of false
{
	SetAllStateDefault();
}

void Minesweeper::Update(sf::Event& event)
{
	if (!isGameOver)
	{
		if (event.type == sf::Event::MouseButtonPressed)
		{
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				// place bombs on first tile click (start of game)
				if (!isBombPlaced)
				{
					PlaceBombToTiles(GetHoveredTileIndex());
					isBombPlaced = true;
					SetTilesAdjoiningBombCount();
				}

				// set tile to opened if current state is hidden
				if (tileState[GetHoveredTileIndex()] == State::Hidden)
				{
					tileState[GetHoveredTileIndex()] = State::Opened;
				}

				// set game over when clicked tile have bomb
				TriggerGameOver();
			}
			else if (event.mouseButton.button == sf::Mouse::Right)
			{
				// place bombs on first tile click (start of game)
				if (!isBombPlaced)
				{
					PlaceBombToTiles(GetHoveredTileIndex());
					isBombPlaced = true;
					SetTilesAdjoiningBombCount();
				}
				
				// set tile to be flagged if current state is hidden
				if (tileState[GetHoveredTileIndex()] == State::Hidden)
				{
					tileState[GetHoveredTileIndex()] = State::Flagged;
				}
				// remove flag if current state is flagged
				else if (tileState[GetHoveredTileIndex()] == State::Flagged)
				{
					tileState[GetHoveredTileIndex()] = State::Hidden;
				}
			}
		}

		if (isBombPlaced)
		{
			AutoOpenTile();
		}
	}
	else
	{
		if (event.type == sf::Event::MouseButtonPressed)
		{
			if (event.mouseButton.button == sf::Mouse::Left && btnRestart.IsTriggerable())
			{
				TriggerRestart();
			}
		}
	}
}

void Minesweeper::Draw()
{
	for (int y = 0; y < GRID_HEIGHT; y++)
	{
		for (int x = 0; x < GRID_WIDTH; x++)
		{
			sf::Vector2i tileSprite = ASSETS::MS_SPRITE_POS::HIDDEN;

			// set tile sprite base on current state of each tile
			switch (tileState[GRID_HEIGHT * y + x])
			{
			case State::Hidden:
				tileSprite = ASSETS::MS_SPRITE_POS::HIDDEN;
				break;
			case State::Opened:
				if (bombLoc[board.GetTileIndex({ x, y })])
				{
					if (board.GetTileIndex({ x, y }) == clickedBombIndex)
					{
						tileSprite = ASSETS::MS_SPRITE_POS::BOMB_EXPLODE;
					}
					else
					{
						tileSprite = ASSETS::MS_SPRITE_POS::BOMB_HIDDEN;
					}
				}
				else
				{
					switch (tileAdjoiningBombCount[board.GetTileIndex({ x, y })])
					{
					case 0:
						tileSprite = ASSETS::MS_SPRITE_POS::TILE_0;
						break;
					case 1:
						tileSprite = ASSETS::MS_SPRITE_POS::TILE_1;
						break;
					case 2:
						tileSprite = ASSETS::MS_SPRITE_POS::TILE_2;
						break;
					case 3:
						tileSprite = ASSETS::MS_SPRITE_POS::TILE_3;
						break;
					case 4:
						tileSprite = ASSETS::MS_SPRITE_POS::TILE_4;
						break;
					case 5:
						tileSprite = ASSETS::MS_SPRITE_POS::TILE_5;
						break;
					case 6:
						tileSprite = ASSETS::MS_SPRITE_POS::TILE_6;
						break;
					case 7:
						tileSprite = ASSETS::MS_SPRITE_POS::TILE_7;
						break;
					case 8:
						tileSprite = ASSETS::MS_SPRITE_POS::TILE_8;
						break;
					default:
						tileSprite = ASSETS::MS_SPRITE_POS::TILE_0;
						break;
					}
				}
				break;
			case State::Flagged:
				tileSprite = ASSETS::MS_SPRITE_POS::FLAGGED;
				break;
			default:
				tileSprite = ASSETS::MS_SPRITE_POS::TILE_0;
				break;
			}

			board.SetTileTextureRect({ x, y }, sf::IntRect(
				tileSprite,
				ASSETS::MINESWEEPER_TILE_SIZE
			));
			board.SetTileColor({ x, y }, sf::Color::White);
			board.DrawTile({ x, y });
		}
	}

	if (isGameOver)
	{
		btnRestart.Draw();
	}
}

void Minesweeper::SetAllStateDefault()
{
	for (int i = 0; i < TILE_STATE_SIZE; i++)
	{
		tileState[i] = State::Hidden;
	}
}

void Minesweeper::PlaceBombToTiles(const int& clickedTileIndex)
{
	std::set<int> adjoiningIndex;
	adjoiningIndex.insert(clickedTileIndex - GRID_WIDTH);		// top
	adjoiningIndex.insert(clickedTileIndex + GRID_WIDTH);		// bottom
	adjoiningIndex.insert(clickedTileIndex + 1);				// right
	adjoiningIndex.insert(clickedTileIndex + 1 - GRID_WIDTH);	// top right
	adjoiningIndex.insert(clickedTileIndex + 1 + GRID_WIDTH);	// bottom right
	adjoiningIndex.insert(clickedTileIndex - 1);				// left
	adjoiningIndex.insert(clickedTileIndex - 1 - GRID_WIDTH);	// top left
	adjoiningIndex.insert(clickedTileIndex - 1 + GRID_WIDTH);	// bottom left

	for (int i = 0; i < TILE_STATE_SIZE; i++)
	{
		// place bomb outside one tile range base on clicked index
		if (adjoiningIndex.find(i) == adjoiningIndex.end())
		{
			// random number is negated to get lower amount of bomb
			bombLoc[i] = !dist(gen);
		}
		else
		{
			bombLoc[i] = false;
		}
	}
}

void Minesweeper::SetTilesAdjoiningBombCount()
{
	for (int y = 0; y < GRID_HEIGHT; y++)
	{
		for (int x = 0; x < GRID_WIDTH; x++)
		{
			int count = 0;
			int tileIndex = board.GetTileIndex({ x, y });

			// tile bound
			int rightBound = (GRID_WIDTH - 1) + (GRID_HEIGHT * y);
			int leftBound = GRID_HEIGHT * y;
			int topBound = x - GRID_WIDTH;
			int bottomBound = x + GRID_WIDTH * GRID_HEIGHT;

			// check tile right bound
			if (tileIndex + 1 <= rightBound)
			{
				// increment count when there is bomb on right adjoining tile
				if (bombLoc[tileIndex + 1]) { count++; }

				if (tileIndex - GRID_WIDTH > topBound)
				{
					// increment count when there is bomb on top right adjoining tile
					if (bombLoc[tileIndex + 1 - GRID_WIDTH]) { count++; }
				}

				if (tileIndex + GRID_WIDTH < bottomBound)
				{
					// increment count when there is bomb on bottom right adjoining tile
					if (bombLoc[tileIndex + 1 + GRID_WIDTH]) { count++; }
				}
			}

			// check tile left bound
			if (tileIndex - 1 >= leftBound)
			{
				// increment count when there is bomb on left adjoining tile
				if (bombLoc[tileIndex - 1]) { count++; }

				if (tileIndex - GRID_WIDTH > topBound)
				{
					// increment count when there is bomb on top left adjoining tile
					if (bombLoc[tileIndex - 1 - GRID_WIDTH]) { count++; }
				}

				if (tileIndex + GRID_WIDTH < bottomBound)
				{
					// increment count when there is bomb on bottom left adjoining tile
					if (bombLoc[tileIndex - 1 + GRID_WIDTH]) { count++; }
				}
			}

			// check tile top bound
			if (tileIndex - GRID_WIDTH > topBound)
			{
				// increment count when there is bomb on top adjoining tile
				if (bombLoc[tileIndex - GRID_WIDTH]) { count++; }
			}

			// check tile bottom bound
			if (tileIndex + GRID_WIDTH < bottomBound)
			{
				// increment count when there is bomb on bottom adjoining tile
				if (bombLoc[tileIndex + GRID_WIDTH]) { count++; }
			}

			tileAdjoiningBombCount[tileIndex] = count;
		}
	}
}

void Minesweeper::AutoOpenTile()
{
	// auto open tile when adjoining bomb count is 0 and state is hidden
	for (int y = 0; y < GRID_HEIGHT; y++)
	{
		for (int x = 0; x < GRID_WIDTH; x++)
		{
			int tileIndex = board.GetTileIndex({ x, y });

			// tile bound
			int rightBound = (GRID_WIDTH - 1) + (GRID_HEIGHT * y);
			int leftBound = GRID_HEIGHT * y;
			int topBound = x - GRID_WIDTH;
			int bottomBound = x + GRID_WIDTH * GRID_HEIGHT;

			if (tileState[tileIndex] == State::Hidden)
			{
				// check tile right bound
				if (tileIndex + 1 <= rightBound)
				{
					// open tile if right adjoining tile bomb count is 0 and state is hidden
					if (
						tileAdjoiningBombCount[tileIndex + 1] == 0 &&
						tileState[tileIndex + 1] == State::Opened &&
						!bombLoc[tileIndex + 1])
					{
						tileState[tileIndex] = State::Opened;
					}

					if (tileIndex - GRID_WIDTH > topBound)
					{
						// open tile if top right adjoining tile bomb count is 0 and state is hidden
						if (
							tileAdjoiningBombCount[tileIndex + 1 - GRID_WIDTH] == 0 &&
							tileState[tileIndex + 1 - GRID_WIDTH] == State::Opened &&
							!bombLoc[tileIndex + 1 - GRID_WIDTH])
						{
							tileState[tileIndex] = State::Opened;
						}
					}

					if (tileIndex + GRID_WIDTH < bottomBound)
					{
						// open tile if bottom right adjoining tile bomb count is 0 and state is hidden
						if (
							tileAdjoiningBombCount[tileIndex + 1 + GRID_WIDTH] == 0 &&
							tileState[tileIndex + 1 + GRID_WIDTH] == State::Opened &&
							!bombLoc[tileIndex + 1 + GRID_WIDTH])
						{
							tileState[tileIndex] = State::Opened;
						}
					}
				}

				// check tile left bound
				if (tileIndex - 1 >= leftBound)
				{
					// open tile if left adjoining tile bomb count is 0 and state is hidden
					if (
						tileAdjoiningBombCount[tileIndex - 1] == 0 &&
						tileState[tileIndex - 1] == State::Opened &&
						!bombLoc[tileIndex - 1])
					{
						tileState[tileIndex] = State::Opened;
					}

					if (tileIndex - GRID_WIDTH > topBound)
					{
						// open tile if top left adjoining tile bomb count is 0 and state is hidden
						if (
							tileAdjoiningBombCount[tileIndex - 1 - GRID_WIDTH] == 0 &&
							tileState[tileIndex - 1 - GRID_WIDTH] == State::Opened &&
							!bombLoc[tileIndex - 1 - GRID_WIDTH])
						{
							tileState[tileIndex] = State::Opened;
						}
					}

					if (tileIndex + GRID_WIDTH < bottomBound)
					{
						// open tile if bottom left adjoining tile bomb count is 0 and state is hidden
						if (
							tileAdjoiningBombCount[tileIndex - 1 + GRID_WIDTH] == 0 &&
							tileState[tileIndex - 1 + GRID_WIDTH] == State::Opened &&
							!bombLoc[tileIndex - 1 + GRID_WIDTH])
						{
							tileState[tileIndex] = State::Opened;
						}
					}
				}

				// check tile top bound
				if (tileIndex - GRID_WIDTH > topBound)
				{
					// open tile if top adjoining tile bomb count is 0 and state is hidden
					if (
						tileAdjoiningBombCount[tileIndex - GRID_WIDTH] == 0 &&
						tileState[tileIndex - GRID_WIDTH] == State::Opened &&
						!bombLoc[tileIndex - GRID_WIDTH])
					{
						tileState[tileIndex] = State::Opened;
					}
				}

				// check tile bottom bound
				if (tileIndex + GRID_WIDTH < bottomBound)
				{
					// open tile if bottom adjoining tile bomb count is 0 and state is hidden
					if (
						tileAdjoiningBombCount[tileIndex + GRID_WIDTH] == 0 &&
						tileState[tileIndex + GRID_WIDTH] == State::Opened &&
						!bombLoc[tileIndex + GRID_WIDTH])
					{
						tileState[tileIndex] = State::Opened;
					}
				}
			}
		}
	}
}

void Minesweeper::TriggerGameOver()
{
	if (bombLoc[GetHoveredTileIndex()])
	{
		isGameOver = true;
		clickedBombIndex = GetHoveredTileIndex();

		// set tile to open if it has bomb
		for (int i = 0; i < TILE_STATE_SIZE; i++)
		{
			if (bombLoc[i])
			{
				tileState[i] = State::Opened;
			}
		}
	}
}

void Minesweeper::TriggerRestart()
{
	isGameOver = false;
	isBombPlaced = false;
	clickedBombIndex = -1;
	
	// set all tile state to hidden
	SetAllStateDefault();

	// set all bombLoc to false
	std::fill(bombLoc.begin(), bombLoc.end(), false);

	// set all tile adjoining bomb count to 0
	std::fill(tileAdjoiningBombCount.begin(), tileAdjoiningBombCount.end(), 0);
}

int Minesweeper::GetHoveredTileIndex()
{
	return board.GetTileIndex(board.GetHoveredTilePos());
}
