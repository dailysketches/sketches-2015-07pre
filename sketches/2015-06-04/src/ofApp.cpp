#include "ofApp.h"

//Pattern based on http://www.openprocessing.org/sketch/157035

/* This draws the animation */
void ofApp::setupAnim() {
    masker.setup(width, height);
    layerId = masker.newLayer();
    
    ofDisableArbTex();
    offset = ofRandom(3);
    setupImage("face.png", &img, &tex);

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
    ofSetColor(ofColor::white);
    tx0 = 1;
    ty0 = ofGetFrameNum() * 0.0012 + offset;
    tx1 = tx0 - 1;
    ty1 = ty0 - 0.2;
    drawLayer(&tex);
    masker.endLayer(layerId);
    
    masker.beginMask(layerId);
    ofBackground(ofColor::black);
    if(ofGetFrameNum() == 0 || ofRandom(1) > 0.6) {
        ofTriangle(ofRandom(-width, width*2), ofRandom(-height, height*2),
                   ofRandom(-width, width*2), ofRandom(-height, height*2),
                   ofRandom(-width, width*2), ofRandom(-height, height*2));
    } else if(ofRandom(1) > 0.3) {
        offset = ofRandom(3);
    }
    masker.endMask(layerId);
}

void ofApp::drawAnim() {
    if(ofGetFrameNum() == 0) ofBackground(ofColor::black);
    ofSetColor(ofColor::white, 40);
    drawLayer(&tex);

    ofSetColor(ofColor::white, 15);
    ofTranslate(halfWidth, halfHeight);
    for (int i = 0; i < 360; i+=6) {
        for (int q = 0; q < 360; q+=360) {
            radians = ofDegToRad(q + i + ofGetFrameNum() * 5);
            
            x = ofMap(sin(radians) * i, -600, -10, i, 0);
            y = ofMap(cos(radians) * i, -600, -10, 0, i);
            ofCircle(x, y, 2);
            ofCircle(y, x, 2);
            ofCircle(-x, -y, 2);
            ofCircle(-y, -x, 2);
            
            x = ofMap(sin(radians) * i, -600, -10, -i, 0);
            ofCircle(x, y, 2);
            ofCircle(y, x, 2);
            ofCircle(-x, -y, 2);
            ofCircle(-y, -x, 2);
        }
    }
    ofTranslate(-halfWidth, -halfHeight);
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
    width = 440, height = 440;
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