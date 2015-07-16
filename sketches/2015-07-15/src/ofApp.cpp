#include "ofApp.h"
/* Begin description
{
   Red, red, red
}
End description */

/* Snippet begin */
void ofApp::setup(){
    ofSetWindowShape(1000, 800);
    gif.setup(ofGetTimestampString("out/%Y-%m-%d"), 120, 500, 500);
    gif.fadeInOut(2, 4, ofColor::white);
    numLayers = 7;
    masker.setup(500, 500, numLayers + 1);
    masker.toggleOverlay();
    setupTransparencies();
    setupCardboards();
    setupIncrements();
    glass.setup("glass1.png", 500, 500, 2.0, TEXTURE_OFFSET_MIDDLE_CENTER);
    circle.setup("circle-feather3.png", 500, 500, 1.0, TEXTURE_OFFSET_MIDDLE_CENTER);
}

void ofApp::setupTransparencies() {
    image.setup("card-invert.png", 500, 500, 1.5, TEXTURE_OFFSET_MIDDLE_LEFT);
    transparencies.push_back(image);
    image.setup("card-invert.png", 500, 500, 0.75, TEXTURE_OFFSET_BOTTOM_RIGHT);
    transparencies.push_back(image);
    image.setup("card-invert.png", 500, 500, 1.25, TEXTURE_OFFSET_TOP_CENTER);
    transparencies.push_back(image);
    image.setup("card-invert.png", 500, 500, 1.5, TEXTURE_OFFSET_BOTTOM_LEFT);
    transparencies.push_back(image);
    image.setup("card-invert.png", 500, 500, 0.75, TEXTURE_OFFSET_TOP_RIGHT);
    transparencies.push_back(image);
    image.setup("card-invert.png", 500, 500, 1.25, TEXTURE_OFFSET_MIDDLE_CENTER);
    transparencies.push_back(image);
}

void ofApp::setupCardboards() {
    image.setup("cardboard.png", 500, 500, 2.0, TEXTURE_OFFSET_MIDDLE_LEFT);
    cardboards.push_back(image);
    image.setup("cardboard.png", 500, 500, 2.0, TEXTURE_OFFSET_BOTTOM_RIGHT);
    cardboards.push_back(image);
    image.setup("cardboard.png", 500, 500, 2.0, TEXTURE_OFFSET_TOP_CENTER);
    cardboards.push_back(image);
    image.setup("cardboard.png", 500, 500, 2.0, TEXTURE_OFFSET_BOTTOM_LEFT);
    cardboards.push_back(image);
    image.setup("cardboard.png", 500, 500, 2.0, TEXTURE_OFFSET_TOP_RIGHT);
    cardboards.push_back(image);
    image.setup("cardboard.png", 500, 500, 2.0, TEXTURE_OFFSET_MIDDLE_CENTER);
    cardboards.push_back(image);
}

void ofApp::setupIncrements() {
    incrementMultiplier = 0.0125;
    for(int i = 1; i <= numLayers / 2; i++) {
        increments.push_back(-incrementMultiplier * i);
        increments.push_back(incrementMultiplier * i);
    }
}

void ofApp::update(){
    glass.setTexturePosition(ofRandom(2), ofRandom(2));
    glass.setTextureScale(ofRandom(1.0, 6.0));
    masker.beginLayer(0);
    {
        ofSetColor(ofColor::red);
        glass.draw();
        ofSetColor(ofColor::white);
    }
    masker.endLayer(0);

    masker.beginMask(0);
    {
        circle.draw();
    }
    masker.endMask(0);

    for(int i = 1; i < numLayers; i++) {
        masker.beginLayer(i);
        ofPushStyle();
        {
            ofSetColor(ofColor(i * 20 + 140, 140, i * 20 + 140));
            ofSetColor(ofColor::red);
            cardboards.at(i-1).incrementTextureOffsetY(i % 2 == 0 ? -0.05 : 0.05);
            cardboards.at(i-1 % 2).draw();
        }
        ofPopStyle();
        masker.endLayer(i);
        
        masker.beginMask(i);
        ofPushStyle();
        {
            transparencies.at(i - 1).incrementTextureOffsetY(increments.at(i - 1) * ((i % 2 == 0) ? sin(ofGetFrameNum() * 0.005) : cos(ofGetFrameNum() * 0.005)));
            transparencies.at(i - 1).incrementTextureOffsetX(i % 2 == 0 ? -0.018 : 0.018);
            transparencies.at(i - 1).draw();
        }
        ofPopStyle();
        masker.endMask(i);
    }
    
    masker.beginLayer();
    {
        ofSetColor(ofColor::white);
        masker.drawLayers(0, numLayers - 1);
    }
    masker.endLayer();
    
    masker.beginMask();
    {
        ofSetColor(ofColor::white);
        circle.draw();
    }
    masker.endMask();
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