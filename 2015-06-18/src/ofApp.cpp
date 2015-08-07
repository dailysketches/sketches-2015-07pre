#include "ofApp.h"

/* This draws the animation */
void ofApp::setupAnim() {
    masker.setup();
    layer1 = masker.newLayer();
    layer2 = masker.newLayer();
    layer3 = masker.newLayer();

    leafVertical.setup("leaf-vertical.png", 2, TEXTURE_OFFSET_BOTTOM_RIGHT);
    leafDiagonal.setup("leaf-diagonal.png", 2, TEXTURE_OFFSET_BOTTOM_RIGHT);
    leafStar.setup("leaf-star.png", 2, TEXTURE_OFFSET_MIDDLE_CENTER);
    
    layer1Alpha = 0;
    layer2Alpha = 0;
    layer3Alpha = 0;
}

void ofApp::updateAnim() {
    masker.beginLayer(layer1);
    {
        ofSetColor(ofColor::white);
        leafVertical.incrementTextureScale(0.02);
        leafVertical.incrementTextureOffset(0.01, 0.025);
        leafVertical.draw();
    }
    masker.endLayer(layer1);

    masker.beginMask(layer1);
    {
        ofBackground(ofColor::black);
        ofSetColor(ofColor::white, animateAlpha(0, 13, layer1Alpha));
        ofRect(0, 0, width, height);
    }
    masker.endMask(layer1);
    
    masker.beginLayer(layer2);
    {
        ofSetColor(ofColor::white);
        if(ofGetFrameNum() > 21) {
            leafDiagonal.incrementTextureScale(-0.04);
            leafDiagonal.incrementTextureOffset(0.016, 0.016);
        }
        leafDiagonal.draw();
    }
    masker.endLayer(layer2);
    
    masker.beginMask(layer2);
    {
        ofBackground(ofColor::black);
        ofSetColor(ofColor::white, animateAlpha(21, 39, layer2Alpha));
        ofRect(0, 0, width, height);
    }
    masker.endMask(layer2);
    
    masker.beginLayer(layer3);
    {
        ofSetColor(ofColor::white);
        if(ofGetFrameNum() > 36) {
            leafStar.incrementTextureScale(-0.04);
            leafStar.incrementTextureOffset(0.001, 0.001);
        }
        leafStar.draw();
    }
    masker.endLayer(layer3);
    
    masker.beginMask(layer3);
    {
        ofBackground(ofColor::black);
        ofSetColor(ofColor::white, animateAlpha(36, 50, layer3Alpha));
        ofRect(0, 0, width, height);
    }
    masker.endMask(layer3);
}

void ofApp::drawAnim() {
    ofBackground(ofColor::black);
    ofSetColor(ofColor::white);

    masker.draw();
    masker.drawOverlay();

    if(ofGetFrameNum() > 40 && layer3Alpha <= 0) {
        renderGif();
    }
}

float ofApp::animateAlpha(int fromFrame, int toFrame, float &alpha) {
    if(ofGetFrameNum() > fromFrame && ofGetFrameNum() <= toFrame && alpha < 255) {
        alpha += 30;
    }
    
    if(ofGetFrameNum() > toFrame && alpha > 0) {
        alpha -= 30;
    }
    
    return alpha;
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