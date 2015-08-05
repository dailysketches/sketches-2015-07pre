#include "ofApp.h"
/* Begin description
{
    It's a direction.
}
End description */

/* Snippet begin */
void ofApp::setup(){
    ofSetWindowShape(1000, 800);
    gif.setup(ofGetTimestampString("out/%Y-%m-%d"), -1, 500, 500);
    masker.setup(500, 500, 2);
    masker.toggleOverlay();
    foil.setup("foil1.png", 500, 500, 2.0, TEXTURE_OFFSET_MIDDLE_CENTER);
    glass.setup("glass1-inverted.png", 500, 500, 1.0, TEXTURE_OFFSET_MIDDLE_CENTER);
    numTraps = 0;
}

void ofApp::update(){
    masker.beginLayer(0);
    {
        foil.incrementTextureOffsetY(0.01);
        ofSetColor(ofColor::red);
        foil.draw();
    }
    masker.endLayer(0);
    
    masker.beginMask(0);
    {
        glass.incrementTextureOffsetY(-0.01);
        ofBackground(ofColor::white);
        if(ofRandom(1) > 0.25) {
            ofSetColor(ofColor(ofColor::white, 120));
            glass.draw();
        }
    }
    masker.endMask(0);
    
    masker.beginLayer(1);
    {
        ofSetColor(ofColor::white);
        foil.draw();
    }
    masker.endLayer(1);
    
    masker.beginMask(1);
    {
        ofBackground(ofColor::black);
        ofSetColor(ofColor::white);
        ofRect(50, 200, 170, 90);
    }
    masker.endMask(1);
}

void ofApp::draw(){
    gif.begin();
    ofPushStyle();
    {
        if(ofGetFrameNum() == 0) ofBackground(ofColor::black);
        ofEnableAlphaBlending();
        ofSetColor(ofColor(ofColor::black, 32));
        ofRect(0, 0, gif.width, gif.height);
        
        ofSetColor(ofColor::white);
        float choice = ofRandom(1);
        if(choice > 0.75) {
            masker.drawLayers(0, 1);
        } else if(choice > 0.72) {
            numTraps++;
            ofSetColor(ofColor(ofColor::black, 32));
            ofRect(0, 0, gif.width, gif.height);
            ofSetColor(ofColor::white);
            masker.drawMask(1);
            gif.endCaptureDraw();
            gif.begin();
            ofSetColor(ofColor(ofColor::black, 32));
            ofRect(0, 0, gif.width, gif.height);
            ofSetColor(ofColor::white);
            masker.drawMask(1);
            gif.endCaptureDraw();
            gif.begin();
            ofSetColor(ofColor(ofColor::black, 32));
            ofRect(0, 0, gif.width, gif.height);
            ofSetColor(ofColor::white);
            masker.drawMask(1);
            gif.endCaptureDraw();
            gif.begin();
            ofSetColor(ofColor(ofColor::black, 32));
            ofRect(0, 0, gif.width, gif.height);
            ofSetColor(ofColor::white);
            masker.drawMask(1);
        } else {
            masker.drawLayer(1);
        }
    }
    ofPopStyle();
    gif.endCaptureDraw();
    masker.drawOverlay();
    if(numTraps == 2) {
        gif.render();
    }
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