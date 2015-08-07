#include "ofApp.h"

/* This draws the animation */
void ofApp::setupAnim() {
    ofEnableSmoothing();
    masker.setup(width, height);
    offset = ofRandom(3);
    offset2 = ofRandom(3);
    shift = false;
    numShifts = 0;
    numFramesSinceShift = 0;

    ofDisableArbTex();
    setupImage("road.png", &img1, &tex1);
    setupImage("face.png", &img2, &tex2);

    plane.set(width, height);
    plane.setPosition(width * 0.5, height * 0.5, 0);
    plane.setResolution(2, 2);
}

void ofApp::setupImage(string file, ofImage *img, ofTexture *tex) {
    img->loadImage(file);
    *tex = img->getTextureReference();
    tex->setTextureWrap(GL_MIRRORED_REPEAT, GL_MIRRORED_REPEAT);
}

void ofApp::updateAnim(){
    if(!shift && numFramesSinceShift > 5 && ofRandom(1) < 0.35) {
        numShifts++;
        numFramesSinceShift = 0;
        shift = true;
    }
    
    masker.beginBackground();
    ofBackground(0, 0, 0, 255);
    shift ? ofSetColor(128, 128, 128, 64) : ofSetColor(ofColor::red);
    applyOffset = shift ? offset2 : offset;
    tx0 = 1;
    ty0 = ofGetFrameNum() * 0.0012 + applyOffset;
    tx1 = tx0 - 1;
    ty1 = ty0 - 0.2;
    shift ? drawLayer(&tex1) : drawLayer(&tex2);
    masker.endBackground();
    
    masker.beginMask();
    ofBackground(0, 0, 0, 255);
    ofSetColor(ofColor::white);
    applyOffset = shift ? offset : offset2;
    tx0 = 1;
    ty0 = ofGetFrameNum() * 0.0012 + applyOffset;
    tx1 = tx0 - 1;
    ty1 = ty0 - 0.2;
    shift ? drawLayer(&tex2) : drawLayer(&tex1);
    masker.endMask();
    
    masker.beginForeground();
    ofBackground(0, 0, 0, 255);
    ofSetColor(ofColor::white);
    applyOffset = shift ? offset2 : offset;
    tx0 = 1;
    ty0 = ofGetFrameNum() * 0.0012 + applyOffset;
    tx1 = tx0 - 1;
    ty1 = ty0 - 0.2;
    shift ? drawLayer(&tex1) : drawLayer(&tex2);
    masker.endForeground();
    
    if(shift && numFramesSinceShift > 0 && ofRandom(1) < 0.5) {
        shift = false;
        numFramesSinceShift = 0;
        offset = getNewOffset();
        if(ofGetFrameNum() > 80) renderGif();
    }
    
    numFramesSinceShift++;
}

void ofApp::drawAnim() {
    ofBackground(0, 0, 0);
    ofSetColor(ofColor::white);
    ofEnableAlphaBlending();
    masker.draw();
    ofDisableAlphaBlending();
}

float ofApp::getNewOffset() {
    do {
        candidateOffset = ofRandom(3);
    } while(abs(candidateOffset - offset) < 0.4);
    
    return candidateOffset;
}

void ofApp::drawLayer(ofTexture *tex) {
    plane.mapTexCoords(tx0, ty0, tx1, ty1);
    plane.mapTexCoords(tx1, ty1, tx0, ty0);
    tex->bind();
    plane.draw();
    tex->unbind();
}

/* This handles the setup and GIF rendering, etc */
void ofApp::setup(){
    //Gif render values
    slowMode = false;
    width = 400, height = 400;
    duration = 0.2, colors = 32;
    saveOnFrame = -1;

    filename = ofGetTimestampString("%Y-%m-%d") + ".gif";
    framerate = slowMode ? 5 : 10;
    
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
    ofSetColor(255, 255, 255, 160);
    ofRect(16, height - 64, 330, 32);
    ofSetColor(0, 0, 0, 255);
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