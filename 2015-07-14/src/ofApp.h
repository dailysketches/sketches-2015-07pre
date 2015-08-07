#pragma once

#include "ofMain.h"
#include "ofxGifEncoderTemplate.h"
#include "ofxTexturePlane.h"
#include "ofxLayerMask.h"

class ofApp : public ofBaseApp{

public:
    void setup();
    void update();
    void draw();

    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    void initTransparencies();
    void initImagePositions();
    void drawTransparency(bool &draw, ofxTexturePlane &image);
    void updateTransparencies();
    void updateTransparency(bool &draw);
    void repositionFace();

    ofxGifEncoderTemplate gif;
    ofxTexturePlane face, glass1, cardTransparency1, cardTransparency2, cardTransparency3, cardTransparency4, cardTransparency5, cardTransparency6;
    ofxLayerMask masker;
    float increment;
    bool drawTransparency1, drawTransparency2, drawTransparency3, drawTransparency4, drawTransparency5, drawTransparency6;
    vector<ofxTexturePlaneOffset> imagePositions;
};
