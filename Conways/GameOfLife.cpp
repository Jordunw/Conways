#include "GameOfLife.h"

void GameOfLife::init()
{
	cellWidth = (float)window->getSize().x / (float)NUM_CELLS_X;
	cellRows = window->getSize().y / cellWidth;
	gameboard = std::vector<std::bitset<NUM_CELLS_X>>(cellRows);
	cells = std::vector<std::vector<sf::RectangleShape>>(cellRows);
	for (auto& vec : cells) {
		vec.resize(NUM_CELLS_X);
	}
	for (int i = 0; i < cells.size(); i++) {
		for (int j = 0; j < NUM_CELLS_X; j++) {
			cells.at(i).at(j).setFillColor(sf::Color::Black);
			cells.at(i).at(j).setSize({ cellWidth, cellWidth });
			cells.at(i).at(j).setPosition({(float)j * cellWidth, (float)i * cellWidth});
		}
	}
}

sf::Vector2i GameOfLife::getCell(const sf::Vector2f& pos) {
	int col = std::floor(pos.x / cellWidth);
	int row = std::floor(pos.y / cellWidth);
	if (row > cellRows) return sf::Vector2i(-1,-1);
	if (col > NUM_CELLS_X) return sf::Vector2i(-1, -1);
	return sf::Vector2i(row, col);
}

void GameOfLife::calc() {
	for (int i = 0; i < gameboard.size(); i++) {
		for (int j = 0; j < NUM_CELLS_X; j++) {
			 
		}
	}
}

void GameOfLife::addCell(int row, int col)
{
	gameboard.at(row).set(col);
	updateDrawCell(row, col, true);
}

void GameOfLife::addCell(const sf::Vector2i& pos) {
	gameboard.at(pos.x).set(pos.y);
	updateDrawCell(pos, true);
}

void GameOfLife::removeCell(int row, int col) {
	gameboard.at(row).set(col, false);
	updateDrawCell(row, col, false);
}

void GameOfLife::removeCell(const sf::Vector2i& pos) {
	gameboard.at(pos.x).set(pos.y, false);
	updateDrawCell(pos, false);
}

void GameOfLife::updateDrawCell(int row, int col, bool val) {
	cells[row][col].setFillColor(val ? sf::Color::White : sf::Color::Black);
}

void GameOfLife::updateDrawCell(const sf::Vector2i& pos, bool val) {
	cells[pos.x][pos.y].setFillColor(val ? sf::Color::White : sf::Color::Black);
}

void GameOfLife::draw()
{
	for (const auto& row : cells) {
		for (const auto& col : row) {
			window->draw(col);
		}
	}
}
