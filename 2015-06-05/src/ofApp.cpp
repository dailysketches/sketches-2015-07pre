#include "ofApp.h"

//Pattern based on http://www.openprocessing.org/sketch/157035

/* This draws the animation */
void ofApp::setupAnim() {
    masker.setup(width, height);
    layerId = masker.newLayer();
    
    ofDisableArbTex();
    offset.x = ofRandom(30);
    offset.y = ofRandom(30);
    movingLeft = true;
    setupImage("surface.png", &img, &tex);

    plane.set(width, height);
    plane.setPosition(halfWidth, halfHeight, 0);
    plane.setResolution(2, 2);
}

void ofApp::setupImage(string file, ofImage *img, ofTexture *tex) {
    img->loadImage(file);
    *tex = img->getTextureReference();
    tex->setTextureWrap(GL_MIRRORED_REPEAT, GL_MIRRORED_REPEAT);
}

void ofApp::drawLayer(ofTexture *tex) {
    plane.mapTexCoords(tx0, ty0, tx1, ty1);
    plane.mapTexCoords(tx1, ty1, tx0, ty0);
    tex->bind();
    plane.draw();
    tex->unbind();
}

void ofApp::updateAnim(){
    masker.beginLayer(layerId);
    ofBackground(ofColor::black);
    ofSetColor(ofColor::red);
    tx0 = offset.x + (movingLeft ? ofGetFrameNum() : -ofGetFrameNum()) * 0.0005;
    ty0 = offset.y;
    tx1 = tx0 - 0.16666667;
    ty1 = ty0 - 1;
    drawLayer(&tex);
    masker.endLayer(layerId);
    
    masker.beginMask(layerId);
    ofBackground(ofColor::black);
    for(int i = 0; i < 8; i++) {
        ofSetColor(ofColor::white, ofRandom(32));
        ofRotateZ(ofRandom(360));
        ofRect(-width*2, ofRandom(height), width*4, ofRandom(halfHeight, height));
    }
    masker.endMask(layerId);

    if(ofRandom(1) > 0.5) {
        offset.x = ofRandom(30);
        offset.y = ofRandom(30);
        movingLeft = !movingLeft;
    }
}

void ofApp::drawAnim() {
    if(ofGetFrameNum() == 0) ofBackground(ofColor::black);
    ofSetColor(ofColor::white, 40);
    drawLayer(&tex);
    masker.draw();
    if(ofGetFrameNum() == 72) {
        renderGif();
    }
}

/* This handles the setup and GIF rendering, etc */
void ofApp::setup(){
    //Gif render values
    slowMode = false;
    paused = false;
    width = 500, height = 340;
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