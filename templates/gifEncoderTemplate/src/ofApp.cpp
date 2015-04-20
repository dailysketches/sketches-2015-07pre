#include "ofApp.h"

/* This draws the animation */
void ofApp::setupAnim() {
    vid.initGrabber(width, height);
}

void ofApp::updateAnim(){
    vid.update();
}

void ofApp::drawAnim() {
    vid.draw(0, 0);
    if(ofGetFrameNum() % 2 == 0) {
        ofDrawBitmapString(ofToString(ofGetFrameNum()), 10, 20);
    }
}

/* This handles the setup and GIF rendering, etc */
void ofApp::setup(){
    //Gif render values
    renderMode = true;
    width = 500, height = 500;
    duration = .03, colors = 256;
    saveOnFrame = 20;

    filename = "render.gif";
    framerate = renderMode ? 5 : 60;
    
    //Init
    ofSetFrameRate(framerate);
    ofSetWindowShape(width, height);
    gifEncoder.setup(width, height, duration, colors);
    
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
}

void ofApp::captureFrame() {
    fbo.readToPixels(pixels);
    gifEncoder.addFrame(pixels.getPixels(), width, height,
                        pixels.getBitsPerPixel(), duration);
    
    if(ofGetFrameNum() == saveOnFrame) {
        gifEncoder.save(filename);
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