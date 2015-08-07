#include "PatternMover.h"

void PatternMover::setup() {
    Mover::setup();
    circle.setup();
}

void PatternMover::update() {
    Mover::update();
    circle.update();
}

void PatternMover::draw() {
    ofSetRectMode(OF_RECTMODE_CENTER);
    ofPushMatrix();
    Mover::draw();
    circle.draw();
    ofPopMatrix();
    ofSetRectMode(OF_RECTMODE_CORNER);
}

void PatternMover::setColor(ofColor _color) {
    circle.setColor(_color);
}

void PatternMover::animateToColor(ofColor _color) {
    circle.animateToColor(_color);
}

void PatternMover::setAnimationTime(float time) {
    circle.setAnimationTime(time);
}

void PatternMover::setSize(int size) {
    circle.setSize(size);
}

float PatternMover::getSize() {
    return circle.getSize();
}

void PatternMover::incrementSize() {
    circle.incrementSize();
}