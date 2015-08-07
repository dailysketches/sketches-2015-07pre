#include "ofApp.h"

/* This draws the animation */
void ofApp::setupAnim() {
    ofEnableSmoothing();
    masker.setup(width, height);
    shapeSystem.setup();
    
    shape.setupGradientRing(8, 20, 160);
    shape.setPosition(ofVec3f(halfWidth, halfHeight, 0));
    for(int i = -10000; i < 1000; i+=12) {
        shape.positionZ(i);
        shapes.push_back(shape);
    }
    
    for(int i = 0; i < shapes.size(); i++) {
        shapeSystem.add(shapes.at(i));
    }
    
    img1.loadImage("welcome.png");
    img2.loadImage("unwelcome.png");
    flip = false;
}

void ofApp::updateAnim(){
    for(int i = 0; i < shapes.size(); i++) {
        increment = (i % 2 == 0) ? 4 : -8;
        shapes.at(i).incrementRotateX(increment);
        shapes.at(i).incrementRotateY(increment);
        shapes.at(i).incrementRotateZ(increment / 4);
    }
    
    masker.beginMask();
    ofBackground(ofColor::black);
    shapeSystem.draw();
    if(ofRandom(1) <= 0.1) {
        ofSetColor(ofColor::white, 255);
        ofRect(0, 0, width, height);
        flip = !flip;
    }
    masker.endMask();
    
    masker.beginBackground();
    flip ? img2.draw(0, 0) : img1.draw(0, 0);
    masker.endBackground();
    
    masker.beginForeground();
    flip ? img1.draw(0, 0) : img2.draw(0, 0);
    masker.endForeground();
}

void ofApp::drawAnim() {
    masker.draw();
    if(ofGetFrameNum() == 90) renderGif();
}

/* This handles the setup and GIF rendering, etc */
void ofApp::setup(){
    //Gif render values
    slowMode = false;
    paused = false;
    width = 400, height = 400;
    duration = 0.2, colors = 256;
    saveOnFrame = -1;
    
    filename = ofGetTimestampString("%Y-%m-%d") + ".gif";
    framerate = slowMode ? 5 : 10;
    halfWidth = width * 0.5;
    halfHeight = height * 0.5;
    
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
    
    if(!renderingNow && !paused) {
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