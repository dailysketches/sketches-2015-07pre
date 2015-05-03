#include "ofApp.h"

/* This draws the animation */
void ofApp::setupAnim() {
    ofEnableSmoothing();
    ofEnableAntiAliasing();
    
    shapeSystem.setup();
    camera.setDistance(120);
    
    for(int i = 0; i < 24; i++) {
        GradientShape ring;
        rings.push_back(ring);
    }
    
    for(int i = 0; i < rings.size(); i++) {
        if(i % 3 == 0) color.set(255, 0, 0, 80);
        if(i % 3 == 1) color.set(0, 255, 0, 80);
        if(i % 3 == 2) color.set(0, 0, 255, 80);
        
        rings.at(i).setupHollowRing(60, 3, i * 3); //Resolution, thickness, diameter
        rings.at(i).setColor(color);
        rings.at(i).setBlur(3);
        shapeSystem.add(rings.at(i));
    }
}

void ofApp::updateAnim(){
    float current = sin(ofGetFrameNum() * 0.16);
    endpoint = ofMap(current, -1, 1, 1257, 1263);
    rotation = ofMap(current, -1, 1, 0, 360);
    
    for(int i = 0; i < rings.size(); i++) {
        if(i % 6 == 0) rings.at(i).rotateX(rotation);
        if(i % 6 == 1) rings.at(i).rotateY(rotation);
        if(i % 6 == 2) rings.at(i).rotateZ(rotation);
        if(i % 6 == 3) rings.at(i).rotateX(-rotation);
        if(i % 6 == 4) rings.at(i).rotateY(-rotation);
        if(i % 6 == 5) rings.at(i).rotateZ(-rotation);
        
        rings.at(i).setArcEndpoints(0, endpoint);
    }
    shapeSystem.update();
    
    if(ofGetFrameNum() == 0) {
        firstEndpoint = endpoint;
        lastEndpoint = endpoint;
    }
}

void ofApp::drawAnim() {
    ofBackground(0, 0, 0);
    camera.begin();
    shapeSystem.draw();
    camera.end();
    
    if(endpoint > firstEndpoint && lastEndpoint < firstEndpoint) {
        renderGif();
    }
    
    lastEndpoint = endpoint;
}

/* This handles the setup and GIF rendering, etc */
void ofApp::setup(){
    //Gif render values
    renderMode = false;
    width = 360, height = 360;
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