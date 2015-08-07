#pragma once

//Adapted from:
//http://forum.openframeworks.cc/t/circles-with-holes-or-with-stroke/8173/6
//https://github.com/jasonmcdermott/ofxForums/tree/master/vertexArrayGradientShapes

#include "ofMain.h"

class GradientShape {
    
public:
    void setup(int ID_, ofVec3f centre_, int shapeType_, int numSides_, float blur_, float thickness_, float diameter_, ofColor color_);
    void update();
    void draw();
    void rotateZ(float degrees_);
    void positionZ(float positionZ);
    
private:
    void drawGradient(float opaque_, float transp_, float opac_, float blur_, int numSides_);
    
    ofVec3f position, origin;
    int ID;
    float middleRadius, degreesZ;
    ofFloatColor color;
    
    int shapeType, numSides;
    float blur, thickness, diameter;
};