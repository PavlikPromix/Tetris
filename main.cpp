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

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 1000), "Tetris", sf::Style::Fullscreen);

	window.setFramerateLimit(60);
	window.setVerticalSyncEnabled(true);

	sf::Font font;
	if (!font.loadFromFile("fonts/publicPixel.ttf")) {
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
		sf::Event e;
		while (window.pollEvent(e)) {
			if (e.type == sf::Event::Closed) {
				running = false;
				updThread.join();
				window.close();
			}
			if (e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::Q) {
				running = false;
				updThread.join();
				window.close();
			}
			if (e.type == sf::Event::KeyPressed && (e.key.code == sf::Keyboard::A || e.key.code == sf::Keyboard::Left)) { // Left
				if (inGame)
					grid.MoveLeft();
			}

			if (e.type == sf::Event::KeyPressed && (e.key.code == sf::Keyboard::D || e.key.code == sf::Keyboard::Right)) { // Right
				if (inGame)
					grid.MoveRight();
			}

			if (e.type == sf::Event::KeyPressed && (e.key.code == sf::Keyboard::W || e.key.code == sf::Keyboard::Up)) { // Rotate (UP)
				if (inGame)
					grid.Rotate();
				else gui.SelectPrev();
			}

			if (e.type == sf::Event::KeyPressed && (e.key.code == sf::Keyboard::S || e.key.code == sf::Keyboard::Down)) { // Down
				if (inGame)
					grid.MoveDown();
				else gui.SelectNext();
			}

			if (e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::Space) {
				if (inGame)
					grid.InstantDown();
			}

			if (e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::Enter) {
				if (!inGame) {
					if (gui.GetSelected() == 0)
						inGame = true;
					if (gui.GetSelected() == 1)
						gui.SwitchControls();
					if (gui.GetSelected() == 2) {
						running = false;
						updThread.join();
						window.close();
					}
				}

			}

		}

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
