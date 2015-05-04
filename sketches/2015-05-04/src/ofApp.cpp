#include "ofApp.h"

/* This draws the animation */
void ofApp::setupAnim() {
    
    done = false;
    numArcs = 8;
    
    for(int i = 0; i < numArcs; i++) {
        ofxShape arc;
        arcs.push_back(arc);
        ofxAnimatableFloat arcPosition;
        arcPositions.push_back(arcPosition);
        ofxAnimatableFloat arcRotation;
        arcRotations.push_back(arcRotation);
    }
    
    for(int i = 0; i < numArcs; i++) {
        arcPositions.at(i).setRepeatType(PLAY_ONCE);
        arcPositions.at(i).setCurve(SWIFT_GOOGLE);
        arcPositions.at(i).reset((width * 2) + (width * 0.2));
        arcPositions.at(i).animateTo(width * 0.5);
        arcPositions.at(i).setDuration(1.25);
        
        arcRotations.at(i).setRepeatType(PLAY_ONCE);
        arcRotations.at(i).setCurve(SWIFT_GOOGLE);
        arcRotations.at(i).animateFromTo(180, 0);
        arcRotations.at(i).setDuration(1.25);
        
        arcs.at(i).setupHollowArc(60, (i + 1) * 10, (i + 1) * 35, 180);
        arcs.at(i).setBlur(2);
        arcs.at(i).positionX(arcPositions.at(i).val());
        arcs.at(i).positionY(height * 0.5);
        
        //Set colors
        if(i % 3 == 0) arcs.at(i).setColor(ofColor(4,   110, 171));
        if(i % 3 == 1) arcs.at(i).setColor(ofColor(195, 62,  31));
        if(i % 3 == 2) arcs.at(i).setColor(ofColor(52,  189, 129));
        
        shapeSystem.add(arcs.at(i));
    }
}

void ofApp::updateAnim(){
    bool allFinished = true;
    
    if(!done) {
        for(int i = 0; i < numArcs; i++) {
            if(ofGetFrameNum() > (i * 7)) {
                arcPositions.at(i).update(1.0f/framerate);
                arcs.at(i).positionX(arcPositions.at(i).val());
        
                arcRotations.at(i).update(1.0f/framerate);
            
                if(i % 2 == 0) {
                    arcs.at(i).rotateZ(arcPositions.at(i).val());
                }
            
                if(i % 2 == 1) {
                    arcs.at(i).rotateZ(arcPositions.at(i).val() + 180);
                }
            }
        
            if(!arcPositions.at(i).hasFinishedAnimating()) {
                allFinished = false;
            }
        }
    }
    
    if(allFinished) {
        for(int i = 0; i < numArcs; i++) {
            arcPositions.at(i).setRepeatType(PLAY_ONCE);
            arcPositions.at(i).setCurve(SWIFT_GOOGLE);
            arcPositions.at(i).animateTo(width * 3);
        }
    }
    
    shapeSystem.update();
}

void ofApp::drawAnim() {
    ofBackground(0, 0, 0);
    ofEnableAlphaBlending();
    shapeSystem.draw();
    ofDisableAlphaBlending();
    
    if(ofGetFrameNum() == 68) {
        renderGif();
    }
}

/* This handles the setup and GIF rendering, etc */
void ofApp::setup(){
    //Gif render values
    renderMode = false;
    width = 500, height = 500;
    duration = 0.2, colors = 256;
    saveOnFrame = -1;

    filename = ofGetTimestampString("%Y-%m-%d") + ".gif";
    framerate = renderMode ? 5 : 10;
    
    //Init
    ofSetFrameRate(framerate);
    ofSetWindowShape(width, height);
    gifEncoder.setup(width, height, duration, colors);
    renderingNow = false;
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
    
    if(!renderingNow) {
        captureFrame();
    }
    
    ofSetColor(255, 255, 255, 255);
    fbo.draw(0, 0);
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