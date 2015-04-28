#include "ofApp.h"

/* This draws the animation */
void ofApp::setupAnim() {
    gravity = ofVec2f(0, 0.2);
    running = true;
    stopping = save = resetting = trails = false;
    font.loadFont("LemonMilk.otf", 48);
    ofEnableSmoothing();
    ofEnableAntiAliasing();
}

void ofApp::updateAnim(){
    for(int i = 0; i < 12; i++) {
        createMover();
    }
    
    if(ofGetFrameNum() == 40) {
        trails = true;
    }
    
    if(ofGetFrameNum() == 80) {
        running = false;
        stopping = true;
    }
    
    if(ofGetFrameNum() == 94) {
        stopping = false;
        trails = false;
    }
    
    if(ofGetFrameNum() == 98 || ofGetFrameNum() == 108) {
        resetting = !resetting;
    }
    
    if(ofGetFrameNum() == 110) {
        save = true;
    }
    
    for(int i = 0; i < movers.size(); i++) {
        movers.at(i).applyForce(gravity);
        movers.at(i).update();
    }
}

void ofApp::drawAnim() {
    if(!trails) {
        ofSetHexColor(0x100643);
        ofRect(0, 0, width, height);
    }
    
    if(running) {
        for(int i = 0; i < movers.size(); i++) {
            movers.at(i).draw();
        }
    }
    
    if(stopping) {
        ofSetColor(ofColor::white);
        font.drawString("STOP", 70, 120);
    }
    
    if(resetting) {
        ofSetColor(ofColor::white);
        font.drawString("RESET", 64, 120);
    }
    
    if(save) {
        renderGif();
        movers.clear();
        save = !save;
    }
}

void ofApp::createMover() {
    minX = width * 0.4;
    maxX = width * 0.6;
    x = ofRandom(minX, maxX);
    
    minY = height * 0.1;
    maxY = height * 0.7;
    y = ofRandom(minY, maxY);
    
    color.setHsb(ofMap(y, minY, maxY, 0, 50), 255, 128);
    initial = ofVec2f(ofMap(x, minX, maxX, -3, 3), 0);
    
    PatternMover mover;
    mover.setup();
    mover.setColor(color);
    mover.setSize(3);
    mover.applyForce(initial);
    mover.setLocation(x, y);
    movers.push_back(mover);
}

/* This handles the setup and GIF rendering, etc */
void ofApp::setup(){
    //Gif render values
    renderMode = false;
    width = 300, height = 200;
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