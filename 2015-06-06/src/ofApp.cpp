#include "ofApp.h"

/* This draws the animation */
void ofApp::setupAnim() {
    ofDisableArbTex();
    setupImage("surface.png", &img, &tex);

    plane.setResolution(2, 2);
    
    offset.set(1, 0.04);
}

void ofApp::setupImage(string file, ofImage *img, ofTexture *tex) {
    img->loadImage(file);
    *tex = img->getTextureReference();
    tex->setTextureWrap(GL_MIRRORED_REPEAT, GL_MIRRORED_REPEAT);
}

void ofApp::drawLayer(ofTexture *tex) {
    tx0 = offset.x;
    ty0 = offset.y;
    tx1 = tx0 - 0.66666668;
    ty1 = ty0 - 1;
    plane.setPosition(halfWidth, halfHeight, 0);
    plane.set(width, height);
    plane.mapTexCoords(tx0, ty0, tx1, ty1);
    plane.mapTexCoords(tx1, ty1, tx0, ty0);
    tex->bind();
    plane.draw();
    tex->unbind();
}

void ofApp::drawLayer2(ofTexture *tex) {
    tx0 = offset.x - (0.66666668 * 0.5);
    ty0 = offset.y -0.5;
    tx1 = tx0 - (0.66666668 * 0.5);
    ty1 = ty0 - 0.5;
    plane.setPosition(halfWidth*0.5, halfHeight*0.5, 0);
    plane.set(halfWidth, halfHeight);
    plane.mapTexCoords(tx0, ty0, tx1, ty1);
    plane.mapTexCoords(tx1, ty1, tx0, ty0);
    tex->bind();
    plane.draw();
    tex->unbind();
}

void ofApp::rotateScreen(float degrees, int amount) {
    ofTranslate(amount, amount, 0);
    ofRotate(degrees);
    ofTranslate(-amount, -amount, 0);
}

void ofApp::updateAnim(){
    offset.x += 0.02;
}

void ofApp::drawAnim() {
    ofBackground(ofColor::black);
    ofSetColor(ofColor::wheat);
    
    
    offset.y = 0.02;
    drawLayer(&tex);
    rotateScreen(90, halfWidth);
    drawLayer(&tex);
    rotateScreen(90, halfHeight);
    drawLayer(&tex);
    rotateScreen(90, halfWidth);
    drawLayer(&tex);
    rotateScreen(90, halfHeight);
    drawLayer2(&tex); //cover up

    if(ofGetFrameNum() == 100) {
        renderGif();
    }
}

/* This handles the setup and GIF rendering, etc */
void ofApp::setup(){
    //Gif render values
    slowMode = false;
    paused = false;
    width = 500, height = 340;
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