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

	void ToggleControlsMenu();
	void ToggleStatsMenu();

	void Render(sf::RenderWindow& window);
	void Update();
private:
	int mainSelection = 0;
	bool inControlsMenu = false;
	bool inStatsMenu = false;

	sf::RectangleShape background;

	sf::Font font;
	std::vector<sf::Text> menuItems;
	sf::Text controlsText;
	sf::Text controlsBack;
	sf::Text statsText;
	sf::Text statsBack;

	float GetHorizontalCenteredPos(sf::Text& text);
};