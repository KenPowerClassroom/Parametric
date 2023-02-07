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
#include <map>

#include"Graph.h"
#include"Viewport.h"
#include"Functions.h"
#include"Problem.h"


int width = 800;
int height = 800;

void drawBall(sf::Vector2f pos, sf::RenderWindow& window, Viewport vp) {

    int radius = 25;
    sf::CircleShape circle(radius);
    circle.setFillColor(sf::Color(100, 250, 50));

    circle.setPointCount(100);

    circle.setPosition(vp.screenSpace(pos) - sf::Vector2f(radius,0));

    window.draw(circle);
}

void drawChangeColorBall(float t, float h, sf::RenderWindow& window, Viewport vp) {

    auto clamp = [](float i) {return i > 1.0 ? 1.0 : i<0?0.0:i;  };
    int radius = 25;
    sf::CircleShape circle(radius);
    int trans =  0 + clamp(t) * (255 - 0);
    
    circle.setFillColor(sf::Color(200, 150, 50, trans));

    circle.setPointCount(100);

    circle.setPosition(vp.screenSpace(sf::Vector2f(0.05,h)));

    sf::CircleShape outLine(radius);
    outLine.setFillColor(sf::Color(0,0,0, 0));
    outLine.setOutlineThickness(2);
    outLine.setOutlineColor(sf::Color(200, 150, 50));

    outLine.setPointCount(100);

    outLine.setPosition(vp.screenSpace(sf::Vector2f(0.05, h)));

    window.draw(outLine);
    window.draw(circle);
}

void drawChangeSizeBall(float t, float h, sf::RenderWindow& window, Viewport vp) {

    int endRadius = 25;
    int radius = 0 + t * (endRadius - 0);
    sf::CircleShape circle(radius);

    circle.setOrigin(sf::Vector2f(radius, radius));
    circle.setFillColor(sf::Color(100, 150, 250));

    circle.setPointCount(100);

    circle.setPosition(vp.screenSpace(sf::Vector2f(0.0, h)) + sf::Vector2f(endRadius, endRadius));
    
    sf::CircleShape outLine(endRadius);
    outLine.setOrigin(sf::Vector2f(endRadius, endRadius));
    outLine.setFillColor(sf::Color(0, 0, 0, 0));
    outLine.setOutlineThickness(2);
    outLine.setOutlineColor(sf::Color(100, 150, 250));

    outLine.setPointCount(100);

    outLine.setPosition(vp.screenSpace(sf::Vector2f(0.0, h)) + sf::Vector2f(endRadius, endRadius) );

    window.draw(outLine);
    window.draw(circle);
}
void drawBalls(float t, float h, sf::RenderWindow& window, Viewport vp){
    drawBall(sf::Vector2f(t, h), window, vp);
    drawChangeColorBall(t, h, window, vp);
    drawChangeSizeBall(t, h,  window, vp);
}

float tween(float t, float start, float end) {
    return start + t * (end - start);
}
float easeInQuadratic(float t) {
    return 2 * t * t;
}

float easeOutQuadratic(float t) {
    return 1 - easeInQuadratic(1-t);
}

float easeInOutQuadratic(float t) {
    //return tween(t, easeInQuadratic(t), easeOutQuadratic(t));
    return  t < 0.5 ? easeInQuadratic(t) : easeOutQuadratic(t);
}

float easeInCubic(float t) {
    return 4*t*t*t;
}

float easeOutCubic(float t) {
    return 1 - easeInCubic(1 - t);
}

float easeInOutCubic(float t) {
    //return tween(t, easeInCubic(t), easeOutCubic(t));
   return  t < 0.5 ? easeInCubic(t) : easeOutCubic(t);
}

float easeInQuintic(float t) {
    return 16 * t *t * t * t * t;
}

float easeOutQuintic(float t) {
    return 1 - easeInQuintic(1 - t);
}

float easeInOutQuintic(float t) {
    //return tween(t, easeInCubic(t), easeOutCubic(t));
    return  t < 0.5 ? easeInQuintic(t) : easeOutQuintic(t);
}

float easeInBack(float t) {

    const float c1 = 1.70158;
    const float c3 = c1 + 1;

    return 4*c3 * t * t * t - 2*c1 * t * t;
    
}

float easeOutBack(float t) {

    return 1 - easeInBack(1 - t);

}

float easeInOutBack(float t) {
    //return tween(t, easeInCubic(t), easeOutCubic(t));
    return  t < 0.5 ? easeInBack(t) : easeOutBack(t);
}

float sqr(float f) { return f * f; }
float cub(float f) { return f * f*f; }

float parabola(float t) {

    return 4*sqr(t-0.5);

}

float parabolaTarget(float t) {

    return sqr(t - 0.75);

}


int main() {




    sf::VideoMode mode = sf::VideoMode::getDesktopMode();
    width = mode.width *0.8;
    height = mode.height*0.8;
    sf::RenderWindow sfmlWin(sf::VideoMode(width, height), "Hello World SFML Window");
    sf::Font font;
    //You need to pass the font file location
    if (!font.loadFromFile("cmr12.ttf")) {
        return -1;
    }
    sf::Text message("Press ESC to quit", font);


    float t = 0;


    Viewport overallVP(width*0.9, height * 0.9, width * 0.05, height * 0.05, width, height);
    Viewport graphVP(height / 2, height/2, width / 4, 3.8*height / 8, width, height);

    Graph graph(sfmlWin, graphVP);

    graph.addCurve(sf::Color(100, 100, 100), 0.03);
    graph.addCurve(sf::Color::Green);
	
    sf::Clock deltaClock;
    sf::Time timeForAnimation = sf::milliseconds(2000);
    sf::Time delayTime = sf::milliseconds(1);
    sf::Time pauseTime = sf::milliseconds(500);


    typedef float (*myFunc)(float);

    //myFunc functions[3] = { &easeInOutQuadratic , &easeInOutQuintic, &easeInOutBack };

    map<sf::Keyboard::Key, Problem> problems;
	
    problems[sf::Keyboard::Key::A] = Problem("Move line up", "Make the white line go through the grey region", "lineA", lineA, lineATarget);
    problems[sf::Keyboard::Key::B] = Problem("Move line up", "Make the white line go through the grey region", "????", easeInOutQuadratic, easeInOutBack);
    problems[sf::Keyboard::Key::C] = Problem("Move line up", "Make the white line go through the grey region", "????", lineB, lineBTarget);    
    problems[sf::Keyboard::Key::D] = Problem("Move line up", "Make the white line go through the grey region", "????", parabola, parabolaTarget);

    Problem currentProblem = problems[sf::Keyboard::Key::A];
    bool firstFrame = true, lastFrame = false;
    while (sfmlWin.isOpen()) {
        bool changeProblem = false;
        sf::Time dt = deltaClock.restart();
        t += dt.asSeconds() / timeForAnimation.asSeconds();

        sf::Event e;
		
        while (sfmlWin.pollEvent(e)) {

            switch (e.type) {
            case sf::Event::EventType::Closed:
                sfmlWin.close();
                break;
            case sf::Event::KeyPressed:
                if (e.key.code == sf::Keyboard::Escape) {
                    sfmlWin.close();
                    break;
                }
				auto p = problems.find(e.key.code);
                if (p != problems.end()) {
                    currentProblem =p->second;
                    changeProblem = true;
                    break;
                }
            }
            
        }

        if (t >= 1 or changeProblem) {
            if(!changeProblem)sf::sleep(pauseTime);
            t = 0;
            graph.reset();


            firstFrame = true;
            deltaClock.restart();
            continue;
        }

        sfmlWin.clear();
        sfmlWin.draw(message);

        float y;
		
        y = currentProblem.target(t);
        graph.addPoint(0, sf::Vector2f(t, y));
        drawBalls(y, 0.1 * 0, sfmlWin, overallVP);


        y = currentProblem.starter(t);
        graph.addPoint(1, sf::Vector2f(t, y));
        drawBalls(y, 0.1 * 1, sfmlWin, overallVP);

		
        //int i = 0;
        //for (auto f : functions) {
        //    float y = f(t);
        //    graph.addPoint(i, sf::Vector2f(t, y));
        //    drawBalls(y, 0.1*i, sfmlWin, overallVP);
        //    i++;
        //}
		
        //float y = easeInOutQuadratic(t);
        //float quin = easeInOutQuintic(t);
        //float easeBack = easeInOutBack(t);

        graph.drawGraph();

        sf::sleep(delayTime);

        sfmlWin.display();

        if (firstFrame) {
            sf::sleep(pauseTime);
            sf::Time dt = deltaClock.restart(); 
            firstFrame = false;

        }
        //assert(i < 1000);



 
    }
    return 0;
}