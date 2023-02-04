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
	sf::Font font;

	sf::RenderWindow& window;
	Viewport& vp;
public:
	Graph(sf::RenderWindow& window, Viewport& vp):window(window), vp(vp) {
		font.loadFromFile("cmr12.ttf");
	};
	void drawGraph();
	void addPoint(int i, sf::Vector2f point);
	void reset();
	void addCurve(sf::Color color = sf::Color::White, float thinckness = 0.005){
		auto curve = new Curve;
		curve->color = color;
		curve->thickness = thinckness;
		curves.push_back(curve);
	}
	void centredText(string s, sf::Vector2f pos, int size=30) {
		auto text = sf::Text{s, font };
		text.setCharacterSize(size);
		auto center = sf::Vector2i(text.getGlobalBounds().width / 2.f, text.getGlobalBounds().height / 2.f);
		auto localBounds = center + sf::Vector2i(text.getLocalBounds().left, text.getLocalBounds().top) ;

		text.setOrigin(localBounds.x, localBounds.x);
		text.setPosition(pos);
		window.draw(text);
	}
};

