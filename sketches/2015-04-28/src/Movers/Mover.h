#pragma once

#include "ofMain.h"

class Mover {
    
public:
    void setup();
    void update();
    void draw();
    
    void applyForce(ofVec2f force);
    void setTopSpeed(int speed);
    void setLocation(float x, float y);
    void setMass(float _mass);
    void setAcceleration(float x, float y);
    void accelerateTowards(ofVec2f target, float multiplier);
    float getX();
    float getY();
    
protected:
    void checkEdges();
    
    ofVec2f location, velocity, acceleration;
    float mass;
    int topspeed;
};