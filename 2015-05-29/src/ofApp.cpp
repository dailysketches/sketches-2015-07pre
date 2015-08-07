#include "ofApp.h"

/* This draws the animation */
void ofApp::setupAnim() {
    ofEnableSmoothing();
    maskOpacity = 0;
    paused = false;
    maskOpacity = 30;
}

void ofApp::updateAnim() {
    
}

void ofApp::drawAnim() {
    ofEnableAlphaBlending();
    if(ofGetFrameNum() == 0) ofBackground(ofColor::black);
    ofSetColor(0, 0, 0, maskOpacity);
    ofRect(0, 0, width, height);
    
    ofSetColor(ofColor::red);
    for(int i = 0; i < 360; i+=10) {
        for(int j = 0; j < 4; j++) {
            x = ofRandom(0, width);
            y = ofMap(sin(ofGetFrameNum() * 0.06), -1, 1, -20, halfWidth);
            ofLine(x, y, x, y + 50);
        }
        rotateScreen(i);
    }
    
    ofDisableAlphaBlending();
    
    if(ofGetFrameNum() > 96) {
        maskOpacity += 40;
    }
    
    if(maskOpacity > 255) {
        renderGif();
    }
}

void ofApp::rotateScreen(float degrees) {
    ofTranslate(halfWidth, halfHeight, 0);
    ofRotate(degrees);
    ofTranslate(-halfWidth, -halfHeight, 0);
}

/* This handles the setup and GIF rendering, etc */
void ofApp::setup(){
    //Gif render values
    slowMode = false;
    width = 300, height = 300;
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