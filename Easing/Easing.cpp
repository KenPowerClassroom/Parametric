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
#include"Problem.h"
#include"Functions.h"


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




int main() {




    sf::VideoMode mode = sf::VideoMode::getDesktopMode();
    width = mode.width *0.8;
    height = mode.height*0.8;
    sf::RenderWindow sfmlWin(sf::VideoMode(width, height), "Hello World SFML Window");
    sf::View view;
    view.reset(sf::FloatRect(0,0,width,height));
    sf::Font font;
    //You need to pass the font file location
    if (!font.loadFromFile("cmr12.ttf")) {
        return -1;
    }


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
	
    string commonText = "The green line is generated from a function\nwhich is found in the file functions.cpp.\nYour job is to modify the function\n so that the green line matches the grey line";
    problems[sf::Keyboard::Key::A] = Problem("Move line up", "", "lineA", moveHorizLine, moveHorizLineTarget);
    problems[sf::Keyboard::Key::B] = Problem("Move line up", "The green line is generated from the function lineA(t) \nwhich is found in the file functions.cpp. Your job is to \tmodify the function so that the green line follow the grey region", "lineA", changeSlope, changeSlopeTarget);
    problems[sf::Keyboard::Key::C] = Problem("Move line up", "The green line is generated from the function lineA(t) \nwhich is found in the file functions.cpp. Your job is to \tmodify the function so that the green line follow the grey region", "lineA", changeSlopeAndMove, changeSlopeAndMoveTarget);
    problems[sf::Keyboard::Key::D] = Problem("Move line up", "The green line is generated from the function lineA(t) \nwhich is found in the file functions.cpp. Your job is to \tmodify the function so that the green line follow the grey region", "lineA", moveParabolsLeft, moveParabolsLeftTarget);
    problems[sf::Keyboard::Key::E] = Problem("Move line up", "The green line is generated from the function lineA(t) \nwhich is found in the file functions.cpp. Your job is to \tmodify the function so that the green line follow the grey region", "lineA", moveParabolaUp, moveParabolaUpTarget);
    problems[sf::Keyboard::Key::F] = Problem("Move line up", "The green line is generated from the function lineA(t) \nwhich is found in the file functions.cpp. Your job is to \tmodify the function so that the green line follow the grey region", "lineA", invertParabola, invertParabolaTarget);
    problems[sf::Keyboard::Key::G] = Problem("Move line up", "The green line is generated from the function lineA(t) \nwhich is found in the file functions.cpp. Your job is to \tmodify the function so that the green line follow the grey region", "lineA", widenParabola, widenParabolaTarget);
    problems[sf::Keyboard::Key::H] = Problem("Move line up", "The green line is generated from the function lineA(t) \nwhich is found in the file functions.cpp. Your job is to \tmodify the function so that the green line follow the grey region", "lineA", widenAndMoveParabola, widenAndMoveParabolaTarget);
    problems[sf::Keyboard::Key::I] = Problem("Move line up", "The green line is generated from the function lineA(t) \nwhich is found in the file functions.cpp. Your job is to \tmodify the function so that the green line follow the grey region", "lineA", easeIn, easeInTarget);
    problems[sf::Keyboard::Key::J] = Problem("Move line up", "The green line is generated from the function lineA(t) \nwhich is found in the file functions.cpp. Your job is to \tmodify the function so that the green line follow the grey region", "lineA", easeInUpsideDown, easeInUpsideDownTarget);
    problems[sf::Keyboard::Key::K] = Problem("Move line up", "The green line is generated from the function lineA(t) \nwhich is found in the file functions.cpp. Your job is to \tmodify the function so that the green line follow the grey region", "lineA", easeInFlipVert, easeInFlipVertTarget);
    problems[sf::Keyboard::Key::L] = Problem("Move line up", "The green line is generated from the function lineA(t) \nwhich is found in the file functions.cpp. Your job is to \tmodify the function so that the green line follow the grey region", "lineA", easeOut, easeOutTarget);
    problems[sf::Keyboard::Key::M] = Problem("Move line up", "The green line is generated from the function lineA(t) \nwhich is found in the file functions.cpp. Your job is to \tmodify the function so that the green line follow the grey region", "lineA", easeInThruCentre, easeInThruCentreTarget);
    problems[sf::Keyboard::Key::N] = Problem("Move line up", "The green line is generated from the function lineA(t) \nwhich is found in the file functions.cpp. Your job is to \tmodify the function so that the green line follow the grey region", "lineA", easeOutThruCentre, easeOutThruCentreTarget);


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
            case sf::Event::EventType::Resized:
                view.setViewport(sf::FloatRect(0, 0, (float)width/e.size.width, float(height)/e.size.height));
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
        sfmlWin.setView(view);

        if (t >= 1 or changeProblem) {
            if(!changeProblem)sf::sleep(pauseTime);
            t = 0;
            graph.reset();


            firstFrame = true;
            deltaClock.restart();
            continue;
        }

        sfmlWin.clear();
        sf::Text message(commonText, font);
        message.setCharacterSize(24);
        message.setLineSpacing(1.25);
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

        sf::View graphView;
        graphView.reset(sf::FloatRect(-1, 1, 3.0, -3.0));
        graphView.setViewport(sf::FloatRect(0.5, 0.1, 0.5, 0.5*((float)width/height)));
        sfmlWin.setView(graphView);
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