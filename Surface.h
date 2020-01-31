//
// Created by Ophiuchus on 6/28/2018.
//

#ifndef SFML_TEMPLATE_SURFACE_H
#define SFML_TEMPLATE_SURFACE_H

#include <vector>
#include <cmath>
using namespace std;
#include <SFML/Graphics.hpp>
using namespace sf;

class Surface {
    Vector2f vertices[2];
    float slope;
    float friction;
    float bounce;
public:
    Surface(Vector2f vertIn[2], float friction=0, float bounce=0);
    Surface(Vector2f a, Vector2f b, float friction=0, float bounce=0);
    bool collision(Vector2f init, Vector2f terget);
    float getSlope();
    Vector2f getFirst();
    Vector2f getSecond();
    RectangleShape getRect();
    float getFrict();
    float getBounce();
    Vector2f getPos();
    bool isOnSurface(Vector2f in);
    Vector2f onSurface(Vector2f a, Vector2f b);
    Vector2f lenVect();
    float length();
    float xLen();
    float yLen();
};


#endif //SFML_TEMPLATE_SURFACE_H
