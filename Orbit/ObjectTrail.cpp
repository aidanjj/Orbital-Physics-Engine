#include <math.h>
#include "ObjectTrail.h"
ObjectTrail::ObjectTrail() {
	trail.setPrimitiveType(sf::TriangleStrip);
}

void ObjectTrail::setColor(const sf::Color& color)
{
	this->color = color;
}

void ObjectTrail::setTrailSize(int width, int length) {
	if (width >= 0 && length >= 0) {
		this->lineWidth = width;
		this->maxVertexCount = length;
	}
}

void ObjectTrail::addPoint(double x, double y) {
	int vertexCount = trail.getVertexCount();
	if (vertexCount > 0) {
		sf::Vertex prevVertexLeft = trail.operator[](vertexCount - 2);
		sf::Vertex prevVertexRight = trail.operator[](vertexCount - 1);
		int prevX = (prevVertexLeft.position.x + prevVertexRight.position.x) / 2;
		int prevY = (prevVertexLeft.position.y + prevVertexRight.position.y) / 2;
		double directionX = (x - prevX) / sqrt((x - prevX) * (x - prevX) + (y - prevY) * (y - prevY));
		double directionY = (y - prevY) / sqrt((x - prevX) * (x - prevX) + (y - prevY) * (y - prevY));

		double perpDirX = directionY;
		double perpDirY = -directionX;

		double rX = lineWidth * perpDirX + x;
		double lX = lineWidth * -perpDirX + x;
		double rY = lineWidth * perpDirY + y;
		double lY = lineWidth * -perpDirY + y;
		if (vertexCount > maxVertexCount) {
			for (int i = 0; i < vertexCount - 2; i += 2) {
				trail.operator[](i).position.x = trail.operator[](i + 2).position.x;
				trail.operator[](i + 1).position.x = trail.operator[](i + 3).position.x;
				trail.operator[](i).position.y = trail.operator[](i + 2).position.y;
				trail.operator[](i + 1).position.y = trail.operator[](i + 3).position.y;
			}
			trail.operator[](vertexCount - 2).position.x = lX;
			trail.operator[](vertexCount - 1).position.x = rX;
			trail.operator[](vertexCount - 2).position.y = lY;
			trail.operator[](vertexCount - 1).position.y = rY;
		}
		else {
			trail.append(sf::Vertex(sf::Vector2f(lX, lY), color));
			trail.append(sf::Vertex(sf::Vector2f(rX, rY), color));
		}
	}
	else {
		trail.append(sf::Vertex(sf::Vector2f(x, y), color));
		trail.append(sf::Vertex(sf::Vector2f(x, y), color));
	}
}
