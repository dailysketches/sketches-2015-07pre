#include "ofApp.h"

/* This draws the animation */
void ofApp::setupAnim() {
    ofDisableArbTex();
    
    img.loadImage("tissue.png");
    texture = img.getTextureReference();
    texture.setTextureWrap(GL_MIRRORED_REPEAT, GL_MIRRORED_REPEAT);
    
    offset = ofRandom(1);
    shift = false;
    numShifts = 0;
    
    //Position the planes to take up the full screen
    for(int i = 0; i < 2; i++) {
        planes.push_back(plane);
        planes.at(i).set(ofGetHeight(), ofGetWidth());
        planes.at(i).setPosition(ofGetWidth() * 0.5, ofGetHeight() * 0.5, 0);
        planes.at(i).setResolution(2, 2);
    }
}

void ofApp::updateAnim(){
    if(!shift && ofRandom(1) < 0.15) {
        numShifts++;
        shift = true;
        offset = getNewOffset();
    }
    
    tx0 = 0 * offset * 0.1;
    ty0 = offset + ofGetFrameNum() * 0.001;
    tx1 = tx0 + 1;
    ty1 = ty0 + 2;
    
    //Position the texture on the plane
    planes.at(0).mapTexCoords(tx0, ty0, tx1, ty1);
    planes.at(1).mapTexCoords(tx1, ty1, tx0, ty0);
}

void ofApp::drawAnim() {
    ofBackground(0, 0, 0);
    
    if(shift) {
        if(ofRandom(1) > 0.2) shift = false;
    } else {
        texture.bind();
        for(int i = 0; i < planes.size(); i++) {
            planes.at(i).draw();
        }
        texture.unbind();
    }
}

float ofApp::getNewOffset() {
    do {
        candidateOffset = ofRandom(1);
    } while(abs(candidateOffset - offset) < 0.2);
    
    return candidateOffset;
}

/* This handles the setup and GIF rendering, etc */
void ofApp::setup(){
    //Gif render values
    renderMode = true;
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
        
        if(numShifts == 15) {
            renderGif();
        }
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