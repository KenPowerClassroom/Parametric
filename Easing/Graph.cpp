#include "Graph.h"
#include <cassert>
#include"ThickLine.h"

void Graph::drawGraph(sf::RenderWindow& window, Viewport& vp) {

    sf::Vertex line[MAX_POINTS];
    sf::Vertex axes[5];

    axes[0].position = vp.screenSpace(sf::Vector2f(0, 1));
    axes[0].color = sf::Color::White;
    axes[1].position = vp.screenSpace(sf::Vector2f(0, 0));
    axes[1].color = sf::Color::White;
    axes[2].position = vp.screenSpace(sf::Vector2f(1, 0));
    axes[2].color = sf::Color::White;
    axes[3].position = vp.screenSpace(sf::Vector2f(1, 1));
    axes[3].color = sf::Color::White;
    axes[4].position = vp.screenSpace(sf::Vector2f(0, 1));
    axes[4].color = sf::Color::White;
    window.draw(axes, 5, sf::LineStrip);



    //ThickLine::convert(p, q, 50);


    //sf::Vertex line[1000];

    for (auto& c : curves) {
        PointList q;
        int i = 0;
        ThickLine::convert(c->points, q, 0.01);
        for (auto& p : q) {
            line[i].position = vp.screenSpace(sf::Vector2f(p));
            line[i].color = c->color;
            i++;
        }
        window.draw(line, i, sf::TriangleStrip);
    }    
    //for (auto& c : curves) {
    //    int i = 0;
    //    for (auto& p : c->points) {
    //        line[i].position = vp.screenSpace(sf::Vector2f(p));
    //        line[i].color = c->color;
    //        i++;
    //    }
    //    window.draw(line, c->points.size(), sf::LineStrip);
    //}

}

void Graph::addPoint(int curve, sf::Vector2f point) {
    assert(curves[curve]->points.size() < MAX_POINTS);
    curves[curve]->points.push_back(point);

}

void Graph::reset() {
    for (auto& c : curves) c->points.clear();
}
