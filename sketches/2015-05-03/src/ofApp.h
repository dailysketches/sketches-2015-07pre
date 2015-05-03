#pragma once

#include "ofMain.h"
#include "ofxGifEncoder.h"
#include "ShapeSystem.h"

class ofApp : public ofBaseApp{
    
public:
    void setup();
    void setupAnim();
    void update();
    void updateAnim();
    void draw();
    void drawAnim();
    void renderGif();
    void drawArc(float radius, float angleEnd);
    
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
    bool renderMode, renderingNow;
    
    ofxGifEncoder gifEncoder;
    ofFbo fbo;
    ofPixels pixels;
    
    ShapeSystem shapeSystem;
    ofEasyCam camera;
    ofColor color;
    ofVec3f center;
    
    vector<GradientShape> rings;
    int numShapes;
    float endpoint, firstEndpoint, lastEndpoint, rotation, alpha;
};
