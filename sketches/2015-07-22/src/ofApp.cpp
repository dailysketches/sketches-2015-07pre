#include "ofApp.h"
/* Begin description
{
    An endless process
}
End description */

/* Snippet begin */
void ofApp::setup(){
    ofSetWindowShape(1000, 800);
    numLayers = 6;
    gif.setup(ofGetTimestampString("out/%Y-%m-%d"), 80, 500, 500, ISOLATE_DRAWING);
    gif.fadeInOut(2, 4, 4);
    masker.setup(500, 500, numLayers, ISOLATE_LAYERS);
    masker.toggleOverlay();
    glass.setup("glass3.png", 500, 500, 2.0);
    wbw.setup("wbw.png", 500, 500, 0.5);
    for(int i = 0; i < numLayers; i++) {
        wbw.setTextureOffset(i);
        wbws.push_back(wbw);
    }
    bwb.setup("bwb.png", 500, 500, 0.25);
    for(int i = 0; i < numLayers; i++) {
        bwb.setTextureOffset(8-i);
        bwbs.push_back(bwb);
    }
}

void ofApp::update(){
    for(int i = 0; i < numLayers; i++) {
        wbws.at(i).incrementTextureOffset(-0.01, i % 2 == 0 ? -0.01 : 0.01);
        bwbs.at(i).incrementTextureOffset(i % 2 == 0 ? 0.01 : 0, i % 2 == 0 ? -0.01 : 0.01);
        
        masker.beginLayer(i);
        {
            if(i % 2 == 0) {
                ofSetColor(ofColor:: red);
                for(int y = i * 2; y < gif.height; y+=10) {
                    ofLine(0, y, gif.width, y);
                }
            } else {
                wbws.at(i).draw();
            }
        }
        masker.endLayer(i);
        
        masker.beginMask(i);
        {
            bwbs.at(i).draw();
        }
        masker.endMask(i);
    }
}

void ofApp::draw(){
    gif.begin();
    {
        glass.incrementTextureOffsetY(0.01);
        glass.draw();
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