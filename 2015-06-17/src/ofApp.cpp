#include "ofApp.h"

/* This draws the animation */
void ofApp::setupAnim() {
    numImages = 8;
    highestIndex = numImages - 1;
    image.setup("surface.png");
    for(int i = 0; i < numImages; i++) {
        image.setTextureOffsetX(ofRandom(500));
        image.setTextureScale(ofMap(i, 0, highestIndex, 2, 0.35));
        image.setPlaneHeight(ofMap(i, 0, highestIndex, 500, 200));
        image.setPlanePosition(0, ofMap(i, 0, highestIndex, -50, 300));
        images.push_back(image);
        imgColors.push_back(ofColor(ofMap(i, 0, highestIndex, 100, 255), ofMap(i, 0, highestIndex, 100, 0), 0, ofMap(i, 0, highestIndex, 0, 255)));
    }

    system.setup();
    shape.setupGradientSquare(70, height * 2);
    shape.positionX(-halfWidth - 35);
    shape.positionY(40);
    shape.setColor(ofColor(ofColor::white, 96));
    system.add(shape);
}

void ofApp::updateAnim(){
    for(int i = 0; i < numImages; i++) {
        images.at(i).incrementTextureOffsetX(i % 2 == 0 ? 0.03 : -0.03);
    }
}

void ofApp::drawAnim() {
    ofBackground(ofColor::black);
    
    ofEnableAlphaBlending();
    for(int i = 0; i < numImages; i++) {
        ofSetColor(imgColors.at(i));
        rotateScreen(90);
        images.at(i).draw();
        rotateScreen(180);
        images.at(i).draw();
        rotateScreen(90);
    }
    
    rotateScreen(180);
    system.draw();
    rotateScreen(180);
    system.draw();
    
    ofDisableAlphaBlending();
    
    if(ofGetFrameNum() == 67) {
        renderGif();
    }
}

void ofApp::rotateScreen(float degrees) {
    ofTranslate(halfWidth, halfHeight);
    ofRotateZ(degrees);
    ofTranslate(-halfWidth, -halfHeight);
}

/* This handles the setup and GIF rendering, etc */
void ofApp::setup(){
    //Gif render values
    slowMode = false;
    paused = false;
    width = 460, height = 460;
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