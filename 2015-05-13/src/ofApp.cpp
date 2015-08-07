#include "ofApp.h"

/* This draws the animation */
void ofApp::setupAnim() {
    numShapes = 4;
    spacing = width / numShapes; //20
    offset = spacing * 0.5;      //10
    
    for(int x = 0; x < numShapes; x++) {
        for(int y = 0; y < numShapes; y++) {
            for(int size = spacing - 2; size > 0; size-=4) {
                ofxShape shape;
                shape.setupHollowSquare(1, size);
                shape.positionX(x * spacing + offset);
                shape.positionY(y * spacing + offset);
                shape.positionZ(100);
                shapes.push_back(shape);
            }
        }
    }
    
    for(int i = 0; i < shapes.size(); i++) {
        system.add(shapes.at(i));
    }
}

void ofApp::updateAnim(){
    for(int i = 0; i < shapes.size(); i++) {
        if(i % 2 == 0) {
            shapes.at(i).incrementRotateZ(1);
        } else {
            shapes.at(i).incrementRotateZ(-1);
        }
    }
}

void ofApp::drawAnim() {
    ofBackground(0, 0, 0);
    system.draw();
    
    if(ofGetFrameNum() == 90) {
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
    ofSetColor(255, 255, 255, 160);
    ofRect(16, height - 64, 330, 32);
    ofSetColor(0, 0, 0, 255);
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