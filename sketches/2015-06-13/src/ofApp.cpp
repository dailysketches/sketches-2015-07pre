#include "ofApp.h"

/* This draws the animation */
void ofApp::setupAnim() {
    masker.setup(width, height);
    layer1 = masker.newLayer();
    layer2 = masker.newLayer();
    
    ofDisableArbTex();
    offset = ofRandom(3);
    setupImage("foil.png", &img1, &tex1);
    setupImage("glass.png", &img2, &tex2);

    plane.set(width, height);
    plane.setPosition(halfWidth, halfHeight, 0);
    plane.setResolution(2, 2);
    
    glitch = false;
    alpha = 255;
    fadeIn = true;
    fadeOut = false;
}

void ofApp::setupImage(string file, ofImage *img, ofTexture *tex) {
    img->loadImage(file);
    *tex = img->getTextureReference();
    tex->setTextureWrap(GL_MIRRORED_REPEAT, GL_MIRRORED_REPEAT);
}

void ofApp::drawLayer(ofTexture *tex) {
    plane.mapTexCoords(tx0, ty0, tx1, ty1);
    plane.mapTexCoords(tx1, ty1, tx0, ty0);
    tex->bind();
    plane.draw();
    tex->unbind();
}

void ofApp::updateAnim(){
    masker.beginLayer(layer1);
    {
        ofBackground(ofColor::white);
        ofSetColor(ofColor::white);
        tx0 = ofGetFrameNum() * 0.005;
        ty0 = 0;
        tx1 = tx0 - 0.015625;
        ty1 = ty0 - 0.125;
        drawLayer(&tex1);
    }
    masker.endLayer(layer1);
    
    masker.beginMask(layer1);
    {
        ofBackground(ofColor::white);
        ofSetColor(ofColor::black);
        for(int x = 10; x < width; x+=80) {
            for(int y = 10; y < height; y+=80) {
                ofRect(x, y, 60, 60);
            }
        }
    }
    masker.endMask(layer1);

    masker.beginLayer(layer2);
    {
        ofSetColor(ofColor::white);
        tx0 = 0;
        ty0 = ofGetFrameNum() * 0.01;
        tx1 = tx0 - 2;
        ty1 = ty0 - 0.5;
        drawLayer(&tex2);
    }
    masker.endLayer(layer2);
    
    masker.beginMask(layer2);
    {
        masker.drawLayer(layer1);
        ofSetColor(ofColor::white);
        for(int x = 10; x < width; x+=80) {
            for(int y = 10; y < height; y+=80) {
                ofRect(x, y, 60, 60);
            }
        }
    }
    masker.endMask(layer2);
}

void ofApp::drawAnim() {
    ofBackground(ofColor::black);
    
    if(glitch) {
        masker.draw();
        if(ofRandom(1) > 0.4) {
            glitch = !glitch;
        }
    } else {
        masker.drawLayer(layer2);
        if(ofRandom(1) > 0.9) {
            glitch = !glitch;
        }
    }
    
    if(fadeIn) {
        alpha -= 40;
        if(alpha <= 0) fadeIn = false;
    }
    
    if(fadeOut) {
        alpha += 40;
        if(alpha >= 355) {
            renderGif();
        }
    }
    
    ofSetColor(ofColor::black, alpha);
    ofRect(0, 0, width, height);
    
    if(ofGetFrameNum() == 70) {
        fadeOut = true;
    }
}

/* This handles the setup and GIF rendering, etc */
void ofApp::setup(){
    //Gif render values
    slowMode = false;
    paused = false;
    width = 320, height = 320;
    duration = 0.2, colors = 256;
    saveOnFrame = -1;

    filename = ofGetTimestampString("%Y-%m-%d") + ".gif";
    framerate = slowMode ? 5 : 10;
    halfWidth = width * 0.5;
    halfHeight = height * 0.5;

    //Init
    ofSetFrameRate(framerate);
    ofSetWindowShape(width, height);
    gifEncoder.setup(width, height, duration, colors);
    renderingNow = false;
    renderMessage = "";
    
    fbo.allocate(width, height, GL_RGB);
    fbo.begin();
    ofClear(255, 255, 255, 0);
    fbo.end();

    //Begin patch
    setupAnim();
}

void ofApp::update(){
    updateAnim();
}

void ofApp::draw(){
    fbo.begin();
    drawAnim();
    fbo.end();
    
    if(!renderingNow && !paused) {
        captureFrame();
    }
    
    ofSetColor(255, 255, 255, 255);
    fbo.draw(0, 0);
    ofDrawBitmapString(
        "Recording to frame #" +
        ofToString(saveOnFrame) +
        " at " +
        ofToString(ofGetFrameRate()) +
        "fps...\nCurrent frame: " +
        ofToString(ofGetFrameNum()) +
        "\n" + renderMessage,
        20, height - 50);
}

void ofApp::captureFrame() {
    fbo.readToPixels(pixels);
    gifEncoder.addFrame(pixels.getPixels(), width, height,
                        pixels.getBitsPerPixel(), duration);
    
    if(ofGetFrameNum() == saveOnFrame) {
        renderGif();
    }
}

void ofApp::renderGif() {
    if(!renderingNow) {
        renderingNow = true;
        gifEncoder.save(filename);
        renderMessage = "Now rendering";
    }
}

void ofApp::exit(){
    gifEncoder.exit();
}

void ofApp::keyPressed(int key){
    
}

void ofApp::keyReleased(int key){
    
}

void ofApp::mouseMoved(int x, int y ){
    
}

void ofApp::mouseDragged(int x, int y, int button){
    
}

void ofApp::mousePressed(int x, int y, int button){
    
}

void ofApp::mouseReleased(int x, int y, int button){
    
}

void ofApp::windowResized(int w, int h){
    
}

void ofApp::gotMessage(ofMessage msg){
    
}

void ofApp::dragEvent(ofDragInfo dragInfo){
    
}