#include "ofApp.h"

/* This draws the animation */
void ofApp::setupAnim() {
    increment = 10;
    max = 400;
    pos = 0;
}

void ofApp::updateAnim(){
    pos += increment;
    if(pos > max * 2) {
        pos = 0;
        vertical = !vertical;
    }
}

void ofApp::drawAnim() {
    ofBackground(0, 0, 0);
    for(int i = 1; i <= max; i++) {
        if(vertical) drawVerticalLines(i);
        else drawHorizontalLines(i);
    }
}

void ofApp::drawVerticalLines(int x) {
    if(x % 2 == 0) {
        ofLine(x, pos - max, x, pos);
    } else {
        ofLine(x, height - pos, x, max * 2 - pos);
    }
}

void ofApp::drawHorizontalLines(int y) {
    if(y % 2 == 0) {
        ofLine(pos - max, y, pos, y);
    } else {
        ofLine(height - pos, y, max * 2 - pos, y);
    }
}

/* This handles the setup and GIF rendering, etc */
void ofApp::setup(){
    //Gif render values
    renderMode = true;
    width = 400, height = 400;
    duration = 0.02, colors = 2;
    saveOnFrame = 154;

    filename = ofGetTimestampString("%Y-%m-%d") + ".gif";
    framerate = renderMode ? 5 : 60;
    
    //Init
    ofSetFrameRate(framerate);
    ofSetWindowShape(width, height);
    gifEncoder.setup(width, height, duration, colors);
    nowSaved = "";
    
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
    captureFrame();
    fbo.draw(0, 0);
    ofDrawBitmapString(
        "Recording to frame #" +
        ofToString(saveOnFrame) +
        " at " +
        ofToString(framerate) +
        "fps...\nCurrent frame: " +
        ofToString(ofGetFrameNum()) +
        "\n" + nowSaved,
        20, height - 50);
}

void ofApp::captureFrame() {
    fbo.readToPixels(pixels);
    gifEncoder.addFrame(pixels.getPixels(), width, height,
                        pixels.getBitsPerPixel(), duration);
    
    if(ofGetFrameNum() == saveOnFrame) {
        gifEncoder.save(filename);
        nowSaved = "Now saved!";
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