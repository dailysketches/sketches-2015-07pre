#include "ofApp.h"

/* This draws the animation */
void ofApp::setupAnim() {
    masker.setup(2);
    image1.setup("texture1.png");
    image2.setup("foil.png", 0.5);
    degrees = rotation = 0;
    paused = true;
}

void ofApp::updateAnim(){
    if(ofGetFrameNum() % 5 == 0) {
        degrees += 90;
        image1.setTextureOffset(ofRandom(2), ofRandom(2));
        image1.setTextureScale(ofRandom(1, 2));
        scaleIncrement = ofRandom(1) > 0.5 ? 0.3 : -0.3;
        translateIncrement.x = ofRandom(1) > 0.5 ? 0.5 : -0.5;
        translateIncrement.y = ofRandom(1) > 0.5 ? 0.05 : -0.05;
        pointIncrement1.x = ofRandom(1) > 0.5 ? 16 : -8;
        pointIncrement1.y = ofRandom(1) > 0.5 ? 8 : -16;
        pointIncrement2.x = ofRandom(1) > 0.5 ? 16 : -8;
        pointIncrement2.y = ofRandom(1) > 0.5 ? 8 : -16;
        pointIncrement3.x = ofRandom(1) > 0.5 ? 16 : -8;
        pointIncrement3.y = ofRandom(1) > 0.5 ? 8 : -16;
        randomTriangle(triangle1);
        randomTriangle(triangle2);
        randomTriangle(triangle3);
    }
    
    image1.incrementTextureScale(scaleIncrement);
    image1.incrementTextureOffset(translateIncrement);
    image2.incrementTextureOffsetY(0.02);
    for(int i = 0; i < 3; i++) {
        triangle1.at(i) += pointIncrement1;
        triangle2.at(i) += pointIncrement2;
        triangle3.at(i) += pointIncrement3;
    }
    
    masker.beginLayer(0);
    {
        drawGradientBackground();
    }
    masker.endLayer(0);
    
    masker.beginMask(0);
    {
        ofPushStyle();
        {
            ofBackground(ofColor::white);
            ofSetColor(ofColor::black);
            drawTriangle(triangle1);
            drawTriangle(triangle2);
            drawTriangle(triangle3);
        }
        ofPopStyle();
    }
    masker.endMask(0);
    
    masker.beginLayer(1);
    {
        rotation += 4;
        rotateScreen(rotation);
        ofSetColor(ofColor::red, ofGetFrameNum() == 0 ? 255 : 110);
        image1.draw();
    }
    masker.endLayer(1);
    
    masker.beginMask(1);
    {
        ofBackground(ofColor::black);
        masker.drawLayer(0);
    }
    masker.endMask(1);
}

void ofApp::drawAnim() {
    if(ofGetFrameNum() == 0) {
        ofBackground(ofColor::black);
    }
    ofSetColor(ofColor::red, ofGetFrameNum() == 0 ? 255 : 128);
    image2.draw();

    ofSetColor(ofColor::black, 128);
    ofRect(0, 0, width, height);

    ofPushMatrix();
    {
        masker.draw();
    }
    ofPopMatrix();
    masker.drawOverlay();
    
    if(ofGetFrameNum() == 100) {
        paused = false;
    }
    
    if(ofGetFrameNum() == 200) {
        renderGif();
    }
}

void ofApp::drawTriangle(vector<ofPoint> &triangle) {
    ofBeginShape();
    for(int i = 0; i < 3; i++) {
        ofVertex(triangle.at(i).x, triangle.at(i).y);
    }
    ofEndShape();
}

void ofApp::drawGradientBackground() {
    rotateScreen(degrees);
    ofBackground(ofColor::black);
    ofBackgroundGradient(ofColor::white, ofColor::black, OF_GRADIENT_LINEAR);
}

void ofApp::randomTriangle(vector<ofPoint> &triangle) {
    triangle.clear();
    for(int i = 0; i < 3; i++) {
        triangle.push_back(ofPoint(ofRandom(-width, doubleWidth), ofRandom(-height, doubleHeight)));
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