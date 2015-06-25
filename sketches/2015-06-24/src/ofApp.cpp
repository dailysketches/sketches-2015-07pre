#include "ofApp.h"

/* This draws the animation */
void ofApp::setupAnim() {
    paused = true;
    numLayers = 6;
    topLayer1 = numLayers - 2;
    topLayer2 = numLayers - 1;
    spacing = 100;
    offset = offset2 = 0;
    increment = 20;
    masker.setup(numLayers);
    
    image.setup("surface.png", width, height, 1, TEXTURE_OFFSET_BOTTOM_LEFT);
    image.incrementTextureOffsetY(0.5);
}

void ofApp::updateAnim(){
    incrementOffset();
    
    for(int i = 0; i < numLayers - 2; i++) {
        masker.beginLayer(i);
        {
            ofBackground(ofColor(ofColor::black, 0));
            hue = ofMap(i, 0, numLayers, 20, 140);
            ofSetColor(ofColor::fromHsb(hue, 255, 255, 240));
            thickness = ofMap(sin(ofGetFrameNum() * 0.01), -1, 1, 10, 50);
            ofTranslate(0, i * 10);
            drawLines(offset, spacing, thickness);
        }
        masker.endLayer(i);
        
        masker.beginMask(i);
        {
            ofBackground(ofColor::black);
            ofSetColor(ofColor::white);
            thickness = ofMap(sin(ofGetFrameNum() * 0.1), -1, 1, 10, 70);
            ofTranslate(0, i * 10);
            drawLines(offset2, spacing, thickness);
        }
        masker.endMask(i);
    }
    
    masker.beginLayer(topLayer1);
    image.draw();
    masker.endLayer(topLayer1);
    
    masker.beginLayer(topLayer2);
    rotateScreen(90);
    image.draw();
    masker.endLayer(topLayer2);
}

void ofApp::drawAnim() {
    ofPushMatrix();
    {
        ofSetColor(ofColor::black, 20);
        ofRect(0, 0, width, height);
        masker.drawLayers(0, 4);
        ofScale(0.5, 0.5);
        rotateScreen(90);
        
        masker.drawLayer(2);
        
        masker.draw();
        ofScale(0.5, 0.5);
        rotateScreen(90);
        
        masker.drawLayer(1);
    }
    ofPopMatrix();
    masker.drawLayer(5);
    masker.drawOverlay();
    
    if(ofGetFrameNum() == 92) {
        paused = false;
    }
    
    if(ofGetFrameNum() == 162) {
        renderGif();
    }
}

void ofApp::incrementOffset() {
    offset+=increment;
    if(offset >= spacing) {
        offset = 0;
    }
    
    offset2-=increment;
    if(offset2 <= -spacing) {
        offset2 = 0;
    }
}

void ofApp::drawLines(float _offset, float _spacing, float _thickness) {
    for(int y = -height; y < doubleHeight; y += _spacing) {
        ofRect(-width, y + _offset, tripleWidth, _thickness);
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
    width = 400, height = 400;
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