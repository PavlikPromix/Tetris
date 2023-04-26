#pragma once

#include "../includes.h"

class Gui
{
public:
	enum State
	{
		General
	};
	Gui(sf::RenderWindow& window, sf::Font& p_font);

	void SelectNext();
	void SelectPrev();
	int GetSelected();

	void SwitchControls();

	void Render(sf::RenderWindow& window);
	void Update();
private:
	bool isOpen = true;
	int mainSelection = 0;
	bool inControls = false;

	sf::RectangleShape background;

	sf::Font font;
	std::vector<sf::Text> menuItems;
	sf::Text controlsText;
	sf::Text controlsBack;

	float GetHorizontalCenteredPos(sf::Text& text);
};