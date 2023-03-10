/*==============================================================================
Do not edit any code in this file!!!


██████   ██████      ███    ██  ██████  ████████     ███████ ██████  ██ ████████
██   ██ ██    ██     ████   ██ ██    ██    ██        ██      ██   ██ ██    ██
██   ██ ██    ██     ██ ██  ██ ██    ██    ██        █████   ██   ██ ██    ██
██   ██ ██    ██     ██  ██ ██ ██    ██    ██        ██      ██   ██ ██    ██
██████   ██████      ██   ████  ██████     ██        ███████ ██████  ██    ██


████████ ██   ██ ██ ███████     ███████ ██ ██      ███████ ██
   ██    ██   ██ ██ ██          ██      ██ ██      ██      ██
   ██    ███████ ██ ███████     █████   ██ ██      █████   ██
   ██    ██   ██ ██      ██     ██      ██ ██      ██
   ██    ██   ██ ██ ███████     ██      ██ ███████ ███████ ██

==============================================================================*/
#include"globals.h"
#include "Graph.h"
#include <cassert>
#include"ThickLine.h"

void Graph::drawGraph() {

    float unit = Unit;
    
    sf::Vector2f origin(0, 0);
    sf::Vector2f width(1, 1);
    if (parametric) {
        width = sf::Vector2f(5, 5);
        origin = sf::Vector2f(unit/2, unit/2);
    }

    sf::Vertex boundary[5];

    boundary[0].position = sf::Vector2f(0, unit);
    boundary[0].color = sf::Color::White;
    boundary[1].position = sf::Vector2f(0, 0);
    boundary[1].color = sf::Color::White;
    boundary[2].position = sf::Vector2f(unit, 0);
    boundary[2].color = sf::Color::White;
    boundary[3].position = sf::Vector2f(unit, unit);
    boundary[3].color = sf::Color::White;
    boundary[4].position = sf::Vector2f(0, unit);
    boundary[4].color = sf::Color::White;
    window.draw(boundary, 5, sf::LineStrip);

    sf::Vertex axes[4];
    //x-axis
    axes[0].position = sf::Vector2f(0   , origin.y);
    axes[0].color = sf::Color::White;
    axes[1].position = sf::Vector2f(unit, origin.y);
    axes[1].color = sf::Color::White;
    
    //y-axis
    axes[2].position = sf::Vector2f(origin.x, 0);
    axes[2].color = sf::Color::White;
    axes[3].position = sf::Vector2f(origin.x, unit);
    axes[3].color = sf::Color::White;

    window.draw(axes, 4, sf::Lines);

    sf:Color ticKColor = sf::Color::White;
    const int NUM_TICKS = 22;
    sf::Vertex ticks[NUM_TICKS * 2];
    for (int i = 0; i < NUM_TICKS * 2; i++) {
        ticks[i].color = ticKColor;
    }
    float tickLength = 0.02 * unit;
    int i = 0;
    for (int t = 0; t <= unit; t+=(unit/10)) {
        ticks[i++].position = sf::Vector2f((float)t, origin.y);
        ticks[i++].position = sf::Vector2f((float)t, origin.y -tickLength);
    }
    for (int t = 0; t <= unit; t += (unit / 10)) {
        ticks[i++].position = sf::Vector2f(origin.x, (float)t );
        ticks[i++].position = sf::Vector2f(origin.x -tickLength, (float)t );
    }


    window.draw(ticks, NUM_TICKS * 2, sf::Lines);

    float textOffset = unit/20.0f;
    int labelTextSize = 40;
    int axisTextSize = 25;

    centredText("t", sf::Vector2f(unit/2, -textOffset), labelTextSize);
    centredText("f(t)", sf::Vector2f(-textOffset, unit / 2), labelTextSize,true);
    centredText("0.0", sf::Vector2f(0, -textOffset), axisTextSize);
    centredText("1.0", sf::Vector2f(unit, origin.y -textOffset), axisTextSize);
    centredText("0.0", sf::Vector2f(-textOffset, 0), axisTextSize, true);
    centredText("1.0", sf::Vector2f(origin.y -textOffset, unit), axisTextSize, true);


    for (auto& c : curves) {
        PointList q;
        int i = 0;
        ThickLine::convert(c->points, q, c->thickness);
        for (auto& p : q) {
            assert(i < MAX_POINTS);
            line[i].position = sf::Vector2f(p.x*unit/width.x+origin.x, p.y*unit/width.y + origin.y);
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
