#include "ofApp.h"

/* This draws the animation */
void ofApp::setupAnim() {
    ofEnableSmoothing();
    ofSetLineWidth(4);
    masker.setup(width, height);
    
    for(int i = 0; i < 70; i++) {
        ofxAnimatableFloat animHeight;
        animHeight.reset(ofRandom(40));
        heights.push_back(animHeight);
        
        ofxAnimatableFloat opacity;
        opacity.reset(ofMap(i, 0, 300, 100, 255));
        opacities.push_back(opacity);
        
        ofxAnimatableFloat target;
        target.reset(ceil(ofRandom(-height, height * 2)));
        targets.push_back(target);
        
        ofxAnimatableFloat position;
        position.reset(createDistinct(target.val()));
        position.setCurve(SWIFT_GOOGLE);
        position.setRepeatType(LOOP_BACK_AND_FORTH);
        position.setDuration(ceil(ofRandom(2)) * 2);
        position.animateTo(targets.at(i).val());
        positions.push_back(position);
    }
}

float ofApp::createDistinct(float from) {
    float candidate;
    do candidate = ceil(ofRandom(-height, height * 2));
    while(abs(candidate - from) < 150);
    return candidate;
}

void ofApp::updateAnim(){
    ofEnableAlphaBlending();
    
    masker.beginBackground();
    ofBackground(ofColor::black);
    ofSetColor(ofColor::white, 200);
    for(int i = -width; i < width*2; i+=30) {
        ofLine(i, height, i + width*0.5, 0);
    };
    masker.endBackground();
    
    masker.beginMask();
    ofBackground(ofColor::black);
    for(int i = 0; i < positions.size(); i++) {
        positions.at(i).update(0.05);
        ofSetColor(ofColor::white, opacities.at(i).val());
        ofRect(0, positions.at(i).val(), width, heights.at(i).val());
    }
    masker.endMask();
    
    masker.beginForeground();
    ofBackground(ofColor::black);
    ofSetColor(ofColor::white, 100);
    for(int i = -width; i < width*2; i+=15) {
        ofLine(i + width*0.5, height, i, 0);
    };
    masker.endForeground();
    
    ofDisableAlphaBlending();
}

void ofApp::drawAnim() {
    masker.draw();
    bool allFinished = true;
    for(int i = 0; i < positions.size(); i++) {
        if(positions.at(i).getPlayCount() < 2) {
            allFinished = false;
        }
    }
    if(allFinished) renderGif();
}

/* This handles the setup and GIF rendering, etc */
void ofApp::setup(){
    //Gif render values
    slowMode = false;
    width = 400, height = 300;
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