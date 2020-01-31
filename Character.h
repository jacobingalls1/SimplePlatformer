//
// Created by Ophiuchus on 6/28/2018.
//

#ifndef SFML_TEMPLATE_CHARACTER_H
#define SFML_TEMPLATE_CHARACTER_H

#include <vector>
#include <cmath>
#include <string>
#include "Surface.h"
using namespace std;
#include <SFML/Graphics.hpp>
using namespace sf;


class Character {
    Vector2f pos;
    Vector2f vel;
    float stren;
    Vector2f size;
    Vector2f grav;
public:
    Character(Vector2f size=Vector2f(3, 3), Vector2f position=Vector2f(0, 0),
            float strength=.0005, Vector2f gravity=Vector2f(0, 0), Vector2f velocity=Vector2f(0, 0));
    void update(vector<Surface> surfaces);
    Vector2f position();
    int getDir(Vector2f target);
    void setPos(Vector2i);
    void setPos(Vector2f);
    Vector2f velocity();
    Vector2f size2f();
    vector<Vector2f> getCorners();
    void collision(Surface collide);
    float getStren();
    void accel(Vector2f toAdd);
    void moveUp(float amount);
    void moveDown(float amount);
    void moveLeft(float amount);
    void moveRight(float amount);
    void stop();
};


#endif //SFML_TEMPLATE_CHARACTER_H
