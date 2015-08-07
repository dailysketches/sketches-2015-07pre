#pragma once

#include "ofMain.h"
#include "ofxGifEncoder.h"
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
    
    void setupImage(string file, ofImage *img, ofTexture *tex, float *offset);
    void drawLayer(ofTexture *tex);
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
    bool slowMode, renderingNow;
    
    ofxGifEncoder gifEncoder;
    ofFbo fbo;
    ofPixels pixels;
    
    ofxLayerMask masker;
    ofImage img1, img2;
    ofTexture tex1, tex2;
    ofPlanePrimitive plane;
    float tx0, ty0, tx1, ty1, offset1, offset2, frameNum;
    bool fadeIn, fadeOut;
    int alpha;
};
