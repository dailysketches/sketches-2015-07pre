#include "ofApp.h"

/* This draws the animation */
void ofApp::setupAnim() {
    paused = true;
    numLayers = 9;
    topLayer = numLayers - 1;
    spacing = 100;
    thickness = 50;
    offset = 0;
    increment = 2;
    masker.setup(numLayers);
    //masker.toggleOverlay();
    
    image.setup("surface.png", width, height, 1, TEXTURE_OFFSET_BOTTOM_LEFT);
    image.incrementTextureOffsetY(0.5);
}

void ofApp::updateAnim(){
    incrementOffset();

    for(int i = 0; i < numLayers - 1; i++) {
        masker.beginLayer(i);
        ofBackground(ofColor(0, 0, 0, 0));
        hue = ofMap(i, 0, numLayers, 20, 140);
        ofSetColor(ofColor::fromHsb(hue, 255, 255, 240));
        rotateScreen(i * 45);
        drawLines();
        masker.endLayer(i);
        
        masker.beginMask(i);
        ofBackground(ofColor::black);
        ofSetColor(ofColor::white);
        rotateScreen(i * 45);
        rotateScreen(90);
        drawLines();
        rotateScreen(-90);
        masker.endMask(i);
    }
    
    masker.beginLayer(topLayer);
    masker.draw();
    masker.endLayer(topLayer);
    
    masker.beginMask(topLayer);
    ofSetColor(ofColor::white);
    image.incrementTextureOffsetX(0.02857142857);
    image.draw();
    rotateScreen(180);
    image.draw();
    rotateScreen(90);
    image.draw();
    rotateScreen(180);
    image.draw();
    masker.endMask(topLayer);
    
}

void ofApp::drawAnim() {
    if(ofGetFrameNum() == spacing) {
        paused = false;
    }
    ofBackground(ofColor::black);
    masker.drawLayer(topLayer);
    
    masker.drawOverlay();
    if(ofGetFrameNum() == spacing + (spacing / increment)) {
        renderGif();
    }
}

void ofApp::incrementOffset() {
    offset+=increment;
    if(offset >= spacing) {
        offset = 0;
    }
}

void ofApp::drawLines() {
    for(int y = -height; y < doubleHeight; y += spacing) {
        ofRect(-width, y + offset, tripleWidth, thickness);
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
    width = 500, height = 500;
    duration = 0.2, colors = 256;
    saveOnFrame = -1;

    filename = ofGetTimestampString("%Y-%m-%d") + ".gif";
    framerate = slowMode ? 5 : 10;
    halfWidth = width * 0.5;
    halfHeight = height * 0.5;
    doubleWidth = width * 2;
    doubleHeight = height * 2;
    tripleWidth = width * 3;
    tripleHeight = height * 3;

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