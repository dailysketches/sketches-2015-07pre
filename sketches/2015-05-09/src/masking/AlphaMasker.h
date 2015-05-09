#pragma once

#include "ofMain.h"

class AlphaMasker {

public:
    void setup(int width, int height);
    void draw();
    
    void beginBackground();
    void endBackground();
    
    void beginMask();
    void endMask();
    
    void beginForeground();
    void endForeground();
    
private:
    void setupFbo(ofFbo &fbo);
    string shader(string name);
    
    int width, height;
    ofShader maskShader;
    ofFbo background, mask, foreground, composite;
};
