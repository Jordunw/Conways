#pragma once
#include <string>
#include <bitset>
#include <iostream>
#include <SFML/Main.hpp>
#include <SFML/Graphics.hpp>
#include "Cell.h"

#define NUM_CELLS_X 100

class GameOfLife
{
public:
	GameOfLife(sf::RenderWindow* window) : window{ window } { init(); }
	~GameOfLife() { window = nullptr; }

private:
	sf::RenderWindow* window;
	float cellWidth;
	int cellRows;

	std::vector<std::bitset<NUM_CELLS_X>> gameboard; // vector of bitsets. 1 = alive 0 = dead
	//std::vector<std::vector<sf::RectangleShape>> cells;
	std::vector<std::vector<Cell>> cells;

public:
	void init();
	sf::Vector2i getCell(const sf::Vector2f& pos);
	void addCell(int row, int col);
	void addCell(const sf::Vector2i& pos);
	void removeCell(int row, int col);
	void removeCell(const sf::Vector2i& pos);
	void addGosperGun(const sf::Vector2i& pos);
	void calc();
	void updateDrawCell(int row, int col, bool val);
	void updateDrawCell(const sf::Vector2i& pos, bool val);
	void clearCells();
	void draw();
};

