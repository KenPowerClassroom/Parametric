#pragma once
#include <SFML\Graphics.hpp>

class Viewport
{
	int width;
	int height;
	int xOrigin;
	int yOrigin;
public:
	Viewport(int w, int h, int x, int y) :width(w), height(h), xOrigin(x), yOrigin(y) {};
	sf::Vector2f screenSpace(sf::Vector2f point);
};

