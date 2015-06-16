#include "ofApp.h"

/* This draws the animation */
void ofApp::setupAnim() {
    masker.setup(width, height);
    layer1 = masker.newLayer();
    layer2 = masker.newLayer();
    
    image1.setup("foil.png");
    image2.setup("foil.png");
    
    image1.setOffsetX(0);
    image1.setOffsetY(0);
    image2.setOffsetX(1);
    image2.setOffsetY(1);
    
    pos = 0;
    size = width * 0.2;
}

void ofApp::updateAnim(){
    pos+=10;
    if(pos > height * 2) {
        pos = 0;
    }
    
    masker.beginLayer(layer1);
    {
        image1.incrementOffsetX(0.01);
        image1.incrementOffsetY(0.01);
        image1.draw();
    }
    masker.endLayer(layer1);
    
    masker.beginMask(layer1);
    {
        ofBackground(ofColor::black);
        ofSetColor(ofColor::white);
        for(int x = 0; x < size; x++) {
            if(x % 2 == 0) {
                ofRect(x * size, height - pos, size, height);
            }
        }
    }
    masker.endMask(layer1);

    masker.beginLayer(layer2);
    {
        image2.incrementOffsetX(-0.01);
        image2.incrementOffsetY(-0.01);
        image2.draw();
    }
    masker.endLayer(layer2);
    
    masker.beginMask(layer2);
    {
        ofBackground(ofColor::black);
        ofSetColor(ofColor::white);
        for(int x = 0; x < size; x++) {
            if(x % 2 != 0) {
                ofRect(x * size, pos - height, size, height);
            }
        }
    }
    masker.endMask(layer2);
}

void ofApp::drawAnim() {
    ofBackground(ofColor::black);
    masker.draw();
    masker.drawOverlay();
    
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
    if(key == 'o') {
        masker.toggleOverlay();
    }
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