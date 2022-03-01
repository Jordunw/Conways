#include "GameOfLife.h"

int main() {
	sf::RenderWindow window(sf::VideoMode(1280, 720), "Conway's Game of Life", sf::Style::Titlebar | sf::Style::Close);
	GameOfLife game(&window);

	int mouseX, mouseY;

	while(window.isOpen()){
		sf::Event event;
		while (window.pollEvent(event)) {
			switch (event.type) {
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::KeyPressed:
				switch (event.key.code) {
				case sf::Keyboard::Enter:
					game.calc();
					break;
				case sf::Keyboard::Delete:
					game.clearCells();
					break;
				case sf::Keyboard::Num1:
					game.addGosperGun(game.getCell({ (float)mouseX, (float)mouseY }));
					break;
				}
			case sf::Event::MouseMoved:
				mouseX = event.mouseMove.x;
				mouseY = event.mouseMove.y;
				break;
			case sf::Event::MouseButtonPressed:
				switch (event.mouseButton.button) {
				case sf::Mouse::Left:
					game.addCell(game.getCell({ (float)event.mouseButton.x, (float)event.mouseButton.y }));
					break;
				case sf::Mouse::Right:
					game.removeCell(game.getCell({ (float)event.mouseButton.x, (float)event.mouseButton.y }));
					break;
				default:
					break;
				}
			default:
				break;
			}
		}
		window.clear(sf::Color::Black);
		game.draw();
		window.display();
	}

	return 0;
}