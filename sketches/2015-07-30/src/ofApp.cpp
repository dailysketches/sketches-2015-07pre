#include "ofApp.h"
/* Begin description
{
    Ironworks
}
End description */

/* Snippet begin */
void ofApp::setup(){
    ofSetWindowShape(1000, 800);
    gif.setupPaused(ofGetTimestampString("out/%Y-%m-%d"), 160, 220, 500, 500, ISOLATE_DRAWING);
    gif.fadeInOut(2, 4, ofColor::white, 4);
    masker.setup(500, 500, 1, ISOLATE_LAYERS);
    masker.toggleOverlay();
    foil1.setup("foil.png", 500, 500, 2.0);
    foil1.setTextureOffset(8);
    foil2.setup("foil.png", 500, 500, 6.0);
    foil2.setTextureOffset(TEXTURE_OFFSET_BOTTOM_RIGHT);
    
    glass.setup("glass.png", 0.1);
    for(int i = 0; i < 60; i++) {
        glass.setTextureOffset(ofRandom(2), ofRandom(2));
        glasses.push_back(glass);
    }
    shapeSystem.setup();
    
    shapeSize = gif.width / 3;
    thickness = 90;
    halfShapeSize = shapeSize * 0.5;
    
    for(int i = 0; i < gif.width; i += shapeSize) {
        for(int j = 0; j < gif.height; j += shapeSize) {
            shape.setupHollowArc(30, thickness, shapeSize, 180);
            shape.setColor(ofColor::white);
            shape.setBlur(25);
            shape.setPosition(ofVec3f(i + halfShapeSize, j + halfShapeSize, 0));
            shape.rotateZ(ofRandom(360));
            shapes.push_back(shape);
        }
    }
    
    for(int i = 0; i < shapes.size(); i++) {
        shapeSystem.add(shapes.at(i));
    }
}

void ofApp::update(){
    for(int i = 0; i < shapes.size(); i++) {
        i % 2 == 0 ?
        shapes.at(i).incrementRotateZ(12) :
        shapes.at(i).incrementRotateZ(-12);
    }
    
    foil1.incrementTextureOffsetY(-0.01);
    
    masker.beginLayer(0);
    {
        ofSetColor(ofColor(ofColor::white, 255));
        foil1.draw();
        ofSetColor(ofColor(ofColor::white, 40));
        for(int i = 0; i < glasses.size(); i++) {
            glasses.at(i).incrementTextureOffsetY(0.002 * (i + 1));
            glasses.at(i).draw();
        }
    }
    masker.endLayer(0);

    masker.beginMask(0);
    {
        ofSetColor(ofColor::black, 16);
        ofRect(0, 0, gif.width, gif.height);
        
        ofEnableAlphaBlending();
        
        for(int i = 0; i < shapes.size(); i++) {
            shapes.at(i).setColor(ofColor::white);
        }
        shapeSystem.draw();
        
        gif.rotateAroundCenter(90);
        for(int i = 0; i < shapes.size(); i++) {
            shapes.at(i).setColor(ofColor(ofColor::black, 120));
        }
        shapeSystem.draw();
        
        gif.rotateAroundCenter(90);
        for(int i = 0; i < shapes.size(); i++) {
            shapes.at(i).setColor(ofColor(ofColor::black, 90));
        }
        shapeSystem.draw();
        
        gif.rotateAroundCenter(90);
        for(int i = 0; i < shapes.size(); i++) {
            shapes.at(i).setColor(ofColor(ofColor::black, 60));
        }
        shapeSystem.draw();
        
        ofDisableAlphaBlending();
    }
    masker.endMask(0);
}

void ofApp::draw(){
    gif.begin();
    {
        ofEnableAlphaBlending();
        //ofBackground(ofColor::white);
        ofSetColor(ofColor(ofColor::white, 40));
        foil2.incrementTextureOffset(0.0025, 0.003);
        foil2.draw();
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