#pragma once
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

// Much more lightweight version of sf::RectangleShape
class Cell : public sf::Drawable
{
public:
	Cell(){}
	Cell(const sf::Vector2f& pos, float width, const sf::Color& fillColor = sf::Color::Black);
private:
	sf::Vertex vertices[4];

public:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void setWidth(float width);
	void setFillColor(const sf::Color& color);
};

