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
    void setupTransparencies();
    void setupCardboards();
    void setupIncrements();

    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);

    ofxGifEncoderTemplate gif;
    vector<ofxTexturePlane> transparencies;
    vector<ofxTexturePlane> cardboards;
    vector<float> increments;
    float incrementMultiplier;
    ofxTexturePlane image;
    ofxTexturePlane glass;
    ofxTexturePlane circle;
    ofxLayerMask masker;
    int numLayers;
};
