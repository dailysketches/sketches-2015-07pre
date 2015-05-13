#include "ofApp.h"

/* This draws the animation */
void ofApp::setupAnim() {
    maskOpacity = 255;

    for(int i = 0; i < 50; i++) {
        position.x = ofRandom(-width, width*2);
        position.y = ofRandom(-height, height*2);
        position.z = ofRandom(-400, 0);
        size = ofRandom(20, 380);
        thickness = size * 0.18;
        
        ofxShape square;
        square.setupHollowSquare(thickness, size);
        square.setPosition(position);
        square.setBlur(2);
        shapes.push_back(square);

        ofxShape ring;
        ring.setupHollowRing(60, thickness, size);
        ring.setPosition(position);
        ring.rotateY(90);
        ring.setBlur(2);
        shapes.push_back(ring);
    }
    
    for(int i = 0; i < shapes.size(); i++) {
        system.add(shapes.at(i));
    }
}

void ofApp::updateAnim(){
    float brightness = ofMap(sin(ofGetFrameNum() * 0.03), -1, 1, 0, 255);
    ofColor color = ofColor(brightness, brightness, brightness, 100);

    for(int i = 0; i < shapes.size(); i++) {
        shapes.at(i).incrementRotateX(12);
        shapes.at(i).incrementRotateY(0.8);
        shapes.at(i).incrementRotateZ(-0.77);
        shapes.at(i).incrementPositionX(4);
        shapes.at(i).incrementPositionY(-6);
        shapes.at(i).incrementPositionZ(12);
        shapes.at(i).setColor(color);
    }
}

void ofApp::drawAnim() {
    ofEnableAlphaBlending();

    //Swallow the trails
    ofSetColor(0, 0, 0, 30);
    ofRect(0, 0, width, height);

    system.draw();

    //Fade in
    if(maskOpacity > 0 && ofGetFrameNum() < 20) {
        ofSetColor(0, 0, 0, maskOpacity);
        ofRect(0, 0, width, height);
        maskOpacity -= 25;
    }

    //Fade out
    if(ofGetFrameNum() > 20) {
        ofSetColor(0, 0, 0, maskOpacity);
        ofRect(0, 0, width, height);
        maskOpacity += 25;
    }

    ofDisableAlphaBlending();

    if(maskOpacity > 255) {
        renderGif();
    }
}

/* This handles the setup and GIF rendering, etc */
void ofApp::setup(){
    //Gif render values
    slowMode = false;
    width = 500, height = 500;
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
    ofClear(0, 0, 0, 255);
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