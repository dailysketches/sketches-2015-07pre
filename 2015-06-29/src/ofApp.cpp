#include "ofApp.h"

void ofApp::setup(){
    ofSetWindowShape(500, 500);
    gif.setupPaused(ofGetTimestampString("%Y-%m-%d"), 30, 59);

    ofEnableSmoothing();
    shapeSystem.setup();

    image.setup("glass.png", 0.5);

    shapeSize = 100;
    thickness = 60;
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

    image.incrementTextureOffsetY(0.06666666666);
}

void ofApp::draw(){
    gif.begin();
    {
        if(ofGetFrameNum() == 0) ofBackground(0, 0, 0);
        image.draw();
        ofSetColor(ofColor::black, 16);
        ofRect(0, 0, gif.width, gif.height);
        
        ofEnableAlphaBlending();
        
        for(int i = 0; i < shapes.size(); i++) {
            shapes.at(i).setColor(ofColor::white);
        }
        shapeSystem.draw();
        
        rotateScreen(90);
        for(int i = 0; i < shapes.size(); i++) {
            shapes.at(i).setColor(ofColor(ofColor::black, 192));
        }
        shapeSystem.draw();
        
        rotateScreen(90);
        for(int i = 0; i < shapes.size(); i++) {
            shapes.at(i).setColor(ofColor(ofColor::black, 164));
        }
        shapeSystem.draw();
        
        rotateScreen(90);
        for(int i = 0; i < shapes.size(); i++) {
            shapes.at(i).setColor(ofColor(ofColor::black, 128));
        }
        shapeSystem.draw();
        
        ofDisableAlphaBlending();
    }
    gif.endAndCaptureFrame();
    gif.draw();
}

void ofApp::rotateScreen(float degrees) {
    ofTranslate(gif.halfWidth, gif.halfHeight, 0);
    ofRotate(degrees);
    ofTranslate(-gif.halfWidth, -gif.halfHeight, 0);
}

void ofApp::keyPressed(int key){

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