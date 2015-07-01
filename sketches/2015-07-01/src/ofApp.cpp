#include "ofApp.h"

void ofApp::setup(){
    ofSetWindowShape(500, 500);
    gif.setup(ofGetTimestampString("%Y-%m-%d"), 60);
    
    ofEnableSmoothing();
    shapeSystem.setup();
    masker.setup(8);

    for(int i = 0; i < 8; i++) {
        textures.push_back(texture);
        textures.at(i).setup("road" + ofToString(i % 4 + 1) + ".png", (i+1) * 0.3);
    }
    
    shapeSize = 100;
    thickness = 100;
    halfShapeSize = shapeSize * 0.5;
    
    for(int i = 0; i < gif.width; i += shapeSize) {
        for(int j = 0; j < gif.height; j += shapeSize) {
            shape.setupHollowArc(30, thickness, shapeSize, 180);
            shape.setColor(ofColor::fromHsb(ofRandom(255), ofRandom(100, 255), ofRandom(100, 255)));
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
        shapes.at(i).incrementRotateZ(6) :
        shapes.at(i).incrementRotateZ(-6);
    }
    
    for(int i = 0; i < masker.numLayers(); i++) {
        textures.at(i % textures.size()).incrementTextureOffsetY(-0.03333333333);
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
            ofEnableAlphaBlending();
            if(ofGetFrameNum() == 0) {
                ofBackground(ofColor::black);
            } else {
                ofSetColor(ofColor::black, 64);
                ofRect(0, 0, gif.width, gif.height);
            }

            ofSetColor(ofColor::white, 196);
            textures.at(i % textures.size()).draw();
            if(ofRandom(1) > 0.96) {
                for(int j = 0; j < 4; j++) {
                    ofSetColor(j % 2 == 0 ? ofColor(ofColor::white, ofRandom(64, 196)) : ofColor::black);
                    ofTriangle(ofRandom(-gif.width, 0), ofRandom(-gif.height, 0),
                               ofRandom(0, gif.width), ofRandom(0, gif.height),
                               ofRandom(gif.width, gif.doubleWidth), ofRandom(gif.height, gif.doubleHeight));
                    rotateScreen(90);
                }
            }
            ofDisableAlphaBlending();
        }
        masker.endMask(i);
    }
}

void ofApp::draw(){
    gif.begin();
    {
        ofBackground(ofColor::black);
        masker.draw();
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