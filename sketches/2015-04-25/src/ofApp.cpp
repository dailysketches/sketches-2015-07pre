#include "ofApp.h"

/* This draws the animation */
void ofApp::setupAnim() {
    current = 0;
    max = 80;
    for(int i = 0; i < max; i++) {
        glitches.push_back(templateGlitch);
        glitches.at(glitches.size()-1).allocate(width, height);
    }
    ofSetColor(ofColor::white);
}

void ofApp::updateAnim(){

}

void ofApp::drawAnim() {
    if(ofGetFrameNum() % 5 == 0) {
        ofClear(255,255,255);
    } else {
        ofEnableBlendMode(OF_BLENDMODE_MULTIPLY);
        glitches.at(ofGetFrameNum()%max).draw(0, 0);
        ofDisableBlendMode();
    }
}

/* This handles the setup and GIF rendering, etc */
void ofApp::setup(){
    //Gif render values
    renderMode = true;
    width = 400, height = 400;
    duration = 0.75, colors = 256;

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
    saveOnFrame = max;
}

void ofApp::update(){
    updateAnim();
}

void ofApp::draw(){
    fbo.begin();
    drawAnim();
    fbo.end();
    captureFrame();
    ofSetColor(255, 255, 255);
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