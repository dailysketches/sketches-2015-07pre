#pragma once

#include "ofMain.h"
#include "ofxTimeline.h"
#include "ofxAudioUnit.h"
#include "ofxAudioUnitManager.h"
#include "ofxAudioUnitManagerUtils.h"
#include "TALNoiseMaker.h"

class ofApp : public ofBaseApp{
    
public:
    void setup();
    void setupAudioUnits();
    void setupTimeline();
    void update();
    void draw();
    void togglePlaying();
    void exit();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    ofxAudioUnitManager manager;
    ofxAudioUnitManagerUtils utils;
    AudioUnitChain chain1, chain2;
    TALNoiseMaker noiseMaker1, noiseMaker2;

    bool playing;

    ofxTimeline timeline;
    void bang(ofxTLBangEventArgs &args);
};
