#pragma once

#include "ofMain.h"
#include "ofxGifEncoder.h"

class ofApp : public ofBaseApp{

public:
    void setup();
    void setupAnim();
    void update();
    void updateAnim();
    void draw();
    void drawAnim();

    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);

    void onGifSaved(string & fileName);
    void exit();
    void captureFrame();

    int width, height, colors, duration;
    int framerate, saveOnFrame;
    string filename;
    bool renderMode;

    ofVideoGrabber vid;
    ofxGifEncoder gifEncoder;
    ofFbo fbo;
    ofPixels pixels;
};
