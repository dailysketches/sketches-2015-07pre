#include "ofApp.h"

/* This draws the animation */
void ofApp::setupAnim() {
    ofEnableSmoothing();
    numPerDimension = 3;

    for(int x = 0; x < numPerDimension; x++) {
        for(int y = 0; y < numPerDimension; y++) {
            for(int z = 0; z < numPerDimension; z++) {
                cube = ofxShapeSystem();
                cube.setupCube(2, ofRandom(100, 200), ofColor(ofColor::red, 255));
                cube.setRotation(ofRandom(360), ofRandom(360), ofRandom(360));
                cube.positionX(ofMap(x, 0, numPerDimension-1, 0, width));
                cube.positionY(ofMap(y, 0, numPerDimension-1, 0, height));
                cube.positionZ(ofMap(z, 0, numPerDimension, 250, -250));
                cubes.push_back(cube);
            }
        }
    }
}

void ofApp::updateAnim() {
    for(int i = 0; i < cubes.size(); i++) {
        cubes.at(i).incrementRotateX(2);
        cubes.at(i).incrementRotateY(2);
        cubes.at(i).incrementRotateZ(2);
    }
}

void ofApp::drawAnim() {
    ofBackground(0, 0, 0);

    ofEnableAlphaBlending();
    rotateScreen(ofGetFrameNum() * 2);
    for(int i = 0; i < cubes.size(); i++) {
        cubes.at(i).draw();
    }

    if(ofGetFrameNum() == 180) renderGif();
}

void ofApp::rotateScreen(float degrees) {
    ofTranslate(halfWidth, halfHeight, 0);
    ofRotateX(degrees);
    ofTranslate(-halfWidth, -halfHeight, 0);
}

/* This handles the setup and GIF rendering, etc */
void ofApp::setup(){
    //Gif render values
    slowMode = false;
    width = 400, height = 200;
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