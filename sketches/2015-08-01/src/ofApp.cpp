#include "ofApp.h"
/* Begin description
{
    Taking turns
}
End description */

/* Snippet begin */
void ofApp::setup(){
    ofSetWindowShape(1000, 800);
    gif.setup(ofGetTimestampString("out/%Y-%m-%d"), 63, 500, 500, ISOLATE_DRAWING);
    masker.setup(500, 500, 3, ISOLATE_LAYERS);
    masker.toggleOverlay();
    mask.setup("face-mask.png", 500, 500, 0.0625, TEXTURE_OFFSET_MIDDLE_LEFT);
    glass.setup("glass3.png", 500, 500);
    shapeSystem.setup();
    for(int i = 0; i < 105; i++) {
        shape.setupHollowSquare(40, 100);
        shape.setBlur(2);
        shape.rotateX(ofRandom(360));
        shape.setPosition(
            ofRandom(-60, gif.width + 60),
            ofRandom(-60, gif.width + 60));
        shape.setColor(ofColor(ofColor::red, ofRandom(5, 250)));
        shapes.push_back(shape);
    }
    for(int i = 0; i < shapes.size(); i++) {
        shapeSystem.add(shapes.at(i));
    }
}

void ofApp::update(){
    mask.incrementTextureOffsetY(0.03183098861838);
    glass.incrementTextureOffsetY(-0.03183098861838);
    glass.setTextureScale(ofMap(sin(ofGetFrameNum() * 0.1), -1, 1, 4, 1));
    mask.setTextureScale(ofMap(sin(ofGetFrameNum() * 0.1), -1, 1, 0.5, 1.2));
    for(int i = 0; i < shapes.size(); i++) {
        shapes.at(i).incrementRotateZ(i % 2 == 0 ? -5.71428571428571 : 5.71428571428571);
    }
    masker.beginLayer(0);
    {
        ofBackground(ofColor::black);
        shapeSystem.draw();
    }
    masker.endLayer(0);
    
    masker.beginMask(0);
    {
        ofBackground(ofColor::black);
        mask.draw();
    }
    masker.endMask(0);
    
    masker.beginLayer(1);
    {
        ofSetColor(ofColor::red);
        glass.draw();
    }
    masker.endLayer(1);
    
    masker.beginMask(1);
    {
        masker.drawLayer(0, false);
    }
    masker.endMask(1);
    
    masker.beginLayer(2);
    {
        ofBackground(ofColor::white);
        masker.drawLayer(1);
        masker.drawLayer(0);
    }
    masker.endLayer(2);
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