#include "ofApp.h"
/* Begin description
{
    "...a conscious, purposeful, and personal subject confronting an unconscious, purposeless, and impersonal universe..."
}
End description */

/* Snippet begin */
void ofApp::setup(){
    ofSetWindowShape(1000, 800);
    gif.setupPaused(ofGetTimestampString("out/%Y-%m-%d"), 30, 75, 500, 500, ISOLATE_DRAWING);
    masker.setup(500, 500, 1, ISOLATE_LAYERS);
    masker.toggleOverlay();

    glass1.setup("glass.png", 500, 500, 2.0);
    glass2.setup("glass.png", 500, 500, 2.0);
    framesBeforeRefresh = 15;
}

void ofApp::update(){
    if(ofGetFrameNum() % framesBeforeRefresh == 0) {
        refresh = true;
        int offsetIndex = floor(ofGetFrameNum() / framesBeforeRefresh);
        offsetIndex = ((offsetIndex % 3) + 0) * 2;
        glass1.setTextureOffset(offsetIndex);
        glass2.setTextureOffset(offsetIndex);
        glass1.setTextureScale(3.0);
        glass2.setTextureScale(3.0);
    } else {
        refresh = false;
        glass1.incrementTextureScale(-0.05);
        glass2.incrementTextureScale(0.05);
    }
    
    masker.beginLayer(0);
    {
        glass1.draw();
    }
    masker.endLayer(0);
    
    masker.beginMask(0);
    {
        glass2.draw();
    }
    masker.endMask(0);
}

void ofApp::draw(){
    gif.begin();
    {
        ofEnableAlphaBlending();
        if(refresh) {
            ofSetColor(ofColor::red);
            ofRect(0, 0, gif.width, gif.height);
        }
        masker.draw();
        ofDisableAlphaBlending();
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