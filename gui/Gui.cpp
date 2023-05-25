#include "../includes.h"

Gui::Gui(sf::RenderWindow& window, sf::Font& p_font)
{
	background = sf::RectangleShape({ size * 10, size * 20 });
	background.setPosition({ (float)(window.getSize().x - size * 10) / 2,
						(float)(window.getSize().y - size * 20) / 2 });
	background.setFillColor(sf::Color::Black);

	font = p_font;

	// Main menu
	mainMenuItems.reserve(5);
	for (int i = 0; i < 5; i++)
		mainMenuItems.push_back(sf::Text());

	for (sf::Text& i : mainMenuItems) {
		i.setFillColor(sf::Color::White);
		i.setCharacterSize(32);
		i.setFont(font);
	}

	mainMenuItems[0].setString("Play");
	mainMenuItems[0].setPosition({ GetHorizontalCenteredPos(mainMenuItems[0]),
						 background.getPosition().y + size * 3 });

	mainMenuItems[1].setString("Controls");
	mainMenuItems[1].setPosition({ GetHorizontalCenteredPos(mainMenuItems[1]),
						 background.getPosition().y + size * 6 });
	mainMenuItems[2].setString("Settings");
	mainMenuItems[2].setPosition({ GetHorizontalCenteredPos(mainMenuItems[2]),
						 background.getPosition().y + size * 9 });

	mainMenuItems[3].setString("Stats");
	mainMenuItems[3].setPosition({ GetHorizontalCenteredPos(mainMenuItems[3]),
						 background.getPosition().y + size * 12 });
	
	mainMenuItems[4].setString("Exit");
	mainMenuItems[4].setPosition({ GetHorizontalCenteredPos(mainMenuItems[4]),
						 background.getPosition().y + size * 15 });


	// Controls menu
	controlsText.setFillColor(sf::Color(150, 150, 150));
	controlsText.setCharacterSize(20);
	controlsText.setFont(font);
	controlsText.setString("# Controls\n\n\n* Down \nS / Down Arrow\n\n* Left \nA / Left Arrow\n\n* Right \nD / Right Arrow\n\n* Rotate \nW / Up Arrow\n\n* Instant Down \nSpace\n\n* Quit\nQ");
	controlsText.setPosition({ background.getPosition().x + size * 1,
						 background.getPosition().y + size * 3 });

	controlsBack.setFillColor(sf::Color::White);
	controlsBack.setCharacterSize(32);
	controlsBack.setFont(font);
	controlsBack.setString("Back");
	controlsBack.setPosition({ GetHorizontalCenteredPos(controlsBack),
						 background.getPosition().y + size * 15 });

	// Stats menu
	statsText.setFillColor(sf::Color(150, 150, 150));
	statsText.setCharacterSize(20);
	statsText.setFont(font);
	statsText.setString("# Stats\n\n\nMax score: \n\nTotal score: \n\n");
	statsText.setPosition({ background.getPosition().x + size * 1,
						 background.getPosition().y + size * 3 });

	statsBack.setFillColor(sf::Color::White);
	statsBack.setCharacterSize(32);
	statsBack.setFont(font);
	statsBack.setString("Back");
	statsBack.setPosition({ GetHorizontalCenteredPos(statsBack),
						 background.getPosition().y + size * 15 });
	
	// Settings menu
	settingsMenuItems.reserve(2);
	for (int i = 0; i < 2; i++)
		settingsMenuItems.push_back(sf::Text());

	for (sf::Text& i : settingsMenuItems) {
		i.setFillColor(sf::Color::White);
		i.setCharacterSize(20);
		i.setFont(font);
	}

	settingsMenuItems[0].setString("Enable ColorMod");
	settingsMenuItems[0].setPosition({ GetHorizontalCenteredPos(settingsMenuItems[0]),
						 background.getPosition().y + size * 6 });
	settingsMenuItems[1].setString("Back");
	settingsMenuItems[1].setCharacterSize(32);
	settingsMenuItems[1].setPosition({ GetHorizontalCenteredPos(settingsMenuItems[1]),
						 background.getPosition().y + size * 14 });

}

void Gui::SelectNext()
{
	if (inControlsMenu) return;
	if (inStatsMenu) return;
	if (inSettingsMenu) {
		if (subSelection == settingsMenuItems.size() - 1)
			subSelection = 0;
		else subSelection++;
		return;
	}
	if (mainSelection == mainMenuItems.size() - 1)
		mainSelection = 0;
	else mainSelection++;
}

void Gui::SelectPrev()
{
	if (inControlsMenu) return;
	if (inStatsMenu) return;
	if (inSettingsMenu) {
		if (subSelection == 0)
			subSelection = settingsMenuItems.size() - 1;
		else subSelection--;
		return;
	}
	if (mainSelection == 0)
		mainSelection = mainMenuItems.size() - 1;
	else mainSelection--;
}

int Gui::GetSelected()
{
	return mainSelection;
}

int Gui::GetSubSelected()
{
	return subSelection;
}

bool Gui::GetColorMode()
{
	return colorMode;
}

bool Gui::IsInSettings()
{
	return inSettingsMenu;
}

void Gui::ToggleControlsMenu()
{
	inControlsMenu = !inControlsMenu;
}

void Gui::ToggleStatsMenu()
{
	inStatsMenu = !inStatsMenu;
}

void Gui::ToggleSettingsMenu()
{
	inSettingsMenu = !inSettingsMenu;
	if (inSettingsMenu)
		subSelection = 0;
}

void Gui::ToggleColorMode()
{
	colorMode = !colorMode;
}


void Gui::Render(sf::RenderWindow& window)
{
	window.draw(background);
	if (inControlsMenu) {
		window.draw(controlsText);
		window.draw(controlsBack);
		return;
	}
	if (inStatsMenu) {
		window.draw(statsText);
		window.draw(statsBack);
		return;
	}
	if (inSettingsMenu) {
		for (sf::Text& i : settingsMenuItems)
			window.draw(i);
		return;
	}
	for (sf::Text& i : mainMenuItems)
		window.draw(i);

}

void Gui::Update()
{
	for (sf::Text& i : mainMenuItems)
		i.setFillColor(sf::Color(150, 150, 150));
	mainMenuItems[mainSelection].setFillColor(sf::Color::White);

	// Settings
	for (sf::Text& i : settingsMenuItems)
		i.setFillColor(sf::Color(150, 150, 150));
	settingsMenuItems[subSelection].setFillColor(sf::Color::White);
	if (colorMode) 
		settingsMenuItems[0].setString("Disable ColorMod");
	else settingsMenuItems[0].setString("Enable ColorMod");
	settingsMenuItems[0].setPosition({ GetHorizontalCenteredPos(settingsMenuItems[0]),
						 background.getPosition().y + size * 6 });
}

float Gui::GetHorizontalCenteredPos(sf::Text& text)
{
	return background.getPosition().x + (size * 10 - text.getCharacterSize() * text.getString().getSize()) / 2;
}