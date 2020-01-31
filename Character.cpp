//
// Created by Ophiuchus on 6/28/2018.
//

#include <iostream>
#include "Character.h"

float dotProd(Vector2f a, Vector2f b) {
    return a.x * b.x + a.y * b.y;
}

Character::Character(Vector2f size, Vector2f position, float strength,
        Vector2f gravity, Vector2f velocity) {
    pos = position;
    vel = velocity;
    stren = strength;
    this->size = size;
    grav = gravity;
}

int Character::getDir(Vector2f target) { // {> ^ < V}
    if (abs(target.x) > abs(target.y)) {
        if (target.x > 0) {
            return 0;
        } else {
            return 2;
        }
    } else {
        if (target.y > 0) {
            return 3;
        } else {
            return 1;
        }
    }
}

Vector2f Character::position() {
    return pos;
}

void Character::setPos(Vector2f in) {
    pos = in;
}

void Character::setPos(Vector2i in) {
    pos = Vector2f(in.x, in.y);
}

Vector2f Character::velocity() {
    return vel;
}

Vector2f Character::size2f() {
    return size;
}

vector<Vector2f> Character::getCorners() {
    vector<Vector2f> corners;
    corners.push_back(pos);
    corners.push_back(pos + Vector2f(size.x, 0));
    corners.push_back(pos + size);
    corners.push_back(pos + Vector2f(0, size.y));
    return corners;
}

void Character::collision(Surface collide) {
    switch (getDir(collide.lenVect())) { //{> ^ < V}
        case 0:
        case 2:
            vel.x *= -collide.getBounce();
            vel.y -= vel.y * collide.getFrict();
            break;
        case 1:
        case 3:
            vel.y *= -collide.getBounce();
            vel.x -= vel.x * collide.getFrict();
    }

}

float Character::getStren() {
    return stren;
}

void Character::update(vector<Surface> surfaces) {
    vel += grav;
    vector<Vector2f> corners = getCorners();
    Vector2f velOld = vel;
    int dir = getDir(vel) + 1;// getDir = {> ^ < V}
    for (int i = 0; i < surfaces.size(); i++) {
        for (int j = 0; j < corners.size(); j++) {
            if (surfaces[(dir + i) % 4].collision(corners[j], corners[j] + velOld)) {
                if (!surfaces[i].isOnSurface(corners[j])) {
                    surfaces[i].onSurface(pos, vel);
                }
                this->collision(surfaces[(dir + i) % 4]);
                break;
            }
        }
    }
    pos += vel;
}

void Character::accel(Vector2f in) {
    vel += in;
}

void Character::moveDown(float amount) {
    accel(Vector2f(0, amount));
}

void Character::moveUp(float amount) {
    accel(Vector2f(0, -amount));
}

void Character::moveLeft(float amount) {
    accel(Vector2f(-amount, 0));
}

void Character::moveRight(float amount) {
    accel(Vector2f(amount, 0));
}

void Character::stop() {
    vel = Vector2f(0, 0);
}
