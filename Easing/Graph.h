#pragma once
#include<vector>
#include <SFML\Graphics.hpp>

class Graph
{
	std::vector<sf::Vector2f> points;

public:

	void drawGraph(sf::RenderWindow& window);
	void addPoint(sf::Vector2f point);
	void reset();

};

