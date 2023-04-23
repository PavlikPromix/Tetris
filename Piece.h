#pragma once
#include "includes.h"

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
	Piece(PieceType p_type, sf::Vector2f pos);

	std::array<sf::Vector2f, 4> GetParts();
	sf::Vector2f GetPosition();

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
};

