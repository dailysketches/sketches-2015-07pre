#include "ofApp.h"

/* This draws the animation */
void ofApp::setupAnim() {
    masker.setup();
    layer1 = masker.newLayer();
    image1.setup("cardboard.png", width, height, 1, TEXTURE_OFFSET_MIDDLE_CENTER);
    image2.setup("cardboard-mask.png", width, height, 1, TEXTURE_OFFSET_MIDDLE_CENTER);
}

void ofApp::updateAnim(){
    masker.beginLayer(layer1);
    {
        ofBackground(ofColor::black);
        ofSetColor(ofColor::white);
        image1.incrementTextureOffsetY(0.02);
        image1.draw();
    }
    masker.endLayer(layer1);

    masker.beginMask(layer1);
    {
        ofBackground(ofColor::black);
        ofSetColor(ofColor::white);
        image2.incrementTextureOffsetY(-0.02);
        image2.draw();
    }
    masker.endMask(layer1);
}

void ofApp::drawAnim() {
    ofBackground(ofColor::black);
    ofSetColor(ofColor::white);
    masker.draw();
    if(ofGetFrameNum() == 100) {
        renderGif();
    }
}

/* This handles the setup and GIF rendering, etc */
void ofApp::setup(){
    //Gif render values
    slowMode = false;
    paused = false;
    fullscreen = false;
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
    ofSetWindowPosition(0, 0);
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
    ofSetFullscreen(fullscreen);
    updateAnim();
}

void ofApp::draw(){
    fbo.begin();
    drawAnim();
    fbo.end();

    if(!renderingNow && !paused) {
        captureFrame();
    }

    //Draw FBO
    ofPushMatrix();
    ofPushStyle();
    {
        ofBackground(ofColor::black);
        ofSetColor(ofColor::white);
        fbo.draw(0, 0);
    }
    ofPopStyle();
    ofPopMatrix();

    ofSetColor(ofColor::white);
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
    if(key == 't') {
        showTimeline = !showTimeline;
    } else if(key == 'f') {
        fullscreen = !fullscreen;
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