#include "ofApp.h"

/* This draws the animation */
void ofApp::setupAnim() {
    numImages = 50;
    imageSpacing = height / numImages;
    
    image.setup("surface.png");
    image.setTextureScale(0.4);
    for(int i = 0; i < numImages; i++) {
        image.setTextureOffsetX(ofRandom(500));
        images.push_back(image);
        imgColors.push_back(ofColor(255, ofRandom(150), ofRandom(50), ofRandom(100)));
    }
    
    offset = ofRandom(5000);
}

void ofApp::updateAnim(){
    for(int i = 0; i < images.size(); i++) {
        noise = ofNoise(i, ofGetFrameNum() * 0.06 + offset);
        images.at(i).setPlaneHeight(noise * imageSpacing * 24);
        images.at(i).incrementTextureOffsetX(i % 2 == 0 ? 0.06 : -0.06);
    }
}

void ofApp::drawAnim() {
    ofBackground(ofColor::black);
    ofEnableAlphaBlending();
    for(int i = 0; i < images.size(); i++) {
        ofSetColor(imgColors.at(i));
        images.at(i).draw(0, halfImageSpacing + imageSpacing * i);
    }
    ofDisableAlphaBlending();
    
    if(ofGetFrameNum() == 100) {
        renderGif();
    }
}

/* This handles the setup and GIF rendering, etc */
void ofApp::setup(){
    //Gif render values
    slowMode = false;
    paused = false;
    width = 500, height = 500;
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