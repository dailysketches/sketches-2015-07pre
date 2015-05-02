#include "ShapeSystem.h"

//Adapted from:
//http://forum.openframeworks.cc/t/circles-with-holes-or-with-stroke/8173/6
//https://github.com/jasonmcdermott/ofxForums/tree/master/vertexArrayGradientShapes

void ShapeSystem::setup() {
    
}

void ShapeSystem::add(GradientShape &shape) {
    shapes.push_back(&shape);
}

void ShapeSystem::update() {
    for(int i = 0; i < shapes.size(); i++) {
        shapes[i]->update();
    }
}

void ShapeSystem::draw() {
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    
    glEnableClientState(GL_COLOR_ARRAY);
    glEnableClientState(GL_VERTEX_ARRAY);
    for(int i=0;i<shapes.size();i++) {
        shapes[i]->draw();
    }
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
    
    ofDisableAlphaBlending();
}