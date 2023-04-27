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
	int rnd = rand() % 7;
	switch (rnd) {
		case 0:
			type = Piece::LONG;
			break;
		case 1:
			type = Piece::L;
			break;
		case 2:
			type = Piece::LBACK;
			break;
		case 3:
			type = Piece::SQUARE;
			break;
		case 4:
			type = Piece::Z;
			break;
		case 5:
			type = Piece::ZBACK;
			break;
		case 6:
			type = Piece::T;
			break;
		default:
			break;
	}
	controllable = Piece(type, { 4, 0 });
}

void Grid::MoveDown()
{
	for (sf::Vector2f& part : controllable.GetParts()) {
		sf::Vector2f coord = controllable.GetPosition() + part;
		if (coord.y == 19) {
			Mount();
			return;
		}
		for (sf::Vector2f& block : blocks)
			if (coord + sf::Vector2f { 0, 1 } == block) {
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

		for (sf::Vector2f& block : blocks)
			if (coord + sf::Vector2f { -1, 0 } == block)
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

		for (sf::Vector2f& block : blocks)
			if (coord + sf::Vector2f { 1, 0 } == block)
				return;
	}

	controllable.MoveRight();
}

void Grid::Rotate()
{
	Piece copy = Piece(controllable);
	copy.Rotate();
	for (sf::Vector2f& part : copy.GetParts()) {
		for (sf::Vector2f& block : blocks) {
			sf::Vector2f coord = copy.GetPosition() + part;
			if (coord.x > 9 || coord.x < 0 || coord.y > 19 || coord.y < 0)
				return;
			if (coord == block)
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
			if (GridAt(x, y).getFillColor() == sf::Color::White) {
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
		blocks.clear();
	}

	for (int i = 0; i < 200; i++)
		grid[i].setFillColor(sf::Color::Transparent);

	for (sf::Vector2f& part : controllable.GetParts())
		GridAt(controllable.GetPosition().x + part.x, controllable.GetPosition().y + part.y).setFillColor(sf::Color::White);

	for (sf::Vector2f& block : blocks)
		GridAt(block.x, block.y).setFillColor(sf::Color::White);
}

int Grid::GetScore()
{
	return score;
}

void Grid::Mount()
{
	for (sf::Vector2f& part : controllable.GetParts()) {
		if (controllable.GetPosition().y + part.y == 0)
			border.setOutlineColor(sf::Color::Red);

		blocks.push_back({ controllable.GetPosition().x + part.x,
						 controllable.GetPosition().y + part.y });
	}

	CreatePiece();

	// filled line check
	for (int y = 0; y < 20; y++) {
		int inrow = 0;
		for (int x = 0; x < 10; x++) {
			if (GridAt(x, y).getFillColor() == sf::Color::Transparent)
				break;
			inrow += 1;
		}
		if (inrow == 10) {
			blocks.erase(std::remove_if(blocks.begin(), blocks.end(), [&y](sf::Vector2f block) { return block.y == y; }), blocks.end());

			for (sf::Vector2f& block : blocks)
				if (block.y < y)
					block += { 0, 1 };

			score++;
		}
	}
}

sf::RectangleShape& Grid::GridAt(int x, int y)
{
	return grid[y * 10 + x];
}
