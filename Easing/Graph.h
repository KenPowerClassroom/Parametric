#pragma once
#include<vector>
#include"Viewport.h"

using namespace std;
class Graph
{
	static const int MAX_POINTS = 1010;
	
	typedef vector<sf::Vector2f> PointList;

	vector<PointList*> curves;

public:

	void drawGraph(sf::RenderWindow& window, Viewport& vp);
	void addPoint(int i, sf::Vector2f point);
	void reset();
	void addCurve() {
		curves.push_back(new PointList);
	}
};

