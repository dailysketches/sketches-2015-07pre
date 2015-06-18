#pragma once

#include "ofMain.h"
#include "ofxGifEncoder.h"
#include "ofxTexturePlane.h"
#include "ofxShapeSystem.h"
#include "ofxShape.h"

class ofApp : public ofBaseApp{

public:
    void setup();
    void setupAnim();
    void update();
    void updateAnim();
    void draw();
    void drawAnim();
    void renderGif();
    void rotateScreen(float degrees);
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);

    void exit();
    void captureFrame();

    int width, height, halfWidth, halfHeight, colors, duration;
    int framerate, saveOnFrame;
    string filename, renderMessage;
    bool slowMode, renderingNow, paused;

    ofxGifEncoder gifEncoder;
    ofFbo fbo;
    ofPixels pixels;
    
    vector<ofxTexturePlane> images;
    vector<ofColor> imgColors;
    ofxTexturePlane image;
    float numImages, highestIndex;

    ofxShapeSystem system;
    ofxShape shape;
};
