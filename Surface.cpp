//
// Created by Ophiuchus on 6/28/2018.
//

#include "Surface.h"
#include <iostream>
using namespace std;

bool fComp(float a, float b) {
    return abs(a - b) < .1;
}

bool ccw(Vector2f a, Vector2f b, Vector2f c) {
    return (c.y-a.y)*(b.x-a.x) > (b.y-a.y)*(c.x-a.x);
}

bool betwixt(Vector2f a, Vector2f b, Vector2f c, Vector2f d) {
    return ccw(a, c, d) != ccw(b, c, d) && ccw(a, b, c) != ccw(a, b, d);
}

float len(Vector2f a, Vector2f b) {
    return (float)sqrt(pow((a.x - b.x), 2) + pow((a.y - b.y), 2));
}

Surface::Surface(Vector2f *vertIn, float friction, float bounce) {
    for (int i = 0; i < 2; i++) {
        vertices[i] = vertIn[i];
    }
    slope = (vertIn[0].x - vertIn[1].x) / (vertIn[0].y - vertIn[1].y);
    this->friction = friction;
    this->bounce = bounce;
}

Surface::Surface(Vector2f a, Vector2f b, float friction, float bounce) {
    vertices[0] = a;
    vertices[1] = b;
    this->friction = friction;
    this->bounce = bounce;
}

bool Surface::collision(Vector2f init, Vector2f target) {
    return betwixt(init, target, vertices[0], vertices[1]);
}

float Surface::getSlope() {
    return slope;
}

Vector2f Surface::getFirst() {
    return vertices[0];
}

Vector2f Surface::getSecond() {
    return vertices[1];
}

RectangleShape Surface::getRect() {
    RectangleShape rect;
    float len = length();
    rect.setSize(Vector2f(len, 10));
//    rect.rotate((float)asin(((-vertices[0].y + vertices[1].y) / len) / 3.141592 * 180));
    return rect;
}

float Surface::getFrict() {
    return friction;
}

float Surface::getBounce() {
    return bounce;
}

Vector2f Surface::getPos() {
    if (vertices[0].x < vertices[1].x or vertices[0].y < vertices[1].y) {
        return vertices[0];
    } else {
        return vertices[1];
    }
}

bool Surface::isOnSurface(Vector2f in) {

}

Vector2f Surface::onSurface(Vector2f a, Vector2f b) {

}

Vector2f Surface::lenVect() {
    return Vector2f(abs(vertices[1].y - vertices[0].y), abs(vertices[1].x - vertices[0].x));
}

float Surface::length() {
    return len(vertices[0], vertices[1]);
}

float Surface::xLen() {
    return abs(vertices[0].x - vertices[1].x);
}

float Surface::yLen() {
    return abs(vertices[0].y - vertices[1].y);
}


