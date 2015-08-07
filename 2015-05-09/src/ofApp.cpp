#include "ofApp.h"

/* This draws the animation */
void ofApp::setupAnim() {
    masker.setup(width, height);
    
    ringSize = 15;
    lineDistance = height * 0.06;
    lineThickness = height * 0.02;
    
    setupBackground();
    setupMask();
    setupForeground();
}

void ofApp::setupBackground(){
    for(int i = 0; i < 3; i++) {
        ofxShape shape;
        shape.setupFilledSquare(ofRandom(3, 28));
        shape.scaleX(ofRandom(3, 28));
        shape.scaleY(ofRandom(3, 28));
        shape.positionX(ofRandom(-28, width + 28));
        shape.positionY(ofRandom(-28, height + 28));
        shape.setBlur(1);
        shape.setOpacity(58);
        backgroundShapes.push_back(shape);
    }
    
    push(&backgroundShapes, &backgroundSystems);
}

void ofApp::setupMask(){
    for(int i = 0; i < 500; i++) {
        float x = ofRandom(-ringSize, width + ringSize);
        float y = ofRandom(-ringSize, height + ringSize);
        float z = ofRandom(-100, 100);
        ofxShape shape;
        shape.setupGradientRing(60, -4.6, ringSize);
        shape.setPosition(ofVec3f(x, y, z));
        shape.setBlur(ringSize * 0.5);
        shape.setOpacity(ofRandom(60, 200));
        maskShapes.push_back(shape);
        shape.setDiameter(ringSize * 0.5);
        shape.setThickness(4.6);
        maskShapes.push_back(shape);
    }
    
    push(&maskShapes, &maskSystems);
}

void ofApp::setupForeground(){
    //Background color
    ofxShape shape;
    shape.setupFilledSquare(width);
    shape.setColor(ofColor::red);
    shape.positionX(width * 0.5);
    shape.positionY(height * 0.5);
    foregroundShapes.push_back(shape);
    
    //Lines
    for(int i = 0; i < height; i += lineDistance) {
        ofxShape shape;
        shape.setupFilledSquare(lineThickness);
        shape.scaleX(height);
        shape.setColor(ofColor::blue);
        shape.positionY(i);
        shape.setBlur(lineThickness);
        foregroundShapes.push_back(shape);
    }
    
    //Color filter
    shape.setupFilledSquare(width);
    shape.rotateZ(-38);
    shape.scaleY(3);
    shape.positionX(-250);
    shape.setColor(ofColor::purple);
    shape.setBlur(270);
    shape.setOpacity(220);
    foregroundShapes.push_back(shape);
    shape.positionX(500);
    foregroundShapes.push_back(shape);
    
    push(&foregroundShapes, &foregroundSystems);
}

void ofApp::updateAnim(){
    for(int i = 0; i < maskShapes.size(); i += 2) {
        float y = 5 + maskShapes.at(i).getPosition().y;
        if(y > height) {
            y -= height;
        }
        maskShapes.at(i    ).positionY(y);
        maskShapes.at(i + 1).positionY(y);
    }
    
    for(int i = 1; i < foregroundShapes.size() - 2; i++) {
        float y = foregroundShapes.at(i).getPosition().y - (lineDistance * 0.04);
        if(y < -lineThickness) y = height;
        foregroundShapes.at(i).positionY(y);
    }
}

void ofApp::drawAnim() {
    ofBackground(0, 0, 0, 255);
    
    masker.beginBackground();
    draw(&backgroundSystems);
    masker.endBackground();
    
    masker.beginMask();
    ofRotateX(30);
    ofRotateY(12);
    ofRotateZ(-32);
    ofTranslate(-300, -130);
    ofScale(2, 2);
    draw(&maskSystems);
    masker.endMask();
    
    masker.beginForeground();
    draw(&foregroundSystems);
    masker.endForeground();
    
    masker.draw();
    
    if(ofGetFrameNum() == 100) {
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
    width = 500, height = 500;
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