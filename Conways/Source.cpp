#include "GameOfLife.h"

int main() {
	sf::RenderWindow window(sf::VideoMode(1280, 720), "Conway's Game of Life", sf::Style::Titlebar | sf::Style::Close);
	GameOfLife game(&window);

	while(window.isOpen()){
		sf::Event event;
		while (window.pollEvent(event)) {
			switch (event.type) {
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::KeyPressed:
				switch (event.key.code) {
				case sf::Keyboard::Num1:
					static bool pressed = false;
					pressed ? game.addCell(5, 5) : game.removeCell(5,5);
					pressed = !pressed;
				}
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