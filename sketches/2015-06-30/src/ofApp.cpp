#include "ofApp.h"

void ofApp::setup(){
    finalFrame = 59;
    frameDecay = 64;
    lastDrawableFrameForLoop = finalFrame - (256 / frameDecay);
    ofSetWindowShape(500, 500);
    gif.setup(ofGetTimestampString("%Y-%m-%d"), finalFrame);

    ofEnableSmoothing();
    shapeSystem.setup();
    masker.setup(4);
    
    for(int i = 0; i < 4; i++) {
        textures.push_back(texture);
        textures.at(i).setup("road" + ofToString(i + 1) + ".png");
    }

    shapeSize = gif.width * 0.5;
    thickness = gif.width * 0.45;
    halfShapeSize = shapeSize * 0.5;

    for(int i = 0; i < gif.width; i += shapeSize) {
        for(int j = 0; j < gif.height; j += shapeSize) {
            shape.setupHollowArc(30, thickness, shapeSize, 180);
            shape.setColor(ofColor::fromHsb(ofRandom(100, 120), ofRandom(100, 255), ofRandom(100, 255)));
            shape.setBlur(30);
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

    for(int i = 0; i < masker.numLayers(); i++) {
        masker.beginLayer(i);
        {
            ofBackground(ofColor::black);
            ofEnableAlphaBlending();
            rotateScreen(90 * i);
            shapeSystem.draw();
            ofDisableAlphaBlending();
        }
        masker.endLayer(i);
        
        masker.beginMask(i);
        {
            ofBackground(ofColor::black);
            if(ofRandom(1) > 0.6 && ofGetFrameNum() <= lastDrawableFrameForLoop) {
                int j = floor(ofRandom(3.9999999));
                textures.at(j).setTextureScale(ofRandom(0.1, 2));
                textures.at(j).setTexturePosition(ofRandom(-1, 1), ofRandom(-1, 1));
                textures.at(j).draw();
            }
        }
        masker.endMask(i);
    }
}

void ofApp::draw(){
    gif.begin();
    {
        ofEnableAlphaBlending();
        if(ofGetFrameNum() == 0) {
            ofBackground(ofColor::black);
        } else {
            ofSetColor(ofColor::black, frameDecay);
            ofRect(0, 0, gif.width, gif.height);
        }
        masker.draw();
        ofDisableAlphaBlending();
    }
    gif.endAndCaptureFrame();
    gif.draw();

    masker.drawOverlay();
}

void ofApp::rotateScreen(float degrees) {
    ofTranslate(gif.halfWidth, gif.halfHeight, 0);
    ofRotate(degrees);
    ofTranslate(-gif.halfWidth, -gif.halfHeight, 0);
}

void ofApp::keyPressed(int key){
    if(key =='o') {
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