#pragma once

#include "Mover.h"
#include "SimpleCirclePattern.h"
#include "ofxAnimatableOfColor.h"

class PatternMover : public Mover {
    
public:
    void setup();
    void update();
    void draw();
    
    void setColor(ofColor _color);
    void animateToColor(ofColor _color);
    void setAnimationTime(float time);
    void setSize(int size);
    float getSize();
    void incrementSize();
    
protected:
    SimpleCirclePattern circle;
};