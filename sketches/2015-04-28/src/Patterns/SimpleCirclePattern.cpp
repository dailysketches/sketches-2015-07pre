#include "SimpleCirclePattern.h"

void SimpleCirclePattern::setup() {
    ofSetCircleResolution(40);
    ofEnableSmoothing();
    setAnimationTime(0.5);
    color.setCurve(SWIFT_GOOGLE);
}

void SimpleCirclePattern::update() {
    //float dt = 1.0f/ofGetFrameRate(); -- for real-time animation
    float dt = 0.03; //for rendering mode
    color.update(dt);
    size.update(dt);
}

void SimpleCirclePattern::draw() {
    ofSetColor(color.getCurrentColor());
    ofCircle(0, 0, size);
}

void SimpleCirclePattern::setColor(ofColor _color) {
    color.setColor(_color);
}

void SimpleCirclePattern::setAnimationTime(float time) {
    color.setDuration(time);
    size.setDuration(time);
}

void SimpleCirclePattern::animateToColor(ofColor _color) {
    color.animateTo(_color);
}

void SimpleCirclePattern::setSize(int _size) {
    size.reset(_size);
}

float SimpleCirclePattern::getSize() {
    return size.getCurrentValue();
}

void SimpleCirclePattern::incrementSize() {
    size.animateToIfFinished(size.getCurrentValue() * 2);
}