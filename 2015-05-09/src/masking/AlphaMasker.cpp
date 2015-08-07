#include "AlphaMasker.h"

void AlphaMasker::setup(int _width, int _height) {
    width = _width;
    height = _height;
    maskShader.load(shader("alphaMask"));
    
    setupFbo(background);
    setupFbo(mask);
    setupFbo(foreground);
    setupFbo(composite);
}

void AlphaMasker::draw() {
    composite.begin();
    ofClear(0, 0, 0, 0);
    maskShader.begin();
    maskShader.setUniformTexture("maskTex", mask.getTextureReference(), 1);
    foreground.draw(0, 0);
    maskShader.end();
    composite.end();
    
    background.draw(0, 0);
    composite.draw(0, 0);
}

void AlphaMasker::beginBackground() {
    background.begin();
}

void AlphaMasker::endBackground() {
    background.end();
}

void AlphaMasker::beginMask() {
    mask.begin();
}

void AlphaMasker::endMask() {
    mask.end();
}

void AlphaMasker::beginForeground() {
    foreground.begin();
}

void AlphaMasker::endForeground() {
    foreground.end();
}

void AlphaMasker::setupFbo(ofFbo &fbo) {
    fbo.allocate(width, height, GL_RGBA);
    fbo.begin();
    ofClear(0, 0, 0, 255);
    fbo.end();
}

string AlphaMasker::shader(string name) {
    string shaderPath = "../../src/masking/shader/" + name;
#ifdef TARGET_OPENGLES
    return shaderPath + "_ES2";
#else
    if(ofIsGLProgrammableRenderer()){
        return shaderPath + "_GL3";
    }else{
        return shaderPath + "_GL2";
    }
#endif
}