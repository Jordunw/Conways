#include "Cell.h"

Cell::Cell(const sf::Vector2f& pos, float width, const sf::Color& fillColor)
{
	vertices[0] = sf::Vertex(pos, fillColor);
	vertices[1] = sf::Vertex({ pos.x, pos.y + width }, fillColor);
	vertices[2] = sf::Vertex({ pos.x + width, pos.y + width }, fillColor);
	vertices[3] = sf::Vertex({ pos.x + width, pos.y }, fillColor);
}

void Cell::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw((sf::Vertex*)vertices, 4, sf::Quads);
}

void Cell::setWidth(float width)
{
	float posx = vertices[0].position.x + width;
	float posy = vertices[0].position.y + width;
	vertices[1].position.y = posy;
	vertices[2].position.x = posx; 
	vertices[2].position.y = posy;
	vertices[3].position.x = posx;
}

void Cell::setFillColor(const sf::Color& color)
{
	for (int i = 0; i < 4; i++) {
		vertices[i].color = color;
	}
}
