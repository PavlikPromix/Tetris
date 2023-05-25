#pragma once
#include "includes.h"

class Grid
{
public:
	Grid(sf::RenderWindow& window);

	void MoveDown();
	void MoveLeft();
	void MoveRight();
	void Rotate();
	void InstantDown();
	void Render(sf::RenderWindow& window);
	void Update(bool& inGame);
	void SetColorMode(bool p_colorMode);

	int GetScore();
	void Reset();
private:
	sf::RectangleShape border;
	sf::RectangleShape grid[200];
	std::vector<Block> blocks;
	Piece controllable;
	int score;
	bool colorMode;

	void CreatePiece();
	void Mount();
	sf::RectangleShape& GridAt(int x, int y);
};