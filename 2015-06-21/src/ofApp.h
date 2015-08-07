#pragma once

#include "ofMain.h"
#include "ofxGifEncoder.h"
#include "ofxTexturePlane.h"
#include <map>

class ofApp : public ofBaseApp{

public:
    void setup();
    void setupAnim();
    void update();
    void updateAnim();
    void draw();
    void drawAnim();
    void renderGif();
    ofxTexturePlaneOffset getRandomOffset();

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
    bool slowMode, renderingNow, paused, fullscreen, showTimeline;

    ofxGifEncoder gifEncoder;
    ofFbo fbo;
    ofPixels pixels;

    ofxTexturePlane image1, image2;
    map<ofxTexturePlaneOffset, float> velocities;
    ofxTexturePlaneOffset lastOffset1, lastOffset2;
};
