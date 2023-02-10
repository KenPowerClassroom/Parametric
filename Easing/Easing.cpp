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

using namespace std;
using namespace sf;

int width = 800;
int height = 800;

void drawBall(Vector2f pos, RenderWindow& window) {

    int radius = 25;
    CircleShape circle(radius);
    circle.setFillColor(Color(100, 250, 50));

    circle.setPointCount(100);

    circle.setPosition(pos - Vector2f(radius,0));

    window.draw(circle);
}

void drawChangeColorBall(float t, float h, RenderWindow& window) {

    auto clamp = [](float i) {return i > 1.0 ? 1.0 : i<0?0.0:i;  };
    int radius = 25;
    CircleShape circle(radius);
    int trans =  0 + clamp(t) * (255 - 0);
    
    circle.setFillColor(Color(200, 150, 50, trans));

    circle.setPointCount(100);

    circle.setPosition(Vector2f(0.05,h));

    CircleShape outLine(radius);
    outLine.setFillColor(Color(0,0,0, 0));
    outLine.setOutlineThickness(2);
    outLine.setOutlineColor(Color(200, 150, 50));

    outLine.setPointCount(100);

    outLine.setPosition(Vector2f(0.05, h));

    window.draw(outLine);
    window.draw(circle);
}

void drawChangeSizeBall(float t, float h, RenderWindow& window) {

    int endRadius = 25;
    int radius = 0 + t * (endRadius - 0);
    CircleShape circle(radius);

    circle.setOrigin(Vector2f(radius, radius));
    circle.setFillColor(Color(100, 150, 250));

    circle.setPointCount(100);

    circle.setPosition(Vector2f(0.0, h) + Vector2f(endRadius, endRadius));
    
    CircleShape outLine(endRadius);
    outLine.setOrigin(Vector2f(endRadius, endRadius));
    outLine.setFillColor(Color(0, 0, 0, 0));
    outLine.setOutlineThickness(2);
    outLine.setOutlineColor(Color(100, 150, 250));

    outLine.setPointCount(100);

    outLine.setPosition(Vector2f(0.0, h) + Vector2f(endRadius, endRadius)) ;

    window.draw(outLine);
    window.draw(circle);
}
void drawBalls(float t, float h, RenderWindow& window){
    drawBall(Vector2f(t, h), window);
    drawChangeColorBall(t, h, window);
    drawChangeSizeBall(t, h,  window);
}




int main() {




    VideoMode mode = VideoMode::getDesktopMode();
    width = mode.width *0.8;
    height = mode.height*0.8;
    RenderWindow sfmlWin(VideoMode(width, height), "Hello World SFML Window");
    View view;
    view.reset(FloatRect(0,0,width,height));
    Font font;
    //You need to pass the font file location
    if (!font.loadFromFile("cmr12.ttf")) {
        return -1;
    }


    float t = 0;


    Graph graph(sfmlWin);

    graph.addCurve(Color(100, 100, 100), 0.03);
    graph.addCurve(Color::Green);
	
    Clock deltaClock;
    Time timeForAnimation = milliseconds(2000);
    Time delayTime = milliseconds(1);
    Time pauseTime = milliseconds(500);


    typedef float (*myFunc)(float);

    //myFunc functions[3] = { &easeInOutQuadratic , &easeInOutQuintic, &easeInOutBack };

    map<Keyboard::Key, Problem> problems;
    int i = 0;
    string commonText = "The green line is generated from a function\nwhich is found in the file functions.cpp.\nYour job is to modify the function\n so that the green line matches the grey line";
    problems[Keyboard::Key::A] = Problem("Move line up", i++,"", "lineA", moveHorizLine, moveHorizLineTarget);
    problems[Keyboard::Key::B] = Problem("Move line up", i++,"" , "lineA", changeSlope, changeSlopeTarget);
    problems[Keyboard::Key::C] = Problem("Move line up", i++,"" , "lineA", changeSlopeAndMove, changeSlopeAndMoveTarget);
    problems[Keyboard::Key::D] = Problem("Move line up", i++,"" , "lineA", moveParabolsLeft, moveParabolsLeftTarget);
    problems[Keyboard::Key::E] = Problem("Move line up", i++,"" , "lineA", moveParabolaUp, moveParabolaUpTarget);
    problems[Keyboard::Key::F] = Problem("Move line up", i++,"" , "lineA", invertParabola, invertParabolaTarget);
    problems[Keyboard::Key::G] = Problem("Move line up", i++,"" , "lineA", widenParabola, widenParabolaTarget);
    problems[Keyboard::Key::H] = Problem("Move line up", i++,"" , "lineA", widenAndMoveParabola, widenAndMoveParabolaTarget);
    problems[Keyboard::Key::I] = Problem("Move line up", i++,"" , "lineA", easeIn, easeInTarget);
    problems[Keyboard::Key::J] = Problem("Move line up", i++,"" , "lineA", easeInUpsideDown, easeInUpsideDownTarget);
    problems[Keyboard::Key::K] = Problem("Move line up", i++,"" , "lineA", easeInFlipVert, easeInFlipVertTarget);
    problems[Keyboard::Key::L] = Problem("Move line up", i++,"" , "lineA", easeOut, easeOutTarget);
    problems[Keyboard::Key::M] = Problem("Move line up", i++,"" , "lineA", easeInThruCentre, easeInThruCentreTarget);
    problems[Keyboard::Key::N] = Problem("Move line up", i++,"" , "lineA", easeOutThruCentre, easeOutThruCentreTarget);


    Problem currentProblem = problems[Keyboard::Key::A];
    bool firstFrame = true, lastFrame = false;
    while (sfmlWin.isOpen()) {
        bool changeProblem = false;
        Time dt = deltaClock.restart();
        t += dt.asSeconds() / timeForAnimation.asSeconds();

        
        Event e;
		
        while (sfmlWin.pollEvent(e)) {

            switch (e.type) {
            case Event::EventType::Closed:
                sfmlWin.close();
                break;
            case Event::EventType::Resized:
                view.setViewport(FloatRect(0, 0, (float)width/e.size.width, float(height)/e.size.height));
                break;

            case Event::KeyPressed:
                if (e.key.code == Keyboard::Escape) {
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
            if(!changeProblem)sleep(pauseTime);
            t = 0;
            graph.reset();


            firstFrame = true;
            deltaClock.restart();
            continue;
        }

        sfmlWin.clear();
        Text message(commonText, font);
        message.setCharacterSize(24);
        message.setLineSpacing(1.5);
        sfmlWin.draw(message);

        float y;
		
        y = currentProblem.target(t);
        graph.addPoint(0, Vector2f(t, y));
        drawBalls(y, 0.1 * 0, sfmlWin);


        y = currentProblem.starter(t);
        graph.addPoint(1, Vector2f(t, y));
        drawBalls(y, 0.1 * 1, sfmlWin);


        View graphView;
        graphView.reset(FloatRect(-0.3, 1.3, 1.5, -1.5));
        graphView.setViewport(FloatRect(0.5, 0.0, 0.5, 0.5*((float)width/height)));
        sfmlWin.setView(graphView);
        graph.drawGraph();

        sleep(delayTime);

        sfmlWin.display();

        if (firstFrame) {
            sleep(pauseTime);
            Time dt = deltaClock.restart(); 
            firstFrame = false;

        }

    }
    return 0;
}