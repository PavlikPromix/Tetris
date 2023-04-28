#include "../includes.h"

Gui::Gui(sf::RenderWindow& window, sf::Font& p_font)
{
	background = sf::RectangleShape({ size * 10, size * 20 });
	background.setPosition({ (float)(window.getSize().x - size * 10) / 2,
						(float)(window.getSize().y - size * 20) / 2 });
	background.setFillColor(sf::Color::Black);

	font = p_font;

	menuItems.reserve(3);
	for (size_t i = 0; i < 4; i++)
		menuItems.push_back(sf::Text());

	for (sf::Text& i : menuItems) {
		i.setFillColor(sf::Color::White);
		i.setCharacterSize(32);
		i.setFont(font);
	}

	menuItems[0].setString("Play");
	menuItems[0].setPosition({ GetHorizontalCenteredPos(menuItems[0]),
						 background.getPosition().y + size * 3 });

	menuItems[1].setString("Controls");
	menuItems[1].setPosition({ GetHorizontalCenteredPos(menuItems[1]),
						 background.getPosition().y + size * 7 });

	menuItems[2].setString("Stats");
	menuItems[2].setPosition({ GetHorizontalCenteredPos(menuItems[2]),
						 background.getPosition().y + size * 11 });
	
	menuItems[3].setString("Exit");
	menuItems[3].setPosition({ GetHorizontalCenteredPos(menuItems[3]),
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
}

void Gui::SelectNext()
{
	if (inControlsMenu) return;
	if (mainSelection == menuItems.size() - 1)
		mainSelection = 0;
	else mainSelection++;
}

void Gui::SelectPrev()
{
	if (inControlsMenu) return;
	if (mainSelection == 0)
		mainSelection = menuItems.size() - 1;
	else mainSelection--;
}

int Gui::GetSelected()
{
	return mainSelection;
}

void Gui::ToggleControlsMenu()
{
	inControlsMenu = !inControlsMenu;
}

void Gui::ToggleStatsMenu()
{
	inStatsMenu = !inStatsMenu;
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
	for (sf::Text& i : menuItems)
		window.draw(i);

}

void Gui::Update()
{
	for (sf::Text& i : menuItems)
		i.setFillColor(sf::Color(150, 150, 150));
	menuItems[mainSelection].setFillColor(sf::Color::White);
}

float Gui::GetHorizontalCenteredPos(sf::Text& text)
{
	return background.getPosition().x + (size * 10 - text.getCharacterSize() * text.getString().getSize()) / 2;
}