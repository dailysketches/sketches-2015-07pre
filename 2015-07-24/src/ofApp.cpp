#include "ofApp.h"
/* Begin description
{
    Based on the same technique from 2015-07-13
}
End description */

/* Snippet begin */
void ofApp::setup(){
    increment = 0.02;
    numLayers = 3;
    filename = "condensation-transp2.png";

    ofSetWindowShape(500, 500);
    gif.setupPaused(ofGetTimestampString("out/%Y-%m-%d"), 240, 280);
    gif.fadeInOut(8, 2, ofColor::white, 1);

    masker.setup(3);
    plane.setup(filename);
    plane.setTexturePositionY(0.5);
    for(int i = 0; i < numLayers; i++) {
        layers.push_back(plane);
        masks.push_back(plane);
    }
}

void ofApp::update(){
    for(int i = 0; i < numLayers; i++) {
        masker.beginLayer(i);
        {
            if(i == 0) {
                layers.at(i).incrementTextureOffsetY(-increment);
                layers.at(i).incrementTextureScale(-increment);
            }
            if(i == 1) {
                layers.at(i).incrementTextureOffsetY(increment);
                layers.at(i).incrementTextureScale(increment);
            }
            if(i == 2) {
                layers.at(i).incrementTextureOffsetX(increment);
                layers.at(i).incrementTextureScale(-increment);
            }
            layers.at(i).draw();
        }
        masker.endLayer(i);

        masker.beginMask(i);
        {
            ofBackground(ofColor::white);
            ofSetColor(ofColor::white);
            if(i == 0) {
                masks.at(i).incrementTextureOffsetY(-increment);
                masks.at(i).incrementTextureScale(-increment*0.5);
            }
            if(i == 1) {
                masks.at(i).incrementTextureOffsetY(increment);
                masks.at(i).incrementTextureScale(increment*0.5);
            }
            if(i == 2) {
                masks.at(i).incrementTextureOffsetX(-increment);
                masks.at(i).incrementTextureScale(increment*0.5);
            }
            masks.at(i).draw();
        }
        masker.endMask(i);
    }
}

void ofApp::draw(){
    gif.begin();
    {
        ofBackground(ofColor::white);
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