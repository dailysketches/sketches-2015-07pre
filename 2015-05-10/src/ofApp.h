#pragma once

#include "ofMain.h"
#include "ofxGifEncoder.h"
#include "ofxShape.h"
#include "ofxShapeSystem.h"
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
    void push(vector<ofxShape> *shapes, vector<ofxShapeSystem> *systems);
    void draw(vector<ofxShapeSystem> *systems);
    
    void setupBackground();
    void setupMask();
    void setupForeground();

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

    int width, height, colors, duration;
    int framerate, saveOnFrame;
    string filename, renderMessage;
    bool slowMode, renderingNow;

    ofxGifEncoder gifEncoder;
    ofFbo fbo;
    ofPixels pixels;
    
    vector <ofxShape> backgroundShapes, maskShapes, foregroundShapes;
    vector <ofxShapeSystem> backgroundSystems, maskSystems, foregroundSystems;
    ofxLayerMask masker;
    
    int halfWidth, halfHeight;
    float diameter, position;
};
