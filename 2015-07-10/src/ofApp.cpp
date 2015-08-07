#include "ofApp.h"

void ofApp::setup(){
    ofSetWindowShape(500, 500);
    gif.setupPaused(ofGetTimestampString("out/%Y-%m-%d"), 40, 80);
    masker.setup(1);
    image.setup("road.png");
    image.setTexturePositionY(0.5);
    transp.setup("road-transp.png");
    goingUp = true;
    directionChanged = true;
    position = 0.5;
}

void ofApp::update(){
    masker.beginLayer(0);
    {
        image.incrementTextureOffsetY(0.05);
        image.draw();
    }
    masker.endLayer(0);
    
    masker.beginMask(0);
    {
        if(ofRandom(1) > 0.6) {
            goingUp = !goingUp;
            directionChanged = true;
        }
        
        if(directionChanged) {
            alpha = 255;
            directionChanged = false;
        } else {
            alpha = 32;
        }
        position += goingUp ? 0.01 : -0.01;
        transp.setTexturePositionY(position);
        
        ofSetColor(ofColor::white, alpha);
        if(ofGetFrameNum() == 0) {
            ofSetColor(ofColor::black);
        }
        ofRect(0, 0, gif.width, gif.height);
        ofSetColor(ofColor::white);
        transp.draw();
    }
    masker.endMask(0);
}

void ofApp::draw(){
    gif.begin();
    {
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