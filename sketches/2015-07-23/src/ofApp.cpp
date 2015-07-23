#include "ofApp.h"
/* Begin description
{
    Floating
}
End description */

/* Snippet begin */
void ofApp::setup(){
    ofSetWindowShape(1000, 800);
    numLayers = 2;
    gif.setupPaused(ofGetTimestampString("out/%Y-%m-%d"), 100, 180, 500, 500, ISOLATE_DRAWING);
    gif.fadeInOut(2, 4, 4);
    masker.setup(500, 500, numLayers, ISOLATE_LAYERS);
    masker.toggleOverlay();
    foil.setup("foil.png", 500, 500, 6.0);
    wbw.setup("wbw.png", 500, 500, 0.5);
    for(int i = 0; i < numLayers; i++) {
        wbw.setTextureOffset(i);
        wbws.push_back(wbw);
    }
    mask.setup("foil.png", 500, 500, 2.0);
    for(int i = 0; i < numLayers; i++) {
        mask.setTextureOffset(8-i);
        masks.push_back(mask);
    }
}

void ofApp::update(){
    for(int i = 0; i < numLayers; i++) {
        wbws.at(i).incrementTextureOffset(-0.01, i % 2 == 0 ? -0.01 : 0.01);
        masks.at(i).incrementTextureOffset(i % 2 == 0 ? 0.005 : 0, i % 2 == 0 ? -0.005 : 0.01);
        
        masker.beginLayer(i);
        {
            if(i % 2 == 0) {
                ofSetColor(ofColor::powderBlue);
                for(int y = i * 2; y < gif.height; y+=4) {
                    ofLine(0, y, gif.width, y);
                }
            } else {
                wbws.at(i).draw();
            }
        }
        masker.endLayer(i);
        
        masker.beginMask(i);
        {
            masks.at(i).draw();
        }
        masker.endMask(i);
    }
}

void ofApp::draw(){
    gif.begin();
    {
        foil.incrementTextureOffset(0.0015, 0.0015);
        foil.draw();
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