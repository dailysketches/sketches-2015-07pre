#include "ofApp.h"

/* This draws the animation */
void ofApp::setupAnim() {
    leafVertical.setup("leaf-vertical.png", width, height, 1, TEXTURE_OFFSET_MIDDLE_CENTER);
    leafDiagonal.setup("leaf-diagonal.png", width, height, 4, TEXTURE_OFFSET_MIDDLE_CENTER);
    leafStar.setup("leaf-star.png", width, height, 2, TEXTURE_OFFSET_MIDDLE_CENTER);
    planes.push_back(&leafVertical);
    planes.push_back(&leafDiagonal);
    planes.push_back(&leafStar);

    mask1.setup("mask-texture-1.png", width, height, 8, TEXTURE_OFFSET_MIDDLE_CENTER);
    masks.push_back(&mask1);
    mask2.setup("mask-texture-2.png", width, height, 10, TEXTURE_OFFSET_MIDDLE_CENTER);
    masks.push_back(&mask2);

    numLayers = 2;
    layerIds = masker.setup(width, height, numLayers);
    increment = 0.02;
}

void ofApp::updateAnim(){
    leafStar.incrementTextureOffsetY(increment);

    for(int i = 0; i < numLayers; i++) {
        masker.beginLayer(layerIds.at(i));
        {
            scale1 = ofMap(sin(ofGetFrameNum() * increment), -1, 1, 0.7, 5);
            scale2 = ofMap(cos(ofGetFrameNum() * increment), -1, 1, 2.5, 4);
            ofSetColor(ofColor::red, alpha);
            planes.at(i)->incrementTextureOffsetY(i % 2 == 0 ? increment : -increment);
            planes.at(i)->setTextureScale(i % 2 == 0 ? scale1 : scale2);
            planes.at(i)->draw();
        }
        masker.endLayer(layerIds.at(i));

        masker.beginMask(layerIds.at(i));
        {
            maskIncrement = ofGetFrameNum() * ((i % 2) - 0.5) * 0.125;
            maskIncrement = ofMap(sin(maskIncrement), 1, -1, 0.001, -0.001);
            if(i % 2 == 1) maskIncrement *= 5;
            
            scale1 = ofMap(sin(ofGetFrameNum() * increment), -1, 1, 3, 9);
            scale2 = ofMap(cos(ofGetFrameNum() * increment), -1, 1, 6, 12);

            ofBackground(ofColor::black);
            ofSetColor(ofColor::white);
            masks.at(i)->incrementTextureOffsetY(maskIncrement);
            masks.at(i)->setTextureScale(i % 2 == 0 ? scale1 : scale2);
            masks.at(i)->draw();
        }
        masker.endMask(layerIds.at(i));
    }
}

void ofApp::drawAnim() {
    alpha = ofGetFrameNum() == 0 || ofRandom(1) > 0.5 ? 255 : 128;
    ofSetColor(ofColor::red, alpha);
    leafStar.draw();

    ofSetColor(ofColor::white);
    masker.draw();
    if(ofGetFrameNum() == numFrames) {
        renderGif();
    }
}

/* This handles the setup and GIF rendering, etc */
void ofApp::setup(){
    //Gif render values
    slowMode = false;
    paused = false;
    fullscreen = false;
    width = 500, height = 500;
    duration = 0.2, colors = 128, numFrames = 100;
    saveOnFrame = -1;

    filename = ofGetTimestampString("%Y-%m-%d") + ".gif";
    framerate = slowMode ? 5 : 10;
    halfWidth = width * 0.5;
    halfHeight = height * 0.5;

    //Init
    ofSetFrameRate(framerate);
    ofSetWindowShape(506, 920);
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
    if(key == 'f') {
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