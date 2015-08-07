#include "ofApp.h"

void ofApp::setup(){
    beginRecordingOnFrame = 20;
    endRecordingAfterFrame = 40;
    increment = 0.01;
    ofSetWindowShape(500, 500);
    gif.setupPaused(ofGetTimestampString("out/%Y-%m-%d"), beginRecordingOnFrame);
    masker.setup(1);
    image.setup("road.png");
    image.setTexturePositionY(0.5);
    transp.setup("road-transp.png");
    goingUp = true;
    position = 0.5;
}

void ofApp::update(){
    masker.beginMask(0);
    {
        alpha = 32;
        if(ofRandom(1) > 0.6) {
            goingUp = !goingUp;
            alpha = 255;
        }

        position += goingUp ? increment : -increment;
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

    masker.beginLayer(0);
    {
        image.setTexturePositionY(1-position);
        image.draw();
    }
    masker.endLayer(0);
}

void ofApp::draw(){
    gif.begin();
    {
        masker.draw();
    }
    gif.endAndCaptureFrame();
    gif.draw();
    masker.drawOverlay();

    if(ofGetFrameNum() == beginRecordingOnFrame) {
        positionOnRecord = position;
    }

    if(ofGetFrameNum() > endRecordingAfterFrame &&
       (position == positionOnRecord - increment ||
        position == positionOnRecord + increment)) {
        gif.renderGif();
    }
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