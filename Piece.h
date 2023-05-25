#pragma once
#include "includes.h"

struct Block
{
	sf::Vector2f pos;
	sf::Color color;
};

class Piece
{
public:
	enum PieceType
	{
		LONG,
		L,
		LBACK,
		SQUARE,
		Z,
		ZBACK,
		T
	};

	Piece();
	Piece(PieceType p_type, sf::Vector2f pos, sf::Color p_color);

	std::array<sf::Vector2f, 4> GetParts();
	sf::Vector2f GetPosition();
	sf::Color GetColor();

	void MoveDown();
	void MoveLeft();
	void MoveRight();
	void Rotate();
	void Move(const sf::Vector2f offset);
private:
	bool rotated = false;
	sf::Vector2f position; // Piece absolute coords
	std::array<sf::Vector2f, 4> p_coords; // Part relative coords
	PieceType type;
	sf::Color color;
};

