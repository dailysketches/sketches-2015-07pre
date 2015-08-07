#pragma once

#include "ofMain.h"
#include "ofxGifEncoder.h"
#include "ofxLayerMask.h"
#include "ofxTexturePlane.h"

class ofApp : public ofBaseApp{

public:
    void setup();
    void setupAnim();
    void update();
    void updateAnim();
    void draw();
    void drawAnim();
    void renderGif();

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
    int framerate, saveOnFrame, numFrames;
    string filename, renderMessage;
    bool slowMode, renderingNow, paused, fullscreen;

    ofxGifEncoder gifEncoder;
    ofFbo fbo;
    ofPixels pixels;

    ofxTexturePlane leafDiagonal, leafStar, leafVertical;
    ofxTexturePlane mask1, mask2;
    vector<ofxTexturePlane*> planes, masks;
    ofxLayerMask masker;
    int numLayers;
    vector<int> layerIds;
    float alpha, increment, maskIncrement, scale1, scale2;
};
