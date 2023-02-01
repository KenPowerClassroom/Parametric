#pragma once
#include<vector>
#include"Viewport.h"

using namespace std;


typedef vector<sf::Vector2f> PointList;

struct Curve{
	PointList points;
	sf::Color color = sf::Color::White;

};
class Graph
{
	static const int MAX_POINTS = 1010;
	

	vector<Curve*> curves;

public:

	void drawGraph(sf::RenderWindow& window, Viewport& vp);
	void addPoint(int i, sf::Vector2f point);
	void reset();
	void addCurve() {
		curves.push_back(new Curve);
	}
};

