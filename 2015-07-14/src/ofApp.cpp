#include "ofApp.h"

void ofApp::setup(){
    increment = 0.001;
    ofSetWindowShape(500, 500);
    gif.setup(ofGetTimestampString("out/%Y-%m-%d"), 56);
    masker.setup(2);
    face.setup("face.png", 2.0, TEXTURE_OFFSET_MIDDLE_CENTER);
    glass1.setup("glass1.png", 3.0, TEXTURE_OFFSET_MIDDLE_CENTER);
    cardTransparency1.setup("card-transp-bg.png", 1.9, TEXTURE_OFFSET_MIDDLE_LEFT);
    cardTransparency2.setup("card-transp-bg.png", 2.6, TEXTURE_OFFSET_BOTTOM_RIGHT);
    cardTransparency3.setup("card-transp-bg.png", 3.3, TEXTURE_OFFSET_TOP_CENTER);
    cardTransparency4.setup("card-transp-bg.png", 3.9, TEXTURE_OFFSET_MIDDLE_LEFT);
    cardTransparency5.setup("card-transp-bg.png", 4.9, TEXTURE_OFFSET_BOTTOM_RIGHT);
    cardTransparency6.setup("card-transp-bg.png", 5.6, TEXTURE_OFFSET_TOP_CENTER);
    initTransparencies();
    initImagePositions();
}

void ofApp::initTransparencies() {
    drawTransparency1 = ofRandom(1) > 0.5;
    drawTransparency2 = ofRandom(1) > 0.5;
    drawTransparency3 = ofRandom(1) > 0.5;
    drawTransparency4 = ofRandom(1) > 0.5;
    drawTransparency5 = ofRandom(1) > 0.5;
    drawTransparency6 = ofRandom(1) > 0.5;
}

void ofApp::initImagePositions() {
    imagePositions.push_back(TEXTURE_OFFSET_TOP_LEFT);
    imagePositions.push_back(TEXTURE_OFFSET_TOP_CENTER);
    imagePositions.push_back(TEXTURE_OFFSET_TOP_RIGHT);
    imagePositions.push_back(TEXTURE_OFFSET_MIDDLE_LEFT);
    imagePositions.push_back(TEXTURE_OFFSET_MIDDLE_CENTER);
    imagePositions.push_back(TEXTURE_OFFSET_MIDDLE_RIGHT);
    imagePositions.push_back(TEXTURE_OFFSET_BOTTOM_LEFT);
    imagePositions.push_back(TEXTURE_OFFSET_BOTTOM_CENTER);
    imagePositions.push_back(TEXTURE_OFFSET_BOTTOM_RIGHT);
}

void ofApp::update(){
    updateTransparencies();
    repositionFace();
    masker.beginLayer(0);
    {
        ofSetColor(ofColor(ofColor::black, ofRandom(1) > 0.9 ? 255 : 32));
        ofRect(0, 0, gif.width, gif.height);
        ofSetColor(ofColor(ofColor::white, 120));
        face.incrementTextureOffsetY(0.001);
        face.draw();
        ofSetColor(ofColor(ofColor::white, 234));
        glass1.incrementTextureOffsetY(0.125);
        glass1.draw();
    }
    masker.endLayer(0);
    
    masker.beginMask(0);
    {
        ofBackground(ofColor::white);
        cardTransparency1.incrementTextureOffsetX(-0.01);
        cardTransparency2.incrementTextureOffsetX(0.1);
        cardTransparency3.incrementTextureOffsetX(-0.01);
        cardTransparency4.incrementTextureOffsetX(-0.02);
        cardTransparency5.incrementTextureOffsetX(0.02);
        cardTransparency6.incrementTextureOffsetX(-0.2);
        drawTransparency(drawTransparency1, cardTransparency1);
        drawTransparency(drawTransparency2, cardTransparency2);
        drawTransparency(drawTransparency3, cardTransparency3);
        drawTransparency(drawTransparency4, cardTransparency4);
        drawTransparency(drawTransparency5, cardTransparency5);
        drawTransparency(drawTransparency6, cardTransparency6);
    }
    masker.endMask(0);

    masker.beginLayer(1);
    {
        masker.drawLayer(0);
    }
    masker.endLayer(1);
    
    masker.beginMask(1);
    {
        masker.drawLayer(0);
    }
    masker.endMask(1);
}

void ofApp::updateTransparencies() {
    updateTransparency(drawTransparency1);
    updateTransparency(drawTransparency2);
    updateTransparency(drawTransparency3);
    updateTransparency(drawTransparency4);
    updateTransparency(drawTransparency5);
    updateTransparency(drawTransparency6);
}

void ofApp::updateTransparency(bool &draw) {
    if(draw) {
        if(ofRandom(1) > 0.7) draw = false;
    } else {
        if(ofRandom(1) > 0.5) draw = true;
    }
}

void ofApp::drawTransparency(bool &draw, ofxTexturePlane &image) {
    if(draw) {
        image.draw();
    }
}

void ofApp::repositionFace() {
    if(ofRandom(1) > 0.6) {
        face.setTextureScale(ofRandom(1.5, 4.5));
        face.setTextureOffset(imagePositions[floor(ofRandom(9))]);
        glass1.setTextureOffsetY(ofRandom(2));
    }
}

void ofApp::draw(){
    gif.begin();
    {
        face.draw();
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