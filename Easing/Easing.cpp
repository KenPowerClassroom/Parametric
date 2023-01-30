#define SFML_STATIC
#ifdef _DEBUG
#pragma comment(lib,"sfml-graphics-s-d.lib")
#pragma comment(lib,"sfml-audio-s-d.lib")
#pragma comment(lib,"sfml-system-s-d.lib")
#pragma comment(lib,"sfml-window-s-d.lib")
#pragma comment(lib,"sfml-network-s-d.lib")
#else
#pragma comment(lib,"sfml-graphics-s.lib")
#pragma comment(lib,"sfml-audio-s.lib")
#pragma comment(lib,"sfml-system-s.lib")
#pragma comment(lib,"sfml-window-s.lib")
#pragma comment(lib,"sfml-network-s.lib")
#endif
#pragma comment(lib,"opengl32.lib")
#pragma comment(lib,"glu32.lib")
#pragma comment(lib,"winmm.lib")
#pragma comment(lib,"freetype.lib")


#include <SFML\Graphics.hpp>
#include <iostream>
#include <cassert>

#include"Graph.h"
#include"Viewport.h"

int width = 800;
int height = 800;

void drawBall(sf::Vector2f pos, sf::RenderWindow& window, Viewport vp) {

    int radius = 25;
    sf::CircleShape circle(radius);
    circle.setFillColor(sf::Color(100, 250, 50));

    circle.setPointCount(100);

    circle.setPosition(vp.screenSpace(pos)-sf::Vector2f(radius,0));

    window.draw(circle);
}

void drawChangeColorBall(float t, sf::RenderWindow& window, Viewport vp) {

    int radius = 50;
    sf::CircleShape circle(radius);
    int trans = 0 + t * (255 - 0);
    
    circle.setFillColor(sf::Color(200, 150, 50, trans));

    circle.setPointCount(100);

    circle.setPosition(vp.screenSpace(sf::Vector2f(0.1,0.4)));

    window.draw(circle);
}

void drawChangeSizeBall(float t, sf::RenderWindow& window, Viewport vp) {

    int endRadius = 50;
    int radius = 0 + t * (endRadius - 0);
    sf::CircleShape circle(radius);

    circle.setOrigin(sf::Vector2f(radius, radius));
    circle.setFillColor(sf::Color(100, 150, 250));

    circle.setPointCount(100);

    circle.setPosition(vp.screenSpace(sf::Vector2f(0.1, 0.6)) + sf::Vector2f(50,0));

    window.draw(circle);
}


float tween(float t, float start, float end) {
    return start + t * (end - start);
}
float easeIn(float t) {
    return t * t;
}

float easeOut(float t) {
    return 1 - easeIn(1-t);
}

float easeInOut(float t) {
    return tween(t, easeIn(t), easeOut(t));
}

float easeInCubic(float t) {
    return 16*t*t*t*t*t;
}

float easeOutCubic(float t) {
    return 1 - easeInCubic(1 - t);
}

float easeInOutCubic(float t) {
    //return tween(t, easeInCubic(t), easeOutCubic(t));
   return  t < 0.5 ? easeInCubic(t) : easeOutCubic(t);
}


int main() {

    Graph graph;
    sf::VideoMode mode = sf::VideoMode::getDesktopMode();
    width = mode.width *0.8;
    height = mode.height*0.8;
    sf::RenderWindow sfmlWin(sf::VideoMode(width, height), "Hello World SFML Window");
    sf::Font font;
    //You need to pass the font file location
    if (!font.loadFromFile("GOTHIC.ttf")) {
        return -1;
    }
    sf::Text message("Press ESC to quit", font);

    const int numPoints = 1002;
    float x[numPoints];
    float y[numPoints];

    float t = 0;


    Viewport overallVP(width*0.9, height * 0.9, width * 0.05, height * 0.05, width, height);
    Viewport graphVP(width/2, height/2, width / 4, height / 4, width, height);


    sf::Clock deltaClock;
    sf::Time timeForAnimation = sf::milliseconds(2000);
    sf::Time delayTime = sf::milliseconds(1);
    sf::Time pauseTime = sf::milliseconds(500);

    bool firstFrame = true, lastFrame = false;
    while (sfmlWin.isOpen()) {
        sf::Time dt = deltaClock.restart();
        t += dt.asSeconds() / timeForAnimation.asSeconds();

        sf::Event e;
        while (sfmlWin.pollEvent(e)) {

            switch (e.type) {
            case sf::Event::EventType::Closed:
                sfmlWin.close();
                break;
             case sf::Event::KeyPressed:
                {
                    //if (event.key.code >= sf::Keyboard::A && event.key.code <= sf::Keyboard::Z) {
                        sfmlWin.close();
                        break;
                
                }
            }
        }

        sfmlWin.clear();
        sfmlWin.draw(message);


        float y = easeInOutCubic(t);

        graph.addPoint(sf::Vector2f(t, y));
        graph.drawGraph(sfmlWin, graphVP);
        drawBall(sf::Vector2f(y, 0.2), sfmlWin, overallVP);
        drawChangeColorBall(y, sfmlWin, overallVP);        
        drawChangeSizeBall(y, sfmlWin, overallVP);


        sf::sleep(delayTime);

        sfmlWin.display();

        if (firstFrame) {
            sf::sleep(pauseTime);
            sf::Time dt = deltaClock.restart(); 
            firstFrame = false;

        }
        //assert(i < 1000);
        if (t >= 1) {
            sf::sleep(pauseTime);
            t = 0;
            graph.reset();
            firstFrame = true;
            deltaClock.restart();
        }


 
    }
    return 0;
}