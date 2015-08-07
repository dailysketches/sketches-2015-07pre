#include "ofApp.h"

/* This draws the animation */
void ofApp::setupAnim() {
    ofEnableSmoothing();
    boundary = 25;
    increment = 8;
    for(int i = 0; i <= 20; i++) {
        line.addVertex(i * width * 0.05, ofRandom(-boundary, boundary));
    }
    lines.push_back(line);
}

void ofApp::updateAnim(){
    if(ofGetFrameNum() < 39) {
        for(int i = 0; i <= 20; i++) {
            line[i].y = drunkWalk(line[i].y);
        }
        lines.push_back(line);
    }
    
    if(ofGetFrameNum() >= 40) {
        if(lines.size() == 1) {
            renderGif();
        } else {
            lines.pop_back();
        }
    }
}

void ofApp::drawAnim() {
    ofBackground(0, 255, 255);
    alpha = 255;
    
    ofTranslate(0, boundary* 2);
    
    ofPushMatrix();
    for(int i = 0; i < lines.size() && alpha >= 0; i++) {
        ofSetColor(1, 131, 185, alpha);
        ofSetLineWidth(i * 0.8);
        
        ofTranslate(0, i);
        lines.at(lines.size() - 1 - i).draw();
        alpha -= 16;
    }
    ofPopMatrix();
    
    ofSetLineWidth(2);
    ofSetColor(255, 255, 255, 200);
    lines.at(lines.size() - 1).draw();
}

float ofApp::drunkWalk(float from) {
    if(from > boundary - increment) return from - increment;
    if(from < -boundary + increment) return from + increment;
    return ofRandom(1) > 0.5 ?
            from + increment :
            from - increment;
}

/* This handles the setup and GIF rendering, etc */
void ofApp::setup(){
    //Gif render values
    renderMode = true;
    width = 500, height = 200;
    duration = .02, colors = 256;
    saveOnFrame = -1;

    filename = ofGetTimestampString("%Y-%m-%d") + ".gif";
    framerate = renderMode ? 5 : 20;
    
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