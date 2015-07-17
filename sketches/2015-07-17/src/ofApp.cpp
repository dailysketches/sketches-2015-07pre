#include "ofApp.h"
/* Begin description
{
    That weird illusion thing again with 'impossible' walls.
}
End description */

/* Snippet begin */
void ofApp::setup(){
    ofSetWindowShape(1000, 800);
    gif.setupPaused(ofGetTimestampString("out/%Y-%m-%d"), 50, 150, 500, 500);
    masker.setup(500, 500, 5, ISOLATE_LAYERS);
    masker.toggleOverlay();

    face.setup("face.png", 500, 500, 1.0, TEXTURE_OFFSET_MIDDLE_CENTER);
    wall.setup("foil4.png", 500, 500, 1.0);
    wallMask.setup("card-invert-wall.png", 500, 500, 1.0);
    for(int i = 0; i < 4; i++) {
        walls.push_back(wall);
        wallMasks.push_back(wallMask);
    }
}

void ofApp::update(){
    float sine = sin(ofGetFrameNum() * 0.05);
    alpha = ofMap(sine, -1, 1, 20, 220);
    
    for(int i = 0; i < 4; i++) {
        masker.beginLayer(i);
        {
            gif.rotateAroundCenter(i * 90);
            walls.at(i).incrementTextureOffsetY(-0.02);
            walls.at(i).setTextureScale(ofMap(sine, -1, 1, 1.0, 4.0));
            ofSetColor(i % 2 == 0 ? ofColor(ofColor::red, alpha) : ofColor(ofColor::white, alpha));
            walls.at(i).draw();
        }
        masker.endLayer(i);
        
        masker.beginMask(i);
        {
            ofSetColor(ofColor::white);
            gif.rotateAroundCenter(i * 90);
            wallMasks.at(i).setTextureScale(ofMap(sine, -1, 1, 0.5, 0.5));
            wallMasks.at(i).incrementTextureOffsetY(-0.05);
            wallMasks.at(i).draw();
            if(i == 0) {
                ofSetColor(ofColor::black);
                ofRect(0, gif.halfHeight, gif.width, gif.halfHeight);
            }
        }
        masker.endMask(i);
    }
    
    masker.beginLayer(4);
    {
        ofSetColor(ofColor(ofColor::red, alpha));
        walls.at(0).draw();
    }
    masker.endLayer(4);
    
    masker.beginMask(4);
    {
        wallMasks.at(0).draw();
        ofSetColor(ofColor::black);
        ofRect(0, 0, gif.width, gif.halfHeight);
    }
    masker.endMask(4);
}

void ofApp::draw(){
    gif.begin();
    ofPushStyle();
    {
        ofEnableAlphaBlending();
        if(ofGetFrameNum() == 0) {
            ofBackground(ofColor::black);
        }
        if(ofRandom(1) > ofMap(alpha, 0, 255, 0.7, 1)) {
            ofSetColor(ofColor(ofColor::white, 255-alpha));
            face.setTextureOffset(TEXTURE_OFFSET_MIDDLE_CENTER);
            face.incrementTextureOffset(ofRandom(-0.05, 0.05), ofRandom(-0.5, 0.5));
            face.draw();
        } else {
            ofSetColor(ofColor(ofColor::black, alpha));
            ofRect(0, 0, gif.width, gif.height);
        }
        masker.draw();
        ofDisableAlphaBlending();
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