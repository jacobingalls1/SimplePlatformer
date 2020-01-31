#include <iostream>
#include <vector>
#include "Surface.h"
#include "Character.h"
using namespace std;

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
using namespace sf;


int main() {

    srand(time(NULL));

    const int SCREEN_SIZE = 1000, EDGE_OFFSET = 100;
    const Vector2f CORNERS[4] = {Vector2f(EDGE_OFFSET, EDGE_OFFSET), Vector2f(SCREEN_SIZE - EDGE_OFFSET, EDGE_OFFSET),
                         Vector2f(SCREEN_SIZE - EDGE_OFFSET, SCREEN_SIZE - EDGE_OFFSET), Vector2f(EDGE_OFFSET, SCREEN_SIZE - EDGE_OFFSET)};
    vector<Surface> surfaces;
    int mouseX = SCREEN_SIZE / 2, mouseY = SCREEN_SIZE / 2;
    for (int i = 0; i < 4; i++) {
        Vector2f vects[2] = {CORNERS[i], CORNERS[(i + 1) % 4]};
        surfaces.push_back(Surface(vects, .07, 1.1));
    }

//    surfaces.push_back(Surface(Vector2f(200, 800), Vector2f(800, 800)));


    vector<Character> characters = {Character(Vector2f(30, 30), Vector2f(500, 500), .7, Vector2f(0, .1))};

    RenderWindow window(VideoMode(SCREEN_SIZE, SCREEN_SIZE), "Simple", Style::None);
    window.requestFocus();
//    window.setMouseCursorVisible(false);
    window.setFramerateLimit(60);
    bool up(0), down(0), left(0), right(0);

    window.setPosition(Vector2i(0, 0));

    while( window.isOpen() ) {

        window.clear(Color::Black);

        Vector2i mouse = Mouse::getPosition();
        mouseX = mouse.x;
        mouseY = mouse.y;

        Vector2i pos = window.getPosition();
        Vector2i cent = pos + Vector2i(SCREEN_SIZE / 2, SCREEN_SIZE / 2);

        Vector2i screenVel = (mouse - cent) / 50;

        window.setPosition(pos + screenVel);

        Vector2i min = pos;
        Vector2i max = pos + Vector2i(SCREEN_SIZE, SCREEN_SIZE);

        Vector2f posF(pos.x, pos.y);

        for (int i = 0; i < surfaces.size(); i++) {
            RectangleShape rect;
            rect.setPosition(surfaces[i].getPos() - posF);
            rect.setSize(Vector2f(surfaces[i].xLen() + 10, surfaces[i].yLen() + 10));
            rect.setFillColor(Color::White);
            window.draw(rect);
        }

        for (int i = 0; i < characters.size(); i++) {
            characters[i].update(surfaces);
            RectangleShape again;
            again.setSize(characters[i].size2f());
            again.setPosition(characters[i].position() - posF);
            again.setFillColor(Color::White);
            window.draw(again);
        }

        window.display();


        for (int i = 0; i < characters.size(); i++) {
            float currStren = characters[i].getStren();
            if (up) {
                characters[i].moveUp(currStren);
            }
            if (down) {
                characters[i].moveDown(currStren);
            }
            if (left) {
                characters[i].moveLeft(currStren);
            }
            if (right) {
                characters[i].moveRight(currStren);
            }

        }


        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            } else if (event.type == Event::KeyPressed) {
                switch (event.key.code) {
                    case Keyboard::Escape:
                    case Keyboard::Q:
                        window.close();
                        break;
                    case Keyboard::Up:
                    case Keyboard::W:
                        up = true;
                        break;
                    case Keyboard::Down:
                    case Keyboard::S:
                        down = true;
                        break;
                    case Keyboard::Left:
                    case Keyboard::A:
                        left = true;
                        break;
                    case Keyboard::Right:
                    case Keyboard::D:
                        right = true;
                        break;
                    case Keyboard::P:
                        characters[0].stop();
                        break;
                }
            } else if (event.type == Event::KeyReleased) {
                switch (event.key.code) {
                    case Keyboard::Up:
                    case Keyboard::W:
                        up = false;
                        break;
                    case Keyboard::Down:
                    case Keyboard::S:
                        down = false;
                        break;
                    case Keyboard::Left:
                    case Keyboard::A:
                        left = false;
                        break;
                    case Keyboard::Right:
                    case Keyboard::D:
                        right = false;
                        break;
                }
            }
        }
    }

    return EXIT_SUCCESS;
}