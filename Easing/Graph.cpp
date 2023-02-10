#include "Graph.h"
#include <cassert>
#include"ThickLine.h"

void Graph::drawGraph() {


    sf::Vertex axes[5];

    axes[0].position = sf::Vector2f(0, 1);
    axes[0].color = sf::Color::White;
    axes[1].position = sf::Vector2f(0, 0);
    axes[1].color = sf::Color::White;
    axes[2].position = sf::Vector2f(1, 0);
    axes[2].color = sf::Color::White;
    axes[3].position = sf::Vector2f(1, 1);
    axes[3].color = sf::Color::White;
    axes[4].position = sf::Vector2f(0, 1);
    axes[4].color = sf::Color::White;
    window.draw(axes, 5, sf::LineStrip);

sf:Color ticKColor = sf::Color::White;
    const int NUM_TICKS = 22;
    sf::Vertex ticks[NUM_TICKS * 2];
    for (int i = 0; i < NUM_TICKS * 2; i++) {
        ticks[i].color = ticKColor;
    }
    float tickLength = 0.02;
    int i = 0;
    for (int t = 0; t <= 10; t++) {
        ticks[i++].position = sf::Vector2f(t/10.0, 0);
        ticks[i++].position = sf::Vector2f(t/10.0, -tickLength);
    }
    for (int t = 0; t <= 10; t++) {
        ticks[i++].position = sf::Vector2f(0, t / 10.0);
        ticks[i++].position = sf::Vector2f(-tickLength, t / 10.0);
    }


    window.draw(ticks, NUM_TICKS * 2, sf::Lines);

    float textOffset = 0.05;

    centredText("t", sf::Vector2f(0.5, -textOffset),20);
    centredText("f(t)", sf::Vector2f(-textOffset, 0.5), 20,true);
    centredText("0.0", sf::Vector2f(0, -textOffset),10);    
    centredText("1.0", sf::Vector2f(1.0, -textOffset), 10);
    centredText("0.0", sf::Vector2f(-textOffset, 0.0), 10, true);
    centredText("1.0", sf::Vector2f(-textOffset, 1.0), 10, true);


    for (auto& c : curves) {
        PointList q;
        int i = 0;
        ThickLine::convert(c->points, q, c->thickness);
        for (auto& p : q) {
            line[i].position = sf::Vector2f(p);
            line[i].color = c->color;
            i++;
        }
        window.draw(line, i, sf::TriangleStrip);
    }    
}

void Graph::addPoint(int curve, sf::Vector2f point) {
    assert(curves[curve]->points.size() < MAX_POINTS);
    curves[curve]->points.push_back(point);

}

void Graph::reset() {
    for (auto& c : curves) c->points.clear();
}
