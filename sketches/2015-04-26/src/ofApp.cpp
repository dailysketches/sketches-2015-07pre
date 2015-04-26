#include "ofApp.h"

/* This draws the animation */
void ofApp::setupAnim() {
    ofEnableAntiAliasing();
    ofEnableSmoothing();
    previousSineOfTheTime = 0;
    
    //Lines
    r = 20;
    ofSetLineWidth(4);
    
    //Perlin
    noiseOffset.x = ofRandomf();
    noiseOffset.y = ofRandomf();
    noiseOffset.z = ofRandomf();
    scaleX = 0.02, scaleY = 0.02;
}

void ofApp::updateAnim(){
    
}

void ofApp::drawAnim() {
    ofBackground(0, 0, 0);
    sineOfTheTime = sin(ofGetFrameNum() * 0.05);
    
    if(previousSineOfTheTime < 0 && sineOfTheTime >= 0 && renderMode && !renderingNow) {
        renderGif();
    }
    
    drawGrid();
    previousSineOfTheTime = sineOfTheTime;
}

void ofApp::drawGrid() {
    for(int i = 0; i < width * 0.1 + 10; i++) {
        for(int j = 0; j < height * 0.1 + 10; j++) {
            
            noise.x = noiseOffset.x + i * scaleX;
            noise.y = noiseOffset.y + j * scaleY;
            noise.z = noiseOffset.z + sineOfTheTime;
            noiseValue = ofNoise(noise.x, noise.y, noise.z);
            
            //http://natureofcode.com/book/chapter-3-oscillation#35-polar-vs-cartesian-coordinates
            theta = noiseValue * 2 * PI;
            x = r * cos(theta);
            y = r * sin(theta);
            
            ofPushMatrix();
            ofTranslate(i * 10, j * 10);
            ofEnableBlendMode(OF_BLENDMODE_ADD);
            if(j % 2 == 0){
                ofSetColor(180, 231, 248, 150);
                ofRect(0, 0, x, y);
            } else {
                ofSetColor(255, 180, 180, 128);
                ofLine(0, 0, x, y);
            }
            ofDisableBlendMode();
            ofPopMatrix();
        }
    }
}

/* This handles the setup and GIF rendering, etc */
void ofApp::setup(){
    //Gif render values
    renderMode = true;
    width = 700, height = 220;
    duration = .02, colors = 64;
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