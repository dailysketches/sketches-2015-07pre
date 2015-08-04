#include "ofApp.h"
/* Begin description
{
    You'll never have an answer.
}
End description */

/* Snippet begin */
void ofApp::setup(){
    ofSetWindowShape(1000, 800);
    gif.setup(ofGetTimestampString("out/%Y-%m-%d"), 80, 500, 500);
    masker.setup(500, 500, 3);
    masker.toggleOverlay();
    foil.setup("foil1.png", 500, 500, 6.0, TEXTURE_OFFSET_MIDDLE_CENTER);
    glass.setup("glass1-inverted.png", 500, 500, 4.0, TEXTURE_OFFSET_MIDDLE_CENTER);
    numFramesSince = 0;
}

void ofApp::update(){
    foil.incrementTextureOffsetY(0.05);
    alpha = ofMap(sin(ofGetFrameNum() * 0.25), -1, 1, 128, 200);
    
    masker.beginLayer(0);
    {
        gif.rotateAroundCenter(90);
        ofSetColor(ofColor(ofColor::white, ofGetFrameNum() % 3 == 0 ? alpha : 0));
        foil.draw();
    }
    masker.endLayer(0);
    
    masker.beginMask(0);
    {
        ofBackground(ofColor::white);
    }
    masker.endMask(0);
    
    masker.beginLayer(1);
    {
        ofBackground(ofColor::red);
    }
    masker.endLayer(1);
    
    masker.beginMask(1);
    {
        gif.rotateAroundCenter(90);
        if(ofRandom(1) > 0.93 && numFramesSince > 8) {
            ofSetColor(ofColor(ofColor::white, 255 - alpha));
            glass.setTextureOffset(ofRandom(2), ofRandom(2));
            glass.draw();
            numFramesSince = 0;
        } else {
            numFramesSince++;
            ofSetColor(ofColor(ofColor::black, 96));
            ofRect(0, 0, gif.width, gif.height);
        }
        
        gif.rotateAroundCenter(-90);
        ofSetColor(ofColor(ofColor::black, 255));
        ofRect(50, 200, 170, 90);
    }
    masker.endMask(1);

    masker.beginLayer(2);
    {
        ofSetColor(ofColor(ofColor::white, 128));
        ofRect(50, 200, 170, 90);
        gif.rotateAroundCenter(180);
        ofSetColor(ofColor(ofColor::white, alpha));
        foil.draw();
    }
    masker.endLayer(2);
    
    masker.beginMask(2);
    {
        ofBackground(ofColor::black);
        ofSetColor(ofColor(ofColor::white, 255));
        ofRect(50, 200, 170, 90);
    }
    masker.endMask(2);
}

void ofApp::draw(){
    gif.begin();
    ofPushStyle();
    {
        ofEnableAlphaBlending();
        ofBackground(ofColor::black);
        ofSetColor(ofColor::white);
        masker.draw();
    }
    ofPopStyle();
    gif.endCaptureDraw();
    masker.drawOverlay();
}
/* Snippet end */

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