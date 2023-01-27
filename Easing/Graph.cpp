#include "Graph.h"

void Graph::drawGraph( sf::RenderWindow& window, Viewport& vp) {

    sf::Vertex line[1001];
    line[0].position = vp.screenSpace(sf::Vector2f(0, 1));
    line[0].color = sf::Color::White;
    line[1].position = vp.screenSpace(sf::Vector2f(0, 0));
    line[1].color = sf::Color::White;
    line[2].position = vp.screenSpace(sf::Vector2f(1, 0));
    line[2].color = sf::Color::White;
    window.draw(line, 3, sf::LineStrip);

    int i = 0;
    for (auto p: points) {
        line[i].position = vp.screenSpace(sf::Vector2f(p));
        line[i].color = sf::Color::White;
        i++;
    }
    window.draw(line, points.size(), sf::LineStrip);

}

void Graph::addPoint(sf::Vector2f point) {
    points.push_back(point);

}

void Graph::reset() {
    points.clear();
}
