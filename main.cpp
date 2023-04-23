#include "includes.h"

bool running = true;

void UpdateThread(Grid* grid)
{
	using namespace std::chrono_literals;

	while (running) {
		grid->MoveDown();
		std::this_thread::sleep_for(500ms);
	}
}

int main()
{
	srand(time(0));
	sf::RenderWindow window(sf::VideoMode(800, 1000), "Tetris", sf::Style::Default);

	window.setFramerateLimit(60);
	window.setVerticalSyncEnabled(true);

	sf::Font font;
	if (!font.loadFromFile("fonts/publicPixel.ttf")) {
		std::cout << "[Error] Font wasn't loaded" << std::endl;
	}

	// Score
	sf::Text score;
	score.setFont(font);
	score.setString("0");
	score.setCharacterSize(32);
	score.setFillColor(sf::Color::White);
	score.setPosition({ 100, 100 });

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
			if (e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::A) { // Left
				grid.MoveLeft();
			}
			if (e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::D) { // Right
				grid.MoveRight();
			}
			if (e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::R) { // Right
				grid.Rotate();
			}
			if (e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::S) { // Intstant Down
				grid.MoveDown();
			}
			if (e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::Space) { // Intstant Down
				grid.InstantDown();
			}
		}

		window.clear(sf::Color::Black);

		grid.Update(running);
		grid.Render(window);

		// text update
		score.setString(std::to_string(grid.GetScore()));
		window.draw(score);

		window.display();
	}

	return 0;
}
