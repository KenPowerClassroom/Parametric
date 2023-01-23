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

int width = 800;
int height = 800;

sf::Vector2f toScreenSpace(sf::Vector2f p) {
    float margin = 100;
    sf::Vector2i origin(100, 100);

    float boxWidth = width - (2 * margin);
    float boxHeight = height - (2 * margin);

    float x = margin + boxWidth * p.x;
    float y = height - (margin + boxHeight * p.y);

    return sf::Vector2f(x, y);

}

void drawGraph(int numPoints, float xValues[], float yValues[], sf::RenderWindow& window) {



    sf::Vertex line[1001];
    line[0].position = toScreenSpace(sf::Vector2f(0, 1));
    line[0].color = sf::Color::White;
    line[1].position = toScreenSpace(sf::Vector2f(0, 0));
    line[1].color = sf::Color::White;
    line[2].position = toScreenSpace(sf::Vector2f(1, 0));
    line[2].color = sf::Color::White;
    window.draw(line, 3, sf::LineStrip);


    for (int i = 0; i < numPoints; i++) {
        line[i].position = toScreenSpace(sf::Vector2f(xValues[i], yValues[i]));
        line[i].color = sf::Color::White;
    }
    window.draw(line, numPoints, sf::LineStrip);

}

void drawBall(sf::Vector2f pos, sf::RenderWindow& window) {

    sf::CircleShape circle(25);
    circle.setFillColor(sf::Color(100, 250, 50));

    // change the number of sides (points) to 100
    circle.setPointCount(100);

    circle.setPosition(toScreenSpace(pos));

    window.draw(circle);
}





int main() {
    std::string s = "abc";
    std::cout << "Hello World!\n" << s;
    sf::RenderWindow sfmlWin(sf::VideoMode(width, height), "Hello World SFML Window");
    sf::Font font;
    //You need to pass the font file location
    if (!font.loadFromFile("GOTHIC.ttf")) {
        return -1;
    }
    sf::Text message("Hello, World !", font);

    const int numPoints = 1000;
    float x[numPoints];
    float y[numPoints];

    float t = 0;
    int i = 0;

    while (sfmlWin.isOpen()) {

        sf::Event e;
        while (sfmlWin.pollEvent(e)) {

            switch (e.type) {
            case sf::Event::EventType::Closed:
                sfmlWin.close();
                break;
            }
        }

        sf::Time delayTime = sf::milliseconds(1);

        sfmlWin.clear();
        sfmlWin.draw(message);

        x[i] = t;
        y[i] = sqrt(t);
        i++;

        drawGraph(i, x, y, sfmlWin);
        drawBall(sf::Vector2f(y[i], -0.05), sfmlWin);


        sf::sleep(delayTime);

        sfmlWin.display();

        t += 1.0/numPoints;

        if (t >= 1){
            t = 0;
            i = 0;
        }
    }
    return 0;
}