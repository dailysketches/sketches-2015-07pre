#include "ofApp.h"

/* This draws the animation */
void ofApp::setupAnim() {
    ofEnableSmoothing();
    masker.setup(width, height);
    fadeIn = true;
    fadeOut = false;
    alpha = 255;

    ofDisableArbTex();
    setupImage("tissue-inverted.png", &img1, &tex1, &offset1);
    setupImage("road.png", &img2, &tex2, &offset2);

    plane.set(width, height);
    plane.setPosition(width * 0.5, height * 0.5, 0);
    plane.setResolution(2, 2);
}

void ofApp::updateAnim(){
    masker.beginBackground();
    ofBackground(0, 0, 0, 255);
    masker.endBackground();
    
    masker.beginMask();
    ofEnableAlphaBlending();
    ofBackground(0, 0, 0, 255);
    ofSetColor(ofColor::white);
    
    ofTranslate(0, 0, 250);
    ofBackground(255, 255, 255);
    for(int i = 0; i < 360; i+= 1) {
        rotateScreen(i);
        drawLayer(&tex1);
    }
    ofDisableAlphaBlending();
    masker.endMask();
    
    masker.beginForeground();
    ofBackground(0, 0, 0, 255);
    ofSetColor(ofColor(62, 225, 255));
    tx0 = -ofGetFrameNum() * 0.030 + offset2;
    ty0 = -ofGetFrameNum() * 0.030 + offset2;
    tx1 = tx0 + (ofGetFrameNum() * 0.030 + offset2) * 2;
    ty1 = ty0 + (ofGetFrameNum() * 0.030 + offset2) * 2;
    drawLayer(&tex2);
    masker.endForeground();
}

void ofApp::drawAnim() {
    ofBackground(0, 0, 0);
    ofSetColor(ofColor::white);
    ofEnableAlphaBlending();
    masker.draw();
    
    if(fadeIn) {
        alpha -= 24;
        if(alpha <= 0) fadeIn = false;
    }
    
    if(fadeOut) {
        alpha += 24;
        if(alpha >= 300) renderGif();
    }
    
    ofSetColor(0, 0, 0, alpha);
    ofRect(0, 0, width, height);

    if(ofGetFrameNum() == 60) {
        fadeOut = true;
    }
    ofDisableAlphaBlending();
}

void ofApp::drawLayer(ofTexture *tex) {
    tx0 = -0.35;
    ty0 = ofGetFrameNum() * 0.0128 + offset1;
    tx1 = tx0 + 3;
    ty1 = ty0 + 1.5;
    plane.mapTexCoords(tx0, ty0, tx1, ty1);
    plane.mapTexCoords(tx1, ty1, tx0, ty0);
    tex->bind();
    plane.draw();
    tex->unbind();
}

void ofApp::setupImage(string file, ofImage *img, ofTexture *tex, float *offset) {
    img->loadImage(file);
    *tex = img->getTextureReference();
    tex->setTextureWrap(GL_MIRRORED_REPEAT, GL_MIRRORED_REPEAT);
    *offset = ofRandom(1);
}

void ofApp::rotateScreen(float degrees) {
    ofTranslate(halfWidth, halfHeight, 0);
    ofRotate(degrees);
    ofTranslate(-halfWidth, -halfHeight, 0);
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