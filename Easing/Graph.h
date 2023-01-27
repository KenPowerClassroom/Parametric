#pragma once
#include<vector>
#include"Viewport.h"

class Graph
{
	static const int MAX_POINTS = 1010;
	std::vector<sf::Vector2f> points;

public:

	void drawGraph(sf::RenderWindow& window, Viewport& vp);
	void addPoint(sf::Vector2f point);
	void reset();
};

