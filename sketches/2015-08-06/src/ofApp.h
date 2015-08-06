#pragma once

#include "ofMain.h"
#include "ofxGifEncoderTemplate.h"
#include "ofxLayerMask.h"
#include "ofxTexturePlane.h"

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

    ofxGifEncoderTemplate gif;
    ofxLayerMask masker1, masker2;

    //Anim 1
    ofxTexturePlane tissue, road;
    vector< vector<ofxTexturePlane> > tissues;
    vector<ofxTexturePlane> roads, tissuesLoader;
    int numTissues, numRoads;
    float scale;

    //Anim 2
    vector<ofxTexturePlane> bwbs, wbws;
    ofxTexturePlane bwb, wbw;
    int numLayers;
};
