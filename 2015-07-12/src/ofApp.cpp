#include "ofApp.h"

void ofApp::setup(){
    increment = 0.02;
    ofSetWindowShape(500, 500);
    gif.setupPaused(ofGetTimestampString("out/%Y-%m-%d"), 105, 140);
    gif.fadeInOut(17, 4, ofColor::red, 1);
    masker.setup(1);
    transp1.setup("road-transp.png");
    transp1.setTexturePositionY(0.5);
    transp2.setup("road-transp.png");
    transp2.setTexturePositionY(0.5);
}

void ofApp::update(){
    masker.beginLayer(0);
    {
        transp1.incrementTextureScale(-increment);
        transp1.draw();
    }
    masker.endLayer(0);

    masker.beginMask(0);
    {
        transp2.incrementTextureScale(-increment*0.5);
        ofBackground(ofColor::white);
        ofSetColor(ofColor::white);
        transp2.draw();
    }
    masker.endMask(0);
}

void ofApp::draw(){
    gif.begin();
    {
        ofBackground(ofColor::red);
        masker.draw();
    }
    gif.endAndCaptureFrame();
    gif.draw();
    masker.drawOverlay();
}

void ofApp::keyPressed(int key){
    if(key == 'o') {
        masker.toggleOverlay();
    }
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