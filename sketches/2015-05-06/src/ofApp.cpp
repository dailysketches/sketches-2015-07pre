#include "ofApp.h"

/* This draws the animation */
void ofApp::setupAnim() {
    paused = true;
    
    for(int i = 5; i > 0; i--) {
        vector<ofxShape> shapeLayer;
        ofxAnimatableFloat positionZ;
        animDuration = 4;
        positionZ.reset(i * 8);
        positionZ.animateToAfterDelay(-(i * 300), ofMap(i, 5, 1, 0, animDuration));
        positionZ.setDuration(animDuration);
        positionZ.setCurve(EASE_IN_EASE_OUT);
        positionZ.setRepeatType(LOOP_BACK_AND_FORTH);
        positionsZ.push_back(positionZ);
        
        ofxAnimatableFloat rotationZ;
        animDuration = 2;
        rotationZ.reset(0);
        rotationZ.animateToAfterDelay(360, ofMap(i, 5, 1, 0, animDuration));
        rotationZ.setDuration(animDuration);
        rotationZ.setCurve(EASE_IN_EASE_OUT);
        rotationZ.setRepeatType(LOOP);
        rotationsZ.push_back(rotationZ);
        
        for(int j = 0; j < i; j++) {
            for(int k = 0; k < i; k++) {
                size = (width / i) * 0.38;
                
                ofxShape shape;
                shape.setupFilledRing(60, size * 1.8);
                shape.setBlur(20);
                shape.positionX(((width / i) * j) + (width / i / 2));
                shape.positionY(((height / i) * k) + (height / i / 2));
                shape.setColor(ofColor::fromHsb(ofMap(i, 5, 1, 130, 170), 150, 60));
                shapeLayer.push_back(shape);
            }
        }
        
        shapes.push_back(shapeLayer);
    }

    for(int i = 0; i < shapes.size(); i++) {
        ofxShapeSystem shapeSystem;
        
        for(int j = 0; j < shapes.at(i).size(); j++) {
            shapeSystem.add(shapes.at(i).at(j));
        }
        
        shapeSystems.push_back(shapeSystem);
    }
}

void ofApp::updateAnim(){
    for(int i = 0; i < positionsZ.size(); i++) {
        positionsZ.at(i).update(1.0f/framerate);
    }
    
    for(int i = 0; i < rotationsZ.size(); i++) {
        rotationsZ.at(i).update(1.0f/framerate);
    }
    
    for(int i = 0; i < shapes.size(); i++) {
        for(int j = 0; j < shapes.at(i).size(); j++) {
            shapes.at(i).at(j).positionZ(positionsZ.at(i).val());
        }
    }
    
    for(int i = 0; i < shapeSystems.size(); i++) {
        shapeSystems.at(i).update();
    }
}

void ofApp::drawAnim() {
    if(ofGetFrameNum() == 82) paused = false;
    
    ofBackground(0, 0, 0);
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    for(int i = 0; i < shapeSystems.size(); i++) {
        ofPushMatrix();
        ofTranslate(width * 0.5, height * 0.5);
        ofRotateZ(rotationsZ.at(i).val());
        ofTranslate(-(width * 0.5), -(height * 0.5));
        shapeSystems.at(i).draw();
        ofPopMatrix();
    }
    ofDisableBlendMode();
    
    if(ofGetFrameNum() == 164) {
        renderGif();
    }
}

/* This handles the setup and GIF rendering, etc */
void ofApp::setup(){
    //Gif render values
    slowMode = false;
    width = 400, height = 400;
    duration = 0.2, colors = 256;
    saveOnFrame = -1;

    filename = ofGetTimestampString("%Y-%m-%d") + ".gif";
    framerate = slowMode ? 5 : 10;
    
    //Init
    ofSetFrameRate(framerate);
    ofSetWindowShape(width, height);
    gifEncoder.setup(width, height, duration, colors);
    renderingNow = false;
    paused = false;
    renderMessage = "";
    
    fbo.allocate(width, height, GL_RGB);
    fbo.begin();
    ofClear(255, 255, 255, 0);
    fbo.end();

    //Begin patch
    setupAnim();
}

void ofApp::update(){
    updateAnim();
}

void ofApp::draw(){
    fbo.begin();
    drawAnim();
    fbo.end();
    
    if(!renderingNow && !paused) {
        captureFrame();
    }
    
    ofSetColor(255, 255, 255, 255);
    fbo.draw(0, 0);
    if(paused) {
        ofDrawBitmapString("paused", 20, height - 50);
    } else {
        ofDrawBitmapString(
            "Recording to frame #" +
            ofToString(saveOnFrame) +
            " at " +
            ofToString(ofGetFrameRate()) +
            "fps...\nCurrent frame: " +
            ofToString(ofGetFrameNum()) +
            "\n" + renderMessage,
            20, height - 50);
    }
}

void ofApp::captureFrame() {
    fbo.readToPixels(pixels);
    gifEncoder.addFrame(pixels.getPixels(), width, height,
                        pixels.getBitsPerPixel(), duration);
    
    if(ofGetFrameNum() == saveOnFrame) {
        renderGif();
    }
}

void ofApp::renderGif() {
    if(!renderingNow) {
        renderingNow = true;
        gifEncoder.save(filename);
        renderMessage = "Now rendering";
    }
}

void ofApp::exit(){
    gifEncoder.exit();
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