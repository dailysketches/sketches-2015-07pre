#include "ofApp.h"

void ofApp::setup(){
    //Gif render values
    renderMode = true;
    width = 500, height = 500;
    duration = .03, colors = 256;
    filename = "render.gif";
    framerate = renderMode ? 5 : 60;
    saveOnFrame = 20;
    
    //Init
    ofSetFrameRate(framerate);
    ofSetWindowShape(width, height);
    gifEncoder.setup(width, height, duration, colors);
    
    //Begin patch
    ofBackground(50, 40, 50);
    vid.initGrabber(width, height);
}

void ofApp::update(){
    vid.update();
}

void ofApp::draw(){
    vid.draw(0, 0);
    if(ofGetFrameNum() % 2 == 0) {
        ofDrawBitmapString(ofToString(ofGetFrameNum()), 10, 20);
    }
    captureFrame();
}

void ofApp::captureFrame() {

    gifEncoder.addFrame(vid.getPixels(), width, height,
                        vid.getPixelsRef().getBitsPerPixel(),
                        duration);
    
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