#include "minesweeper.hpp"
#include "constants.hpp"

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
					tileSprite = ASSETS::MS_SPRITE_POS::BOMB_EXPLODE;
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
	for (int i = 0; i < TILE_STATE_SIZE; i++)
	{
		if (i != clickedTileIndex)
		{
			// random number is negated to get lower amount of bomb
			bombLoc[i] = !dist(gen);
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

int Minesweeper::GetHoveredTileIndex()
{
	return board.GetTileIndex(board.GetHoveredTilePos());
}
