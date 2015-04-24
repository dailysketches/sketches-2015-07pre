#include "ofApp.h"

/* This draws the animation */
void ofApp::setupAnim() {
    ofSetCircleResolution(100);
    ofNoFill();
    ofEnableSmoothing();
    multiplier = 5;
    switchDirection = false;
}

void ofApp::updateAnim(){
    if(switchDirection) {
        multiplier += 0.2;
    } else {
        multiplier -= 0.2;
    }
    
    if(multiplier <= 0.2 || multiplier >= 10) {
        switchDirection = !switchDirection;
        if(!switchDirection) saveNow = true;
    }
}

void ofApp::drawAnim() {
    ofBackground(0, 0, 0);
    for(int i = 1; i <= 100; i++) {
        ofCircle(width * 0.5, height * 0.5, i * multiplier);
        ofCircle(width * 0.5, height * 0.5, i * (15 - multiplier));
    }
    if(!renderMode) {
        ofDrawBitmapString(ofToString(multiplier), 20, 20);
    }
}

/* This handles the setup and GIF rendering, etc */
void ofApp::setup(){
    //Gif render values
    renderMode = true;
    width = 500, height = 500;
    duration = .02, colors = 256;
    saveOnFrame = 46;
    saveNow = false;

    filename = ofGetTimestampString("%Y-%m-%d") + ".gif";
    framerate = renderMode ? 5 : 50;
    
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
    
    if(ofGetFrameNum() == saveOnFrame || saveNow) {
        gifEncoder.save(filename);
        nowSaved = "Now saved!";
        ofSleepMillis(100000);
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