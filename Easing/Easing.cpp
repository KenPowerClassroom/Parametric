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

void drawProblemScreen(Problem p, float t, RenderWindow& window, Graph& graph, Font& cmr, Font& mono) {

    graph.addCurve(Color(100, 100, 100), 0.03);
    graph.addCurve(Color::Green);

    Text message("", cmr);
    Text fnMessage("", mono);

    float textVPosition = 0;
    int paragraphSpacing = 20;
    message.setString("Problem #" + to_string(p.index));
    message.setCharacterSize(40);
    message.setLineSpacing(2);
    textVPosition += message.getGlobalBounds().height + paragraphSpacing;
    window.draw(message);

    string commonText = "The green line is generated from a function\nwhich is found in the file functions.cpp.\nYour job is to modify the function\nso that the green line matches the grey line";

    message.setString(commonText);
    message.setCharacterSize(24);
    message.setLineSpacing(1.5);
    message.setPosition(0, textVPosition);
    textVPosition += message.getGlobalBounds().height + paragraphSpacing;
    window.draw(message);

    message.setString(string("Function to change is called: ") );
    message.setCharacterSize(24);
    message.setLineSpacing(1.5);
    message.setPosition(0, textVPosition);
    textVPosition += message.getGlobalBounds().height + paragraphSpacing;
    window.draw(message);

    fnMessage.setString(string("float ")+p.starterFunction + "(float t);");
    fnMessage.setCharacterSize(24);
    fnMessage.setLineSpacing(1.5);
    fnMessage.setPosition(0, textVPosition);
    textVPosition += fnMessage.getGlobalBounds().height + paragraphSpacing;
    window.draw(fnMessage);

    float y;

    y = p.target(t);
    graph.addPoint(0, Vector2f(t, y));
    drawBalls(y, 0.1 * 0, window);


    y = p.starter(t);
    graph.addPoint(1, Vector2f(t, y));
    drawBalls(y, 0.1 * 1, window);


    View graphView;
    graphView.reset(FloatRect(-150, 650, 750, -750));
    graphView.setViewport(FloatRect(0.5, 0.0, 0.5, 0.5 * ((float)width / height)));
    window.setView(graphView);
    graph.drawGraph();


}

class MainScreen {

    vector<Graph> graphs;
    vector<Problem> problems;
    RenderWindow& window;
    Font& font;

public:
    MainScreen(RenderWindow& w, Font& f) :window(w), font(f) {}

    void init(vector<Problem> ps) {

        for (auto p : ps) {
            graphs.push_back(Graph(window));
            problems.push_back(p);
        }
        for (auto& g : graphs) {
            g.addCurve(Color(100, 100, 100), 0.03);
            g.addCurve(Color::Green);
        }
    }

    void reset() {
        for (auto& g : graphs) {
            g.reset();
        }
    }
    void draw(float t) {
        float graphUnit = Graph::Unit;
        float padding = graphUnit * 0.1;
        

        int problemsPerColumn = problems.size() / 2;
        float problemHeight = 1.0 / problemsPerColumn;
        float problemPadding = problemHeight * 0.25;
        const View tempView = window.getView();
        
        View graphView;
        int lineHeight = 50;
        Text message("Problem #888XXX", font);
        message.setScale(1, -1);
        message.setCharacterSize(150);
        Text textMatch("Function matches", font);
        textMatch.setScale(1, -1);
        textMatch.setCharacterSize(100);
        textMatch.setFillColor(sf::Color::Green);
        Text textNoMatch("Function does not match", font);
        textNoMatch.setScale(1, -1);
        textNoMatch.setCharacterSize(100);
        textNoMatch.setFillColor(sf::Color::Red);
        Text moreInfo("For more info, press XXX", font);
        moreInfo.setScale(1, -1);
        moreInfo.setCharacterSize(75);
        moreInfo.setFillColor(sf::Color(100,100,100));


        float textWidth = message.getGlobalBounds().width;
        float textHeight = message.getGlobalBounds().height;

        float problemLocalWidth = textWidth + 3 * padding + graphUnit;;
        float problemLocalHeight = graphUnit + 2 * padding;
        float problemLocalLeft = -2 * padding - textWidth;
        float problemLocalTop = padding + graphUnit;

        message.setPosition(-textWidth - padding, textHeight + (problemLocalHeight - textHeight)*2.0 / 3);
        textMatch.setPosition(-textWidth - padding, textHeight + (problemLocalHeight - textHeight)*1.0 / 3);
        textNoMatch.setPosition(-textWidth - padding, textHeight + (problemLocalHeight - textHeight) * 1.0 / 3);
        moreInfo.setPosition(-textWidth - padding, textHeight + (problemLocalHeight - textHeight) * 0.0 / 3);


        float aspect = abs(problemLocalWidth / problemLocalHeight);

        float columnLeft = 0.0;
        int i = 0;
        int rowsInColumn = 0;
        graphView.reset(FloatRect(problemLocalLeft, problemLocalTop, problemLocalWidth, -problemLocalHeight));
        for (auto p : problems) {

            graphView.setViewport(FloatRect(columnLeft, rowsInColumn * problemHeight, problemHeight *aspect, problemHeight));
            window.setView(graphView);
            message.setString("Problem #" + to_string(i));
            window.draw(message);
            if(p.check())
                window.draw(textMatch);
            else
                window.draw(textNoMatch);
            moreInfo.setString(string("for more info, press [") + char('A' + i) + string("]"));
            window.draw(moreInfo);
            

            drawProblem(t, p,  i);
            i++;
            rowsInColumn++;
            if (rowsInColumn >= problemsPerColumn) {
                rowsInColumn = 0;
                columnLeft = 0.5;
            }
        }
        
        window.setView(tempView);
    }

    void drawProblem(float t, Problem& p, int i) {
        float y;

        y = p.target(t);
        graphs[i].addPoint(0, Vector2f(t, y));

        y = p.starter(t);
        graphs[i].addPoint(1, Vector2f(t, y));

        graphs[i].drawGraph();



    }


};


int main() {

    VideoMode mode = VideoMode::getDesktopMode();
    width = mode.width *0.8;
    height = mode.height*0.8;
    RenderWindow sfmlWin(VideoMode(width, height), "Hello World SFML Window");
    View view;
    view.reset(FloatRect(0,0,width,height));

    Font font;
    if (!font.loadFromFile("cmr6.ttf")) {
        return -1;
    }

    Font monoFont;
    if (!monoFont.loadFromFile("AnonymousPro.ttf")) {
        return -1;
    }



    float t = 0;
    Graph graph(sfmlWin);
	
    Clock deltaClock;
    Time timeForAnimation = milliseconds(1000);
    Time delayTime = milliseconds(1);
    Time pauseTime = milliseconds(500);

    typedef float (*myFunc)(float);

    vector<Problem> problems;
    int i = 0;
    problems.push_back(Problem("Move line up", i++, "", "moveHorizLine", moveHorizLine, moveHorizLineTarget));
    problems.push_back(Problem("Move line up", i++, "", "changeSlope", changeSlope, changeSlopeTarget));
    problems.push_back(Problem("Move line up", i++, "", "changeSlopeAndMove", changeSlopeAndMove, changeSlopeAndMoveTarget));
    problems.push_back(Problem("Move line up", i++, "", "moveParabolaLeft", moveParabolaLeft, moveParabolsLeftTarget));
    problems.push_back(Problem("Move line up", i++, "", "moveParabolaUp", moveParabolaUp, moveParabolaUpTarget));
    problems.push_back(Problem("Move line up", i++, "", "invertParabola", invertParabola, invertParabolaTarget));
    problems.push_back(Problem("Move line up", i++, "", "widenParabola", widenParabola, widenParabolaTarget));
    problems.push_back(Problem("Move line up", i++, "", "widenAndMoveParabola", widenAndMoveParabola, widenAndMoveParabolaTarget));
    problems.push_back(Problem("Move line up", i++, "", "easeIn", easeIn, easeInTarget));
    problems.push_back(Problem("Move line up", i++, "", "easeInUpsideDown", easeInUpsideDown, easeInUpsideDownTarget));
    problems.push_back(Problem("Move line up", i++, "", "easeInFlipVert", easeInFlipVert, easeInFlipVertTarget));
    problems.push_back(Problem("Move line up", i++, "", "easeOut", easeOut, easeOutTarget));
    problems.push_back(Problem("Move line up", i++, "", "easeInThruCentre", easeInThruCentre, easeInThruCentreTarget));
    problems.push_back(Problem("Move line up", i++, "", "easeOutThruCentre", easeOutThruCentre, easeOutThruCentreTarget));


    Problem currentProblem = problems.at(0);
    bool firstFrame = true, lastFrame = false;

    enum Screen { menu, problem} screen = menu;

    MainScreen mainscreen(sfmlWin, font);
    mainscreen.init(problems);

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
                if (screen == problem) {
                    screen = menu;
                    break;
                }
                    
                int k = e.key.code;
                if (k>= 0 && k < problems.size()) {
				    auto& p = problems.at(k);
                    currentProblem = p;
                    changeProblem = true;
                    screen = problem;
                    break;
                }
            }
            
        }
        sfmlWin.setView(view);
        
        if (t >= 1 or changeProblem) {
            if(!changeProblem) sleep(pauseTime);
            t = 0;
            graph.reset();
            mainscreen.reset();

            firstFrame = true;
            deltaClock.restart();
            continue;
        }

        sfmlWin.clear();
        if (screen == menu)
            //drawMainScreen(problems, t, sfmlWin, graph, font);
            mainscreen.draw(t);

        if (screen == problem)
            drawProblemScreen(currentProblem, t, sfmlWin, graph, font, monoFont);
        
        sleep(delayTime);

        sfmlWin.display();

        if (firstFrame) {
            mainscreen.reset();
            sleep(pauseTime);
            Time dt = deltaClock.restart(); 
            firstFrame = false;

        }

    }
    return 0;
}