#include "includes.h"

Piece::Piece()
{
	// Square
	p_coords[0] = { 0, 0 };
	p_coords[1] = { 1, 0 };
	p_coords[2] = { 0, 1 };
	p_coords[3] = { 1, 1 };

	position = { };
}

Piece::Piece(PieceType p_type, sf::Vector2f pos, sf::Color p_color)
{
	type = p_type;
	color = p_color;
	switch (p_type) {
		case Piece::LONG:
			p_coords[0] = { 0, 0 };
			p_coords[1] = { 1, 0 };
			p_coords[2] = { 2, 0 };
			p_coords[3] = { 3, 0 };
			break;
		case Piece::L:
			p_coords[0] = { 0, 1 };
			p_coords[1] = { 0, 0 };
			p_coords[2] = { 1, 1 };
			p_coords[3] = { 2, 1 };
			break;
		case Piece::LBACK:
			p_coords[0] = { 0, 1 };
			p_coords[1] = { 1, 1 };
			p_coords[2] = { 2, 1 };
			p_coords[3] = { 2, 0 };
			break;
		case Piece::SQUARE:
			p_coords[0] = { 0, 0 };
			p_coords[1] = { 1, 0 };
			p_coords[2] = { 0, 1 };
			p_coords[3] = { 1, 1 };
			break;
		case Piece::Z:
			p_coords[0] = { 0, 0 };
			p_coords[1] = { 1, 0 };
			p_coords[2] = { 1, 1 };
			p_coords[3] = { 2, 1 };
			break;
		case Piece::ZBACK:
			p_coords[0] = { 0, 1 };
			p_coords[1] = { 1, 0 };
			p_coords[2] = { 1, 1 };
			p_coords[3] = { 2, 0 };
			break;
		case Piece::T:
			p_coords[0] = { 0, 1 };
			p_coords[1] = { 1, 0 };
			p_coords[2] = { 1, 1 };
			p_coords[3] = { 2, 1 };
			break;
		default:
			break;
	}
	position = pos;
}

std::array<sf::Vector2f, 4> Piece::GetParts()
{
	return p_coords;
}

sf::Vector2f Piece::GetPosition()
{
	return position;
}

sf::Color Piece::GetColor()
{
	return color;
}

void Piece::MoveDown()
{
	position += { 0, 1 };
}

void Piece::MoveLeft()
{
	position += { -1, 0 };
}

void Piece::MoveRight()
{
	position += { 1, 0 };
}

void Piece::Rotate()
{
	if (type == SQUARE)
		return;

	if (type == LONG) {
		if (rotated) {
			p_coords[0] = { 0, 0 };
			p_coords[1] = { 1, 0 };
			p_coords[2] = { 2, 0 };
			p_coords[3] = { 3, 0 };
			rotated = false;
			return;
		}
		p_coords[0] = { 2, -1 };
		p_coords[1] = { 2, 0 };
		p_coords[2] = { 2, 1 };
		p_coords[3] = { 2, 2 };
		rotated = true;
		return;
	}

	for (sf::Vector2f& p : p_coords)
		p = { p.y, 2 - p.x };
}

void Piece::Move(const sf::Vector2f offset)
{
	position += offset;
}
