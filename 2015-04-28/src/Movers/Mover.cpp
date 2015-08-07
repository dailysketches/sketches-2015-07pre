#include "Mover.h"

void Mover::setup() {
    topspeed = 1000;
    setLocation(ofGetWidth() * 0.5, ofGetHeight() * 0.5);
    setMass(1);
}

void Mover::update() {
    velocity += acceleration;
    velocity.limit(topspeed);
    location += velocity;
    checkEdges();
    
    acceleration *= 0; //reset, so that forces are applied fresh each frame
}

void Mover::draw() {
    ofTranslate(location.x, location.y);
}

void Mover::applyForce(ofVec2f force) {
    //Newton's second law:
    // Net force = mass x acceleration
    // The 'net' is why it's += and not just plain equals
    acceleration += force / mass;
}

void Mover::setTopSpeed(int speed) {
    topspeed = speed;
}

void Mover::setLocation(float x, float y) {
    location.set(x, y);
}

void Mover::setMass(float _mass) {
    mass = _mass;
}

void Mover::setAcceleration(float x, float y) {
    //Don't use this unless you want to override forces
    acceleration.set(x, y);
}

void Mover::accelerateTowards(ofVec2f target, float multiplier) {
    //Don't use this unless you want to override forces
    acceleration = target - location;
    acceleration.normalize();
    acceleration *= multiplier;
}

float Mover::getX() {
    return location.x;
}

float Mover::getY() {
    return location.y;
}

void Mover::checkEdges() {
    if (location.x > ofGetWidth()) {
        location.x = ofGetWidth();
        velocity.x *= -1;
    } else if (location.x < 0) {
        location.x = 0;
        velocity.x *= -1;
    }
    
    if (location.y > ofGetHeight()) {
        location.y = ofGetHeight();
        velocity.y *= -1;
    } else if (location.y < 0) {
        location.y = 0;
        velocity.y *= -1;
    }
}