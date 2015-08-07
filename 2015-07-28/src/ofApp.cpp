#include "ofApp.h"
/* Begin description
{
    Easing back and forth
}
End description */

/* Snippet begin */
void ofApp::setup(){
    increment = 0.01;
    numLayers = 3;
    filename = "leaf-transp2.png";

    ofSetWindowShape(500, 500);
    gif.setupPaused(ofGetTimestampString("out/%Y-%m-%d"), 12, 60);

    masker.setup(numLayers);
    plane.setup(filename);
    for(int i = 0; i < numLayers; i++) {
        layers.push_back(plane);
        masks.push_back(plane);
    }
    reset();
}

void ofApp::reset() {
    offsetIncrements.clear();
    scaleIncrements.clear();

    for(int i = 0; i < numLayers; i++) {
        layers.at(i).setTextureScale(ofRandom(0.1, 1.5));
        layers.at(i).setTexturePosition(ofRandom(2), ofRandom(2));
        masks.at(i).setTextureScale(ofRandom(0.1, 1.5));
        masks.at(i).setTexturePosition(ofRandom(2), ofRandom(2));
        offsetIncrements.push_back(ofVec2f(ofRandom(-increment, increment), ofRandom(-increment, increment)));
        scaleIncrements.push_back(ofRandom(-increment*20, increment*20));
    }
}

void ofApp::update(){
    if(ofGetFrameNum() % 12 == 0) {
        reset();
    }
    for(int i = 0; i < numLayers; i++) {
        masker.beginLayer(i);
        {
            if(ofGetFrameNum() % 3 == 0 && i == 0) {
                ofBackground(ofColor(ofColor::white, 64));
            }
            if(ofGetFrameNum() % 12 == 0) {
                ofBackground(ofColor(ofColor::white, 128));
            }
            layers.at(i).incrementTextureOffset(offsetIncrements.at(i));
            layers.at(i).incrementTextureScale(scaleIncrements.at(i));
            layers.at(i).draw();
        }
        masker.endLayer(i);

        masker.beginMask(i);
        {
            ofBackground(ofColor::white);
            masks.at(i).incrementTextureOffset(-offsetIncrements.at(i));
            masks.at(i).incrementTextureScale(-scaleIncrements.at(i));
            masks.at(i).draw();
        }
        masker.endMask(i);
    }
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