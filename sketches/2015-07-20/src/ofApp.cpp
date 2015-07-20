#include "ofApp.h"
/* Begin description
{
    A torn checkerboard
}
End description */

/* Snippet begin */
void ofApp::setup(){
    ofSetWindowShape(1000, 800);
    gif.setup(ofGetTimestampString("out/%Y-%m-%d"), 100, 500, 500, ISOLATE_DRAWING);
    masker.setup(500, 500, 3, ISOLATE_LAYERS);
    masker.toggleOverlay();
    mask.setup("face-mask.png", 500, 500, 1.5, TEXTURE_OFFSET_MIDDLE_CENTER);
    glass.setup("glass3.png", 500, 500, 2.0);
    shapeSystem.setup();
    numPerDimension.x = 2;
    numPerDimension.y = numPerDimension.x * 2;
    spacing.x = gif.width / numPerDimension.x;
    halfSpacing.x = spacing.x * 0.5;
    spacing.y = gif.height / numPerDimension.y;
    halfSpacing.y = spacing.y * 0.5;
    for(int x = 0; x < numPerDimension.x; x++) {
        for(int y = 0; y < numPerDimension.y; y++) {
            shape.setupFilledSquare(halfSpacing.x);
            shape.setPosition(
                x * spacing.x + halfSpacing.x*0.5 + (y % 2 == 0 ? halfSpacing.x : 0),
                y * spacing.y + halfSpacing.y);
            shapes.push_back(shape);
        }
    }
    for(int i = 0; i < shapes.size(); i++) {
        shapeSystem.add(shapes.at(i));
    }
}

void ofApp::update(){
    mask.incrementTextureOffsetY(0.02);
    glass.incrementTextureOffsetY(0.08);
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
        ofBackground(ofColor::white);
        //shapeSystem.draw();
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