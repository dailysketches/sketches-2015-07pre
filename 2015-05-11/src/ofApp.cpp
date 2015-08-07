#include "ofApp.h"

/* This draws the animation */
void ofApp::setupAnim() {
    halfWidth = width * 0.5;
    halfHeight = height * 0.5;
    
    ofSetWindowShape(width, height);
    masker.setup(width, height);
    
    setupBackground();
    setupMask();
    setupForeground();
    
    ofSetCircleResolution(60);
}

void ofApp::setupBackground(){
    for(int i = 0; i < width; i+=40) {
        for(int j = 0; j < height; j+=40) {
            ofxShape shape;
            shape.setupFilledSquare(26);
            shape.positionX(i+10);
            shape.positionY(j+10);
            shape.setBlur(10);
            backgroundShapes.push_back(shape);
        }
    }
    
    push(&backgroundShapes, &backgroundSystems);
}

void ofApp::setupMask(){
    for(int i = -width; i < width*2; i+=40) {
        for(int j = -width; j < height*2; j+=40) {
            ofxShape shape;
            shape.setupFilledSquare(26);
            shape.positionX(i+10);
            shape.positionY(j+10);
            shape.setBlur(10);
            maskShapes.push_back(shape);
        }
    }
    
    push(&maskShapes, &maskSystems);
}

void ofApp::setupForeground(){
    for(int i = 0; i < width; i+=40) {
        for(int j = 0; j < height; j+=40) {
            ofxShape shape;
            shape.setupFilledSquare(26);
            shape.positionX(i+30);
            shape.positionY(j+30);
            shape.setBlur(10);
            foregroundShapes.push_back(shape);
        }
    }
    
    push(&foregroundShapes, &foregroundSystems);
}

void ofApp::updateAnim(){
    float scale = ofMap(sin(ofGetFrameNum() * 0.08), -1, 1, -54, 54);
    for(int i = 0; i < maskShapes.size(); i++){
        maskShapes.at(i).positionZ(scale);
    }
}

void ofApp::drawAnim() {
    masker.beginBackground();
    draw(&backgroundSystems);
    masker.endBackground();
    
    masker.beginMask();
    draw(&maskSystems);
    masker.endMask();
    
    masker.beginForeground();
    draw(&foregroundSystems);
    masker.endForeground();
    
    masker.draw();
    
    if(ofGetFrameNum() == 78) {
        renderGif();
    }
}

void ofApp::push(vector<ofxShape> *shapes, vector<ofxShapeSystem> *systems) {
    ofxShapeSystem system;
    for(int i = 0; i < shapes->size(); i++) {
        system.add(shapes->at(i));
    }
    systems->push_back(system);
}

void ofApp::draw(vector<ofxShapeSystem> *systems) {
    ofClear(0, 0, 0, 255);
    for(int i = 0; i < systems->size(); i++) {
        systems->at(i).draw();
    }
}

/* This handles the setup and GIF rendering, etc */
void ofApp::setup(){
    //Gif render values
    slowMode = false;
    width = 500, height = 180;
    duration = 0.2, colors = 256;
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
    ofClear(0, 0, 0, 255);
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