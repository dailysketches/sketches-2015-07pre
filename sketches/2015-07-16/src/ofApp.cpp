#include "ofApp.h"
/* Begin description
{
    Forced to stay awake
}
End description */

/* Snippet begin */
void ofApp::setup(){
    ofSetWindowShape(1000, 800);
    gif.setup(ofGetTimestampString("out/%Y-%m-%d"), 64, 500, 500);
    masker.setup(500, 500, 1);
    masker.toggleOverlay();
    foil.setup("foil1.png", 500, 500, 2.0, TEXTURE_OFFSET_MIDDLE_CENTER);
    glass.setup("glass1-inverted.png", 500, 500, 1.0, TEXTURE_OFFSET_MIDDLE_CENTER);
}

void ofApp::update(){
    masker.beginLayer(0);
    {
        foil.setTexturePosition(ofRandom(2), ofRandom(2));
        foil.setTextureScale(ofRandom(1.0, 6.0));
        ofSetColor(ofColor::red);
        foil.draw();
    }
    masker.endLayer(0);

    masker.beginMask(0);
    {
        glass.setTexturePosition(ofRandom(2), ofRandom(2));
        glass.setTextureScale(ofRandom(1.0, 6.0));
        ofBackground(ofColor::white);
        if(ofRandom(1) > 0.25) {
            ofSetColor(ofColor(ofColor::white, 120));
            glass.draw();
        }
    }
    masker.endMask(0);
}

void ofApp::draw(){
    gif.begin();
    ofPushStyle();
    {
        ofBackground(ofColor::white);
        ofSetColor(ofColor::white);
        masker.draw();
    }
    ofPopStyle();
    gif.endAndCaptureFrame();
    gif.draw();
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