#pragma once
#include<vector>
#include"Viewport.h"

using namespace std;


typedef vector<sf::Vector2f> PointList;

struct Curve{
	PointList points;
	sf::Color color = sf::Color::White;
	float thickness;

};
class Graph
{
	static const int MAX_POINTS = 5000;
	sf::Vertex line[MAX_POINTS];

	vector<Curve*> curves;

public:

	void drawGraph(sf::RenderWindow& window, Viewport& vp);
	void addPoint(int i, sf::Vector2f point);
	void reset();
	void addCurve(sf::Color color = sf::Color::White, float thinckness = 0.005){
		auto curve = new Curve;
		curve->color = color;
		curve->thickness = thinckness;
		curves.push_back(curve);
	}
};

