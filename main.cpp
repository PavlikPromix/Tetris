#define _WIN32_WINNT 0x0500
#include "includes.h"

bool running = true;
bool inGame = false;

void UpdateThread(Grid* grid)
{
	using namespace std::chrono_literals;

	while (running) {
		if (inGame) {
			grid->MoveDown();
			std::this_thread::sleep_for(500ms);
		} else
			std::this_thread::sleep_for(0ms); // Ugly hack to avoid thread hanging due to clang compiler optimization

	}
}

void HandleInput(sf::RenderWindow& window, Grid& grid, Gui& gui, bool& inGame, bool& running, std::thread& updThread) {
	sf::Event event;
	while (window.pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			running = false;
			window.close();
		}

		if (event.type == sf::Event::KeyPressed) {
			switch (event.key.code) {
			case sf::Keyboard::Q:
				if (inGame) {
					inGame = false;
					grid.Reset();
				}
				else {
					running = false;
					window.close();
				}
				break;
			case sf::Keyboard::A:
			case sf::Keyboard::Left:
				if (inGame) grid.MoveLeft();
				break;
			case sf::Keyboard::D:
			case sf::Keyboard::Right:
				if (inGame) grid.MoveRight();
				break;
			case sf::Keyboard::W:
			case sf::Keyboard::Up:
				if (inGame) grid.Rotate();
				else gui.SelectPrev();
				break;
			case sf::Keyboard::S:
			case sf::Keyboard::Down:
				if (inGame) grid.MoveDown();
				else gui.SelectNext();
				break;
			case sf::Keyboard::Space:
				if (inGame) grid.InstantDown();
				break;
			case sf::Keyboard::Enter:
				if (!inGame) {
					if (gui.GetSelected() == 0)
						inGame = true;
					if (gui.GetSelected() == 1)
						gui.ToggleControlsMenu();
					if (gui.GetSelected() == 2) {
						if ((gui.IsInSettings() && gui.GetSubSelected() == 1) || !gui.IsInSettings())
							gui.ToggleSettingsMenu();
						else if (gui.IsInSettings() && gui.GetSubSelected() == 0) {
							gui.ToggleColorMode();
							grid.SetColorMode(gui.GetColorMode());
							grid.Reset();
						}
					}
					if (gui.GetSelected() == 3)
						gui.ToggleStatsMenu();
					if (gui.GetSelected() == 4) {
						running = false;
						updThread.join();
						window.close();
					}
				}
				break;
			}
		}
	}
}


int main()
{
	srand(time(0));
	sf::RenderWindow window(sf::VideoMode(800, 1000), "Tetris", sf::Style::Fullscreen);

	window.setFramerateLimit(60);
	window.setVerticalSyncEnabled(true);

	sf::Font font;
	if (!font.loadFromFile("../../../fonts/publicPixel.ttf")) {
		std::cout << "\e[0;31m[Error]\e[0m Font wasn't loaded" << std::endl;
	}

	// Score
	sf::Text score;
	score.setFont(font);
	score.setString("0");
	score.setCharacterSize(32);
	score.setFillColor(sf::Color::White);
	score.setPosition({ (float)(window.getSize().x - size * 10) / 2 + size * 10 + 10,
						(float)(window.getSize().y - size * 20) / 2 });

	Gui gui(window, font);

	Grid grid(window);

	std::thread updThread(UpdateThread, &grid);

	while (window.isOpen()) {
		HandleInput(window, grid, gui, inGame, running, updThread);

		window.clear(sf::Color::Black);

		grid.Update(inGame);
		grid.Render(window);

		if (!inGame) {
			gui.Update();
			gui.Render(window);
		}

		// text update
		score.setString(std::to_string(grid.GetScore()));
		if (inGame)
			window.draw(score);

		window.display();
	}

	return 0;
}
