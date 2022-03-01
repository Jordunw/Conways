#include "GameOfLife.h"

void GameOfLife::init()
{
	cellWidth = (float)window->getSize().x / (float)NUM_CELLS_X;
	cellRows = window->getSize().y / cellWidth;
	gameboard = std::vector<std::bitset<NUM_CELLS_X>>(cellRows);
	//cells = std::vector<std::vector<sf::RectangleShape>>(cellRows);
	cells = std::vector<std::vector<Cell>>(cellRows);
	for (auto& vec : cells) {
		vec.resize(NUM_CELLS_X);
	}
	for (int i = 0; i < cells.size(); i++) {
		for (int j = 0; j < NUM_CELLS_X; j++) {
			cells.at(i).at(j) = Cell({ (float)j * cellWidth, (float)i * cellWidth }, cellWidth);
			//cells.at(i).at(j).setFillColor(sf::Color::Black);
			//cells.at(i).at(j).setSize({ cellWidth, cellWidth });
			//cells.at(i).at(j).setPosition({(float)j * cellWidth, (float)i * cellWidth});
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
	std::vector<sf::Vector2i> flippedCells; // do checks first & add locations to this vec, then make the changes after
	// dont check edge cases because they are annoying
	for (int i = 1; i < gameboard.size() - 1; i++) {
		for (int j = 1; j < NUM_CELLS_X - 1; j++) {
			bool cellState = gameboard[i][j];
			if (!cellState) { // if dead
				uint8_t liveCells = 0;
				liveCells += 
					gameboard[i - 1][j - 1] + 
					gameboard[i + 1][j - 1] + 
					gameboard[i + 1][j] + 
					gameboard[i + 1][j + 1] + 
					gameboard[i][j + 1] + 
					gameboard[i - 1][j + 1] +
					gameboard[i][j-1] +
					gameboard[i-1][j];
					if (liveCells == 3)
						flippedCells.emplace_back(i, j);
					continue;
			}
			else {
				uint8_t liveCells = 0;
				liveCells +=
					gameboard[i - 1][j - 1] +
					gameboard[i + 1][j - 1] +
					gameboard[i + 1][j] +
					gameboard[i + 1][j + 1] +
					gameboard[i][j + 1] +
					gameboard[i - 1][j + 1] +
					gameboard[i][j - 1] +
					gameboard[i - 1][j];
				if (liveCells < 2 || liveCells > 3) {
					flippedCells.emplace_back(i, j);
					continue;
				}
			}
		}
	}
	for (auto& pos : flippedCells) {
		gameboard[pos.x][pos.y].flip();
		updateDrawCell(pos, gameboard[pos.x][pos.y]);
	}
}

// call getCell() first before using this function
void GameOfLife::addCell(int row, int col)
{
	gameboard.at(row).set(col);
	updateDrawCell(row, col, true);
}

// call getCell() first before using this function
void GameOfLife::addCell(const sf::Vector2i& pos) {
	gameboard.at(pos.x).set(pos.y);
	updateDrawCell(pos, true);
}

// call getCell() first before using this function
void GameOfLife::removeCell(int row, int col) {
	gameboard.at(row).set(col, false);
	updateDrawCell(row, col, false);
}

// call getCell() first before using this function
void GameOfLife::removeCell(const sf::Vector2i& pos) {
	gameboard.at(pos.x).set(pos.y, false);
	updateDrawCell(pos, false);
}

void GameOfLife::addGosperGun(const sf::Vector2i& pos)
{
	for (int i = 0; i < 11; i++) {
		for (int j = 0; j < 38; j++) {
			removeCell(pos.x + i, pos.y + j);
		}
	}
	addCell(pos.x + 5, pos.y + 1);
	addCell(pos.x + 6, pos.y + 1);
	addCell(pos.x + 5, pos.y + 2);
	addCell(pos.x + 6, pos.y + 2);
	addCell(pos.x + 5, pos.y + 11);
	addCell(pos.x + 6, pos.y + 11);
	addCell(pos.x + 7, pos.y + 11);
	addCell(pos.x + 4, pos.y + 12);
	addCell(pos.x + 8, pos.y + 12);
	addCell(pos.x + 3, pos.y + 13);
	addCell(pos.x + 9, pos.y + 13);
	addCell(pos.x + 3, pos.y + 14);
	addCell(pos.x + 9, pos.y + 14);
	addCell(pos.x + 6, pos.y + 15);
	addCell(pos.x + 4, pos.y + 16);
	addCell(pos.x + 8, pos.y + 16);
	addCell(pos.x + 5, pos.y + 17);
	addCell(pos.x + 6, pos.y + 17);
	addCell(pos.x + 7, pos.y + 17);
	addCell(pos.x + 6, pos.y + 18);
	addCell(pos.x + 3, pos.y + 21);
	addCell(pos.x + 4, pos.y + 21);
	addCell(pos.x + 5, pos.y + 21);
	addCell(pos.x + 3, pos.y + 22);
	addCell(pos.x + 4, pos.y + 22);
	addCell(pos.x + 5, pos.y + 22);
	addCell(pos.x + 2, pos.y + 23);
	addCell(pos.x + 6, pos.y + 23);
	addCell(pos.x + 1, pos.y + 25);
	addCell(pos.x + 2, pos.y + 25);
	addCell(pos.x + 6, pos.y + 25);
	addCell(pos.x + 7, pos.y + 25);
	addCell(pos.x + 3, pos.y + 35);
	addCell(pos.x + 4, pos.y + 35);
	addCell(pos.x + 3, pos.y + 36);
	addCell(pos.x + 4, pos.y + 36);
}

// call getCell() first before using this function
void GameOfLife::updateDrawCell(int row, int col, bool val) {
	if (row < 0 || row > cellRows || col < 0 || col > NUM_CELLS_X) return;
	cells[row][col].setFillColor(val ? sf::Color::White : sf::Color::Black);
}

// call getCell() first before using this function
void GameOfLife::updateDrawCell(const sf::Vector2i& pos, bool val) {
	if (pos.x < 0 || pos.x > cellRows || pos.y < 0 || pos.y > NUM_CELLS_X) return;
	cells[pos.x][pos.y].setFillColor(val ? sf::Color::White : sf::Color::Black);
}

void GameOfLife::clearCells()
{
	for (auto& bitset : gameboard) {
		bitset.reset();
	}
	for (auto& vec : cells) {
		for (auto& cell : vec) {
			cell.setFillColor(sf::Color::Black);
		}
	}
}

void GameOfLife::draw()
{
	for (const auto& row : cells) {
		for (const auto& col : row) {
			window->draw(col);
		}
	}
}
