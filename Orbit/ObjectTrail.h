#pragma once
#include <SFML/Graphics.hpp>
class ObjectTrail
{
private:
	int lineWidth = 0;
	int count = 0;
	int maxVertexCount = 0;
	sf::Color color = sf::Color::White;
public:
	ObjectTrail();

	sf::VertexArray trail;

	void setObjectTrail(int width, int length);

	void addPoint(double x, double y);

	void setColor(const sf::Color& color);
};

