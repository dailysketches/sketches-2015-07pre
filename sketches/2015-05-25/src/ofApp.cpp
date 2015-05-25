#include "ofApp.h"

/* This draws the animation */
void ofApp::setupAnim() {
    ofEnableSmoothing();
    
    for(int i = 0; i < width; i += 120) {
        for(int j = 0; j < height; j += 120) {
            shape.setupHollowSquare(20, 80);
            shape.setBlur(1);
            shape.setPosition(ofVec3f(i + 5, j + 5, 0));
            shape.rotateZ(ofRandom(360));
            shapes.push_back(shape);
        }
    }
    
    for(int i = 0; i < shapes.size(); i++) {
        shapeSystem.add(shapes.at(i));
    }
}

void ofApp::updateAnim(){
    for(int i = 0; i < shapes.size(); i++) {
        i % 2 == 0 ?
            shapes.at(i).incrementRotateZ(12) :
            shapes.at(i).incrementRotateZ(-12);
    }
}

void ofApp::drawAnim() {
    ofBackground(0, 0, 0);

    ofEnableAlphaBlending();

    ofTranslate(-30, -30);
    for(int i = 0; i < shapes.size(); i++) {
        shapes.at(i).setColor(ofColor(ofColor::white, 64));
    }
    shapeSystem.draw();

    ofTranslate(10, 10);
    for(int i = 0; i < shapes.size(); i++) {
        shapes.at(i).setColor(ofColor(ofColor::white, 128));
    }
    shapeSystem.draw();

    ofTranslate(10, 10);
    for(int i = 0; i < shapes.size(); i++) {
        shapes.at(i).setColor(ofColor(ofColor::white, 192));
    }
    shapeSystem.draw();

    ofTranslate(10, 10);
    for(int i = 0; i < shapes.size(); i++) {
        shapes.at(i).setColor(ofColor(ofColor::white, 255));
    }
    shapeSystem.draw();

    ofDisableAlphaBlending();

    if(ofGetFrameNum() == 30) renderGif();
}

void ofApp::rotateScreen(float degrees) {
    ofTranslate(halfWidth, halfHeight, 0);
    ofRotate(degrees);
    ofTranslate(-halfWidth, -halfHeight, 0);
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