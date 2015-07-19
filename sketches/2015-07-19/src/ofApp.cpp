#include "ofApp.h"
/* Begin description
{
    There's blood on your hands
}
End description */

/* Snippet begin */
void ofApp::setup(){
    ofSetWindowShape(1000, 800);
    gif.setupPaused(ofGetTimestampString("out/%Y-%m-%d"), 60, 140, 500, 500, ISOLATE_DRAWING);
    masker.setup(500, 500, 2, ISOLATE_LAYERS);
    masker.toggleOverlay();
    
    leaf1.setup("leaf1-desaturated.png", 500, 500, 2.0);
    leaf2.setup("leaf2-desaturated.png", 500, 500, 2.0);
    glass1.setup("glass1.png", 500, 500);
    glass2.setup("glass2.png", 500, 500);
    direction = 0;
}

void ofApp::update(){
    leaf2.incrementTextureOffsetX(-0.1);
    if(ofGetFrameNum() == 0 || ofGetFrameNum() % 2 == 0) {
        glass1.setTexturePosition(ofRandom(2), ofRandom(2));
        glass1.setTextureScale(ofRandom(6, 10));
    }
    if(ofGetFrameNum() == 0 || ofGetFrameNum() % 2 == 1) {
        glass2.setTexturePosition(ofRandom(2), ofRandom(2));
        glass2.setTextureScale(ofRandom(0.5, 2));
    }

    masker.beginLayer(0);
    {
        ofSetColor(ofColor::red);
        leaf2.draw();
    }
    masker.endLayer(0);
    
    masker.beginMask(0);
    {
        glass1.draw();
    }
    masker.endMask(0);
    
    masker.beginLayer(1);
    {
        masker.drawLayer(0);
    }
    masker.endLayer(1);
    
    masker.beginMask(1);
    {
        glass2.draw();
    }
    masker.endMask(1);
}

void ofApp::draw(){
    gif.begin();
    {
        if(ofGetFrameNum() % 20 == 0) {
            leaf1.setTexturePosition(ofRandom(2), ofRandom(2));
            ofSetColor(ofColor(ofColor::white, 255));
            framesSinceLastAppearance = 0;
            direction++;
            if(direction > 1) {
                direction = 0;
            }
        } else {
            float alpha;
            if(framesSinceLastAppearance < 3) {
                alpha = 255;
            } else {
                alpha = 255 - framesSinceLastAppearance * 60;
            }
            if(alpha < 0) alpha = 0;
            if(direction == 0) {
                leaf1.incrementTextureOffsetX(0.06);
            }
            if(direction == 1) {
                leaf1.incrementTextureOffsetY(-0.03);
            }

            ofSetColor(ofColor(ofColor::white, alpha));
            framesSinceLastAppearance++;
        }
        leaf1.draw();
        masker.drawLayer(1);
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