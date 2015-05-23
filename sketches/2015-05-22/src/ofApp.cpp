#include "ofApp.h"

/* This draws the animation */
void ofApp::setupAnim() {
    ofEnableSmoothing();
    ofSetLineWidth(4);
    masker.setup(width, height);
    paused = true;
    
    img1.loadImage("chihuly-1.png");
    img2.loadImage("chihuly-2.png");
    numBoxSets = 200;
}

void ofApp::rotateScreen(float degrees) {
    ofTranslate(halfWidth, halfHeight, 0);
    ofRotate(degrees);
    ofTranslate(-halfWidth, -halfHeight, 0);
}

void ofApp::updateAnim(){
    ofEnableAlphaBlending();
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    
    masker.beginBackground();
    img1.draw(0, 0);
    ofSetColor(ofColor(ofColor::black, 40));
    ofRect(0, 0, width, height);
    masker.endBackground();
    
    masker.beginMask();
    ofBackground(ofColor::black);
    for(int i = 0; i < numBoxSets; i++) {
        for(int j = 0; j < width; j+=20) {
            ofSetColor(ofColor::white, ofRandom(10, 35));
            
            ofRect(
                   ofRandom(j - 10, j + 10),
                   ofMap(i, 0, numBoxSets, width * 0.5, width),
                   ofRandom(2, 20),
                   ofRandom(20, 50));
        }
        rotateScreen(10);
    }
    masker.endMask();
    
    masker.beginForeground();
    img2.draw(0, 0);
    ofSetColor(ofColor(ofColor::black, 40));
    ofRect(0, 0, width, height);
    masker.endForeground();
    
    ofDisableBlendMode();
    ofDisableAlphaBlending();
}

void ofApp::drawAnim() {
    masker.draw();
    ofEnableAlphaBlending();
    for(int i = 0; i < numBoxSets; i++) {
        for(int j = 0; j < width; j+=20) {
            if(j % 40 == 0) ofSetColor(ofColor::white, ofRandom(1, 7));
            else ofSetColor(ofColor::black, ofRandom(1, 7));
            
            ofRect(
                ofRandom(j - 10, j + 10),
                ofMap(i, 0, numBoxSets, 30, -30),
                ofRandom(2, 20),
                ofRandom(20, 50));
        }
        rotateScreen(10);
    }
    ofDisableAlphaBlending();
    
    if(ofGetFrameNum() == 50) paused = false;
    if(ofGetFrameNum() == 80) renderGif();
}

/* This handles the setup and GIF rendering, etc */
void ofApp::setup(){
    //Gif render values
    slowMode = false;
    width = 400, height = 400;
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