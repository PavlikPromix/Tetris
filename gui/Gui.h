#pragma once

#include "../includes.h"

class Gui
{
public:
	Gui(sf::RenderWindow& window, sf::Font& p_font);

	void SelectNext();
	void SelectPrev();
	int GetSelected();
	int GetSubSelected();
	bool GetColorMode();
	bool IsInSettings();

	void ToggleControlsMenu();
	void ToggleStatsMenu();
	void ToggleSettingsMenu();
	void ToggleColorMode();

	void Render(sf::RenderWindow& window);
	void Update();
private:
	int mainSelection = 0;
	int subSelection = 0;
	bool inControlsMenu = false;
	bool inStatsMenu = false;
	bool inSettingsMenu = false;
	bool colorMode = false;

	sf::RectangleShape background;

	sf::Font font;
	std::vector<sf::Text> mainMenuItems;
	sf::Text controlsText;
	sf::Text controlsBack;
	sf::Text statsText;
	sf::Text statsBack;
	std::vector<sf::Text> settingsMenuItems;

	float GetHorizontalCenteredPos(sf::Text& text);
};