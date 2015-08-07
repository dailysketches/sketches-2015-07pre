#include "ofApp.h"

//Pattern based on http://www.openprocessing.org/sketch/157035

/* This draws the animation */
void ofApp::setupAnim() {
    shapeSystem.setup();
    shape1.setupGradientSquare(halfWidth*0.15, halfWidth*0.85);
    shape2.setupGradientSquare(halfWidth*0.15, halfWidth*0.85);
    shape3.setupGradientSquare(halfWidth*0.15, halfWidth*0.85);
    shape4.setupGradientSquare(halfWidth*0.15, halfWidth*0.85);

    shape1.setPosition(halfWidth*0.5, halfHeight*0.5);
    shapeSystem.add(shape1);
    
    shape2.setPosition(halfWidth*0.5+halfWidth, halfHeight*0.5);
    shapeSystem.add(shape2);
    
    shape3.setPosition(halfWidth*0.5, halfHeight*0.5+halfHeight);
    shapeSystem.add(shape3);
    
    shape4.setPosition(halfWidth*0.5+halfHeight, halfHeight*0.5+halfHeight);
    shapeSystem.add(shape4);
    
    masker.setup(width, height);
    layerId = masker.newLayer();
    
    ofDisableArbTex();
    offset = ofRandom(3);
    setupImage("foil.png", &img, &tex);

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
    if(ofRandom(1) > 0.4) ofBackground(ofColor::black);
    ofSetColor(ofColor::red);
    tx0 = -ofGetFrameNum() * 0.00006 + offset + ofRandom(-0.09, 0.09);
    ty0 = ofGetFrameNum() * 0.005;
    tx1 = tx0 - 1;
    ty1 = ty0 - 0.25;
    drawLayer(&tex);
    masker.endLayer(layerId);
    
    masker.beginMask(layerId);
    ofBackground(ofColor::black);
    if(ofGetFrameNum() == 0 || ofRandom(1) > 0.2) {
        ofSetColor(ofColor::white, 32);
        for(int i = 0; i < 30; i++) {
            ofTriangle(ofRandom(-width, width*2), ofRandom(-height, height*2),
                       ofRandom(-width, width*2), ofRandom(-height, height*2),
                       ofRandom(-width, width*2), ofRandom(-height, height*2));
        }
    } else if(ofRandom(1) > 0.15) {
        offset = ofRandom(3);
    }
    masker.endMask(layerId);
}

void ofApp::drawAnim() {
    if(ofRandom(1) > 0.4) ofBackground(ofColor::black);
    ofSetColor(ofColor::white);

    tx0 = ofGetFrameNum() * 0.00006 + offset;
    tx1 = tx0 - 1;
    
    ofTranslate(-halfWidth, -halfHeight, 0);
    drawLayer(&tex);
    masker.draw();
    
    ofTranslate(width, 0, 0);
    drawLayer(&tex);
    masker.draw();
    
    ofTranslate(0, height, 0);
    drawLayer(&tex);
    masker.draw();
    
    ofTranslate(-width, 0, 0);
    drawLayer(&tex);
    masker.draw();
    
    ofTranslate(halfWidth, -halfHeight, 0);
    shapeSystem.draw();
    
    if(ofGetFrameNum() == 72) {
        renderGif();
    }
}

/* This handles the setup and GIF rendering, etc */
void ofApp::setup(){
    //Gif render values
    slowMode = false;
    paused = false;
    width = 400, height = 400;
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