#include "ofApp.h"

/* This draws the animation */
void ofApp::setupAnim() {
    ofEnableSmoothing();
    shapeSystem.setup();
    camera.setDistance(60);
    numShapes = 0;
    
    float offset = 10;
    
    color.set(255, 255, 255, 80);
    center.z -= offset;
    outerSquare.setup(++numShapes, center, 2, 4, 0, -5, 35, color);
    shapeSystem.add(outerSquare);
    
    color.set(255, 255, 255, 80);
    center.z -= offset;
    innerSquare.setup(++numShapes, center, 2, 4, 0, -5, 20, color);
    shapeSystem.add(innerSquare);
    
    center.z -= offset;
    color.set(255, 0, 0, 125);
    ring1.setup(++numShapes, center, 1, 60, 8, 8, 25, color);
    shapeSystem.add(ring1);
    
    center.z -= offset;
    color.set(255, 0, 0, 125);
    ring2.setup(++numShapes, center, 1, 60, 8, 8, 25, color);
    shapeSystem.add(ring2);
    
    center.z -= offset;
    color.set(255, 0, 0, 60);
    ring3.setup(++numShapes, center, 0, 60, 8, 8, 25, color);
    shapeSystem.add(ring3);
    
    center.z -= offset;
    color.set(255, 255, 255, 200);
    sphere.setup(++numShapes, center, 0, 60, 5, 0, 10, color);
    shapeSystem.add(sphere);
}

void ofApp::updateAnim(){
    outerSquare.rotateZ(ofMap(-ofGetFrameNum(), 1, 125, 1, 180));
    innerSquare.rotateZ(ofMap( ofGetFrameNum(), 1, 125, 1, 180));
    ring1.positionZ(sin( ofGetFrameNum() * 2       * 0.05) * 100 - 50);
    ring2.positionZ(sin((ofGetFrameNum() * 2 + 20) * 0.05) * 100 - 50);
    ring3.positionZ(sin((ofGetFrameNum() * 2 + 40) * 0.05) * 100 - 50);
    shapeSystem.update();
}

void ofApp::drawAnim() {
    ofBackground(0, 0, 0);
    camera.begin();
    shapeSystem.draw();
    camera.end();
    if(ofGetFrameNum() == 125) {
        renderGif();
    }
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