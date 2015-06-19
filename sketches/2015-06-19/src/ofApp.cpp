#include "ofApp.h"

/* This draws the animation */
void ofApp::setupAnim() {
    timeline.setOutPointAtFrame(48);
    timeline.addCurves("layer-1-alpha", ofRange(0, 255));
    timeline.addCurves("layer-2-alpha", ofRange(0, 255));
    timeline.addCurves("layer-3-alpha", ofRange(0, 255));
    timeline.addCurves("layer-1-scale", ofRange(1, 4));
    timeline.addCurves("layer-2-scale", ofRange(1, 4));
    timeline.addCurves("layer-3-scale", ofRange(1, 4));
    timeline.addCurves("layer-1-x", ofRange(0, 1));
    timeline.addCurves("layer-1-y", ofRange(0, 1));
    timeline.addCurves("layer-2-x", ofRange(0, 1));
    timeline.addCurves("layer-2-y", ofRange(0, 1));
    timeline.addCurves("layer-3-x", ofRange(0, 1));
    timeline.addCurves("layer-3-y", ofRange(0, 1));
    timeline.togglePlay();

    leafVertical.setup("leaf-vertical.png", width, height, 2, TEXTURE_OFFSET_BOTTOM_RIGHT);
    leafDiagonal.setup("leaf-diagonal.png", width, height, 2, TEXTURE_OFFSET_BOTTOM_RIGHT);
    leafStar.setup("leaf-star.png", width, height, 2, TEXTURE_OFFSET_MIDDLE_CENTER);
    planes.push_back(&leafVertical);
    planes.push_back(&leafDiagonal);
    planes.push_back(&leafStar);

    masker.setup(width, height);
    masker.newLayer();
    masker.newLayer();
    masker.newLayer();
}

void ofApp::updateAnim(){
    for(int i = 0; i < planes.size(); i++) {
        ID = ofToString(i+1);
        alpha = timeline.getValue("layer-" + ID + "-alpha");
        scale = timeline.getValue("layer-" + ID + "-scale");
        position.x = timeline.getValue("layer-" + ID + "-x");
        position.y = timeline.getValue("layer-" + ID + "-y");
        masker.beginLayer(i);
        {
            ofSetColor(ofColor::white);
            planes.at(i)->setTextureScale(scale);
            planes.at(i)->setTexturePosition(position.x, position.y);
            planes.at(i)->draw();
        }
        masker.endLayer(i);
        
        masker.beginMask(i);
        {
            ofBackground(ofColor::black);
            ofSetColor(ofColor::white, alpha);
            ofRect(0, 0, width, height);
        }
        masker.endMask(i);
    }
}

void ofApp::drawAnim() {
    ofBackground(ofColor::black);
    ofSetColor(ofColor::white);
    masker.draw();
    if(ofGetFrameNum() == 48) {
        renderGif();
    }
}

/* This handles the setup and GIF rendering, etc */
void ofApp::setup(){
    //Gif render values
    slowMode = false;
    paused = false;
    fullscreen = true;
    ofSetFullscreen(fullscreen);
    ofSetFullscreen(false);
    ofSetFullscreen(fullscreen);
    width = 500, height = 500;
    duration = 0.2, colors = 256;
    saveOnFrame = -1;

    filename = ofGetTimestampString("%Y-%m-%d") + ".gif";
    framerate = slowMode ? 5 : 10;
    halfWidth = width * 0.5;
    halfHeight = height * 0.5;

    //Timeline values
    timeline.setup();
    timeline.setFrameBased(true);
    timeline.setWidth(ofGetWidth() - width - 100);
    showTimeline = true;

    //Init
    ofSetFrameRate(framerate);
    ofSetWindowShape(1600, 1000);
    ofSetWindowPosition(0, 0);
    gifEncoder.setup(width, height, duration, colors);
    renderingNow = false;
    renderMessage = "";
    
    fbo.allocate(width, height, GL_RGB);
    fbo.begin();
    ofClear(255, 255, 255, 0);
    fbo.end();

    //Begin patch
    setupAnim();
    masker.toggleOverlay();
}

void ofApp::update(){
    ofSetFullscreen(fullscreen);
    updateAnim();
}

void ofApp::draw(){

    fbo.begin();
    drawAnim();
    fbo.end();

    if(!renderingNow && !paused) {
        captureFrame();
    }

    //Draw FBO
    ofPushMatrix();
    ofPushStyle();
    {
        ofTranslate(ofGetWidth() - width - 4, 4);
        ofBackground(ofColor::black);
        ofSetColor(ofColor::white);
        ofNoFill();
        ofSetLineWidth(2);
        ofRect(1, 1, width+2, height+2);
        ofTranslate(2, 2);
        fbo.draw(0, 0);
    }
    ofPopStyle();
    ofPopMatrix();

    //Draw timeline
    if(showTimeline) {
        timeline.draw();
    }

    ofSetColor(ofColor::white);
    ofDrawBitmapString(
        "Recording to frame #" +
        ofToString(saveOnFrame) +
        " at " +
        ofToString(ofGetFrameRate()) +
        "fps...\nCurrent frame: " +
        ofToString(ofGetFrameNum()) +
        "\n" + renderMessage,
        20, height - 50);
    
    masker.drawOverlay();
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
    if(key == 't') {
        showTimeline = !showTimeline;
    } else if(key == 'f') {
        fullscreen = !fullscreen;
    } else if(key == 'm') {
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