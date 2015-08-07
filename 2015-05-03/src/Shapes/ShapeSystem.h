#pragma once

#include "GradientShape.h"

//Adapted from:
//http://forum.openframeworks.cc/t/circles-with-holes-or-with-stroke/8173/6
//https://github.com/jasonmcdermott/ofxForums/tree/master/vertexArrayGradientShapes

#include "ofMain.h"

class ShapeSystem {
    
public:
    void setup();
    void add(GradientShape &shape);
    void update();
    void draw();
    
private:
    vector < GradientShape* > shapes;
    ofFloatColor bgColor;
    
    int shapeType, numSides;
    float blur, thickness, diameter;
};