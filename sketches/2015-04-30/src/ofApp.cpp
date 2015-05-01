#include "ofApp.h"

/* This draws the animation */
void ofApp::setupAnim() {
    coordinateSystemCenter = ofPoint(width * 0.5, height * 0.5);
    outerRadius = width * 0.4;
    innerRadius = width * 0.2;
    ofEnableAntiAliasing();
    ofEnableSmoothing();
    ofSetLineWidth(1);
    
    for(int i = 0; i < 30; i++) {
        innerSpread.push_back(i * 36 + ofRandom(18));
        outerSpread.push_back(i * 36 + 18 + ofRandom(18));
    }
}

void ofApp::updateAnim(){
    
}

void ofApp::drawAnim() {
    ofBackground(0, 0, 0);
    ofTranslate(coordinateSystemCenter);
    
    ofPushMatrix();
    ofRotateZ(-ofGetFrameNum());
    drawArc(innerRadius, 120);
    ofPopMatrix();
    
    ofPushMatrix();
    ofRotateZ(ofGetFrameNum());
    drawArc(outerRadius, 220);
    ofPopMatrix();
    
    for(int i = 0; i < 10; i++) {
        ofPushMatrix();
        ofRotateZ(innerSpread.at(i) + ofGetFrameNum() * 4);
        ofLine(0, -height*0.2, 0, -height*0.25);
        ofPopMatrix();
    }
    
    for(int i = 0; i < 20; i++) {
        ofPushMatrix();
        ofRotateZ(innerSpread.at(i) - ofGetFrameNum() * 4);
        ofLine(0, -height*0.25, 0, -height*0.3);
        ofPopMatrix();
    }
    
    for(int i = 0; i < 30; i++) {
        ofPushMatrix();
        ofRotateZ(innerSpread.at(i) - ofGetFrameNum() * 2);
        ofLine(0, -height*0.3, 0, -height*0.5);
        ofPopMatrix();
    }
    
    for(int i = 0; i < 20; i++) {
        ofPushMatrix();
        ofRotateZ(outerSpread.at(i) - ofGetFrameNum() * 2);
        ofLine(0, -height*0.45, 0, -height*0.5);
        ofPopMatrix();
    }
    
    if(ofGetFrameNum() == 360) {
        renderGif();
    }
}

void ofApp::drawArc(float radius, float angleEnd) {
    ofPolyline line;
    line.arc(0, 0, radius, radius, 0, angleEnd, 60);
    line.draw();
}

/* This handles the setup and GIF rendering, etc */
void ofApp::setup(){
    //Gif render values
    renderMode = false;
    width = 400, height = 400;
    duration = .02, colors = 256;
    saveOnFrame = -1;

    filename = ofGetTimestampString("%Y-%m-%d") + ".gif";
    framerate = renderMode ? 5 : 20;
    
    //Init
    ofSetFrameRate(framerate);
    ofSetWindowShape(width, height);
    ofSetWindowPosition(400, 800);
    
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
    renderingNow = true;
    gifEncoder.save(filename);
    renderMessage = "Now rendering";
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