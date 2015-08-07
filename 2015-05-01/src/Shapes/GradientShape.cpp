#include "GradientShape.h"

//Adapted from:
//http://forum.openframeworks.cc/t/circles-with-holes-or-with-stroke/8173/6
//https://github.com/jasonmcdermott/ofxForums/tree/master/vertexArrayGradientShapes

void GradientShape::setup(int ID_, ofVec3f centre_, int shapeType_, int numSides_, float blur_, float thickness_, float diameter_, ofColor color_) {
    ID = ID_;
    origin.set(centre_);
    position.set(centre_);
    shapeType = shapeType_;
    numSides = numSides_;
    blur = blur_;
    thickness = thickness_;
    diameter = diameter_;
    color.set(color_);
    degreesZ = 0;
}

void GradientShape::update() {
    
}

void GradientShape::draw() {
    if (shapeType == 0) {
        drawGradient(diameter - blur, 0, color.a, 0, numSides);
        drawGradient(diameter, diameter - blur, 0, 0, numSides);
    } else if (shapeType == 1) {
        drawGradient(diameter + thickness - blur, diameter - thickness + blur, color.a, 0, numSides);
        drawGradient(diameter + thickness, diameter + thickness - blur, 0, 0, numSides);
        drawGradient(diameter - thickness, diameter - thickness + blur, 0, 0, numSides);
    } else if (shapeType == 2) {
        drawGradient(diameter - thickness, diameter + thickness, 0, 0, numSides);
        drawGradient(diameter + thickness + thickness * 0.05, diameter + thickness, 0, 0, numSides);
    }
}

void GradientShape::rotateZ(float degrees_) {
    degreesZ = degrees_;
}

void GradientShape::positionZ(float positionZ) {
    position.z = positionZ;
}

void GradientShape::drawGradient(float opaque_, float transp_, float opac_, float blur_, int numSides_) {
    
    ofPushMatrix();
    ofTranslate(position.x, position.y, position.z);
    ofRotateZ(degreesZ);
    
    GLfloat* ver_coords = new GLfloat[ (numSides_+1) * 4];
    GLfloat* ver_cols = new GLfloat[ (numSides_+1) * 8];
    
    float angle;
    float angleSize = 2*PI/numSides_;
    
    
    if (opaque_ < transp_) {
        middleRadius = opaque_ - ((transp_-opaque_)+blur_);
    } else {
        middleRadius = opaque_ - ((transp_-opaque_)+blur_);
    }
    
    middleRadius = (opaque_ + transp_)/2;
    
    for (int i=0; i< (1+numSides_); i++) {
        angle = i* angleSize;
        ver_coords[i*4+0] = (opaque_*cos(angle));
        ver_coords[i*4+1] = (opaque_*sin(angle));
        ver_cols[i*8+0] = color.r;
        ver_cols[i*8+1] = color.g;
        ver_cols[i*8+2] = color.b;
        ver_cols[i*8+3] = opac_;
        ver_coords[i*4+2] = (transp_*cos(angle));
        ver_coords[i*4+3] = (transp_*sin(angle));
        ver_cols[i*8+4] = color.r;
        ver_cols[i*8+5] = color.g;
        ver_cols[i*8+6] = color.b;
        ver_cols[i*8+7] = color.a;
    }
    
    
    glVertexPointer( 2, GL_FLOAT, 0, ver_coords);
    glColorPointer(4, GL_FLOAT, 0, ver_cols);
    glDrawArrays( GL_TRIANGLE_STRIP, 0, ( numSides_ + 1 ) * 2 );
    
    delete[] ver_coords;
    delete[] ver_cols;
    ofPopMatrix();
}