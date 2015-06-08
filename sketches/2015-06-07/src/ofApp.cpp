#include "ofApp.h"

/* This draws the animation */
void ofApp::setupAnim() {
    size = 60;
    margin = width - size;
    halfMargin = margin * 0.5;
}

void ofApp::updateAnim(){
    
}

void ofApp::drawAnim() {
    ofBackground(ofColor::white);
    
    ofSetColor(ofColor::black, 10);
    for(int i = 0; i < 1400; i++) {
        x = width * 0.5 - size * 0.5 + (ofRandom(margin) - halfMargin);
        y = floor(ofRandom(height/size)) * size;
        ofRect(x, y, size, size);
    }
    
    ofSetColor(ofColor::white, 64);
    for(int i = 0; i < height/size; i++) {
        ofRect(halfMargin, i * size + size * 0.5, width - margin, 4);
    }
    
    ofSetColor(ofColor::white, 64);
    for(int i = -height; i < height; i++) {
        ofRect(halfMargin, (i * size * 0.5) + ofGetFrameNum(), width - margin, 4);
        ofRect(halfMargin, (i * size * 0.5) - ofGetFrameNum(), width - margin, 4);
    }
    
    if(ofGetFrameNum() == 30) {
        renderGif();
    }
}

/* This handles the setup and GIF rendering, etc */
void ofApp::setup(){
    //Gif render values
    slowMode = false;
    paused = false;
    width = 160, height = 360;
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