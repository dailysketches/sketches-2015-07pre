#include "ofApp.h"

void ofApp::setup(){
    width = 500, height = 500;
    
    ofSetWindowShape(width, height);
    vid.initGrabber(width, height);
    
    gifEncoder.setup(width, height, .25, 256);
    
    ofBackground(50, 40, 50);
    ofSetFrameRate(5);
}

void ofApp::update(){
    if(ofGetFrameNum() == 20) {
        gifEncoder.save("test.gif");
    }
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
    gifEncoder.addFrame(
                        vid.getPixels(),
                        width,
                        height,
                        vid.getPixelsRef().getBitsPerPixel(),
                        .1f
                        );
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