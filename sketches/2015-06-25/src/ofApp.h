#pragma once

#include "ofMain.h"
#include "ofxGifEncoder.h"
#include "ofxTexturePlane.h"
#include "ofxLayerMask.h"

class ofApp : public ofBaseApp{

public:
    void setup();
    void setupAnim();
    void update();
    void updateAnim();
    void draw();
    void drawAnim();
    void renderGif();
    void randomTriangle(vector<ofPoint> &triangle);
    void drawTriangle(vector<ofPoint> &triangle);
    void drawGradientBackground();
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

    int width, height, halfWidth, halfHeight, doubleWidth, doubleHeight, colors, duration;
    int framerate, saveOnFrame;
    string filename, renderMessage;
    bool slowMode, renderingNow, paused;

    ofxGifEncoder gifEncoder;
    ofFbo fbo;
    ofPixels pixels;

    ofxLayerMask masker;
    ofxTexturePlane image1, image2;
    vector<ofPoint> triangle1, triangle2, triangle3;
    float degrees, rotation, scaleIncrement;
    ofVec2f translateIncrement;
    ofVec2f pointIncrement1, pointIncrement2, pointIncrement3;
};
