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

void drawGraph(int numPoints, float xValues[], float yValues[], sf::RenderWindow& window) {

    sf::Vertex line[2];
    line[0].position = sf::Vector2f(100, 700);
    line[0].color = sf::Color::Red;
    line[1].position = sf::Vector2f(100, 100);
    line[1].color = sf::Color::Red;

    window.draw(line);

}

int main() {
    std::string s = "abc";
    std::cout << "Hello World!\n" << s;
    sf::RenderWindow sfmlWin(sf::VideoMode(800, 800), "Hello World SFML Window");
    sf::Font font;
    //You need to pass the font file location
    if (!font.loadFromFile("GOTHIC.ttf")) {
        return -1;
    }
    sf::Text message("Hello, World !", font);

    float x[]{ 1,2,3,4,5,6,7,8,9,10 };
    float y[]{ 1,2,3,4,4,4,3,2,9,10 };


    while (sfmlWin.isOpen()) {

        sf::Event e;
        while (sfmlWin.pollEvent(e)) {

            switch (e.type) {
            case sf::Event::EventType::Closed:
                sfmlWin.close();
                break;
            }
        }

        sfmlWin.clear();
        sfmlWin.draw(message);
        drawGraph(10, x, y, sfmlWin);
        sfmlWin.display();
    }
    return 0;
}