#include "includes.h"

Grid::Grid(sf::RenderWindow& window)
{
	// border setup
	border = sf::RectangleShape({ size * 10, size * 20 });
	border.setPosition({ (float)(window.getSize().x - size * 10) / 2,
						(float)(window.getSize().y - size * 20) / 2 });
	border.setFillColor(sf::Color::Transparent);
	border.setOutlineColor(sf::Color::White);
	border.setOutlineThickness(1);

	blocks.reserve(100);

	for (int i = 0; i < 200; i++) { // Initializing grid
		grid[i] = sf::RectangleShape({ size, size });
		grid[i].setPosition({ border.getPosition().x + size * (i % 10),
							border.getPosition().y + size * (i / 10) });
		grid[i].setFillColor(sf::Color::Transparent);
		grid[i].setOutlineColor(sf::Color(20, 20, 20));
		//grid[i].setOutlineThickness(1);
	}

	score = 0;

	CreatePiece();
}

void Grid::CreatePiece()
{
	srand(time(0));
	Piece::PieceType type = Piece::SQUARE;
	sf::Color color = sf::Color::White;
	int rnd = rand() % 7;
	switch (rnd) {
		case 0:
			type = Piece::LONG;
			color = sf::Color(92, 190, 255); // Blue
			break;
		case 1:
			type = Piece::L;
			color = sf::Color(255, 165, 0); // Orange
			break;
		case 2:
			type = Piece::LBACK;
			color = sf::Color(220, 49, 49); // Red
			break;
		case 3:
			type = Piece::SQUARE;
			color = sf::Color(241, 244, 57); // Yellow
			break;
		case 4:
			type = Piece::Z;
			color = sf::Color(255, 64, 175); // Magenta
			break;
		case 5:
			type = Piece::ZBACK;
			color = sf::Color(245, 245, 220); // Beige
			break;
		case 6:
			type = Piece::T;
			color = sf::Color(0, 219, 95); // Green
			break;
		default:
			break;
	}
	if (!colorMode) {
		controllable = Piece(type, { 4, 0 }, sf::Color::White);
		return;
	}

	controllable = Piece(type, { 4, 0 }, color);
}

void Grid::MoveDown()
{
	for (sf::Vector2f& part : controllable.GetParts()) {
		sf::Vector2f coord = controllable.GetPosition() + part;
		if (coord.y == 19) {
			Mount();
			return;
		}
		for (Block& block : blocks)
			if (coord + sf::Vector2f { 0, 1 } == block.pos) {
				Mount();
				return;
			}
	}

	controllable.MoveDown();
}

void Grid::MoveLeft()
{
	for (sf::Vector2f& part : controllable.GetParts()) {
		sf::Vector2f coord = controllable.GetPosition() + part;
		if (coord.x == 0)
			return;

		for (Block& block : blocks)
			if (coord + sf::Vector2f { -1, 0 } == block.pos)
				return;
	}

	controllable.MoveLeft();
}

void Grid::MoveRight()
{
	for (sf::Vector2f& part : controllable.GetParts()) {
		sf::Vector2f coord = controllable.GetPosition() + part;
		if (coord.x == 9)
			return;

		for (Block& block : blocks)
			if (coord + sf::Vector2f { 1, 0 } == block.pos)
				return;
	}

	controllable.MoveRight();
}

void Grid::Rotate()
{
	Piece copy = Piece(controllable);
	copy.Rotate();
	for (sf::Vector2f& part : copy.GetParts()) {
		for (Block& block : blocks) {
			sf::Vector2f coord = copy.GetPosition() + part;
			if (coord.x > 9 || coord.x < 0 || coord.y > 19 || coord.y < 0)
				return;
			if (coord == block.pos)
				return;
		}
	}
	controllable.Rotate();
}

void Grid::InstantDown()
{
	float min = 10;
	float max = -1;
	for (sf::Vector2f& part : controllable.GetParts()) {
		max = std::max(controllable.GetPosition().x + part.x, max);
		min = std::min(controllable.GetPosition().x + part.x, min);
	}
	int minDistance = 20;
	for (int x = min; x <= max; x++) {
		int partY = 0;
		for (sf::Vector2f& part : controllable.GetParts()) {
			if (controllable.GetPosition().x + part.x == x)
				partY = std::max(partY, (int)(controllable.GetPosition().y + part.y));
		}
		partY++;
		int stepsForColumn = 0;
		for (int y = partY; y < 20; y++) {
			if (GridAt(x, y).getFillColor() != sf::Color::Transparent) {
				break;
			}
			stepsForColumn++;
		}
		minDistance = std::min(minDistance, stepsForColumn);
	}
	controllable.Move({ 0, (float)minDistance });
}

void Grid::Render(sf::RenderWindow& window)
{
	for (int i = 0; i < 200; i++) {
		window.draw(grid[i]);
	}
	window.draw(border);
}

void Grid::Update(bool& inGame)
{
	if (border.getOutlineColor() == sf::Color::Red) {
		inGame = false;
		border.setOutlineColor(sf::Color::White);
		Reset();
	}

	for (int i = 0; i < 200; i++)
		grid[i].setFillColor(sf::Color::Transparent);

	for (sf::Vector2f& part : controllable.GetParts())
		GridAt(controllable.GetPosition().x + part.x, controllable.GetPosition().y + part.y)
		.setFillColor(controllable.GetColor());

	for (Block& block : blocks)
		GridAt(block.pos.x, block.pos.y).setFillColor(block.color);
}

void Grid::SetColorMode(bool p_colorMode)
{
	colorMode = p_colorMode;
}


int Grid::GetScore()
{
	return score;
}

void Grid::Reset()
{
	score = 0;
	blocks.clear();
	CreatePiece();
}

void Grid::Mount()
{
	for (sf::Vector2f& part : controllable.GetParts()) {
		if (controllable.GetPosition().y + part.y == 0)
			border.setOutlineColor(sf::Color::Red);

		blocks.push_back({ { controllable.GetPosition().x + part.x,
						 controllable.GetPosition().y + part.y }, controllable.GetColor() });
	}

	CreatePiece();

	// filled line check
	int rowsCleared = 0;

	for (int y = 0; y < 20; y++) {
		int inrow = 0;
		for (int x = 0; x < 10; x++) {
			if (GridAt(x, y).getFillColor() == sf::Color::Transparent)
				break;
			inrow += 1;
		}
		if (inrow == 10) {
			blocks.erase(std::remove_if(blocks.begin(), blocks.end(), [&y](Block block) { return block.pos.y == y; }), blocks.end());

			for (Block& block : blocks)
				if (block.pos.y < y)
					block.pos += { 0, 1 };

			rowsCleared++;
		}
	}

	int points = 0;
	if (rowsCleared > 0) {
		points = 1 << (rowsCleared - 1);  // Points multiplier (e.g., 1, 2, 4, 8, ...).
		score += points;
	}
}

sf::RectangleShape& Grid::GridAt(int x, int y)
{
	return grid[y * 10 + x];
}
