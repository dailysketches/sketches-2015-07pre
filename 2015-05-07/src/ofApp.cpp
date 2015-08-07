#include "ofApp.h"

/* This draws the animation */
void ofApp::setupAnim() {
    ofEnableSmoothing();
    bottomLayer.allocate(width, height, GL_RGBA);
    maskLayer.allocate(width, height, GL_RGBA);
    topLayer.allocate(width, height, GL_RGBA);
    
    maskShader.load("../../src/shader/alphaMask");
    maskShader.begin();
    maskShader.setUniformTexture("Tex0", topLayer.getTextureReference(), 0);
    maskShader.setUniformTexture("Tex1", maskLayer.getTextureReference(), 1);
    maskShader.end();
    
    setupBottomLayer();
    setupMaskLayer();
    setupTopLayer();
}

void ofApp::setupBottomLayer(){
    for(int i = -width; i < width*2; i += width * 0.01) {
        ofxShape shape;
        shape.setupFilledSquare(width - (width * 0.01));
        shape.scaleX(0.001);
        shape.setBlur(3);
        shape.setColor(ofColor::red);
        shape.positionX(ofMap(i, 0, width, width * 0.05, width * 0.99));
        shape.positionY(height * 0.5);
        bottomLayerShapes.push_back(shape);
    }
    
    ofxShapeSystem system1;
    for(int i = 0; i < bottomLayerShapes.size(); i++) {
        system1.add(bottomLayerShapes.at(i));
    }
    bottomLayerSystems.push_back(system1);
}

void ofApp::setupMaskLayer(){
    ofxShape shape;
    shape.setupFilledRing(60, width * 0.45);
    shape.positionX(width * 0.5);
    shape.positionY(height * 0.5);
    maskLayerShapes.push_back(shape);
    
    ofxShapeSystem system1;
    for(int i = 0; i < maskLayerShapes.size(); i++) {
        system1.add(maskLayerShapes.at(i));
    }
    maskLayerSystems.push_back(system1);
}

void ofApp::setupTopLayer(){
    for(int i = 0; i < height; i += height * 0.08) {
        ofxShape shape;
        shape.setupFilledSquare(height - (height * 0.05));
        shape.scaleY(0.03);
        shape.setBlur(3);
        shape.positionX(width * 0.5);
        shape.positionY(ofMap(i, 0, height, height * 0.05, height * 0.99));
        topLayerShapes.push_back(shape);
    }
    
    ofxShapeSystem system1;
    for(int i = 0; i < topLayerShapes.size(); i++) {
        system1.add(topLayerShapes.at(i));
    }
    topLayerSystems.push_back(system1);
}

void ofApp::updateAnim(){
    float faster = sin(ofGetFrameNum() * 0.1);
    float slower = sin(ofGetFrameNum() * 0.025);
    maskLayerShapes.at(0).setBlur(ofMap(faster, -1, 1, 3, 300));
    maskLayerShapes.at(0).rotateZ(ofMap(slower, -1, 1, 0, 90));
    
    bottomLayer.begin();
    ofClear(0, 0, 0, 255);
    ofPushMatrix();
    ofTranslate(width * 0.5, height * 0.5);
    ofRotateZ(ofMap(faster, -1, 1, 45, 135));
    ofTranslate(-width * 0.5, -height * 0.5);
    for(int i = 0; i < bottomLayerSystems.size(); i++) {
        bottomLayerSystems.at(i).update();
        bottomLayerSystems.at(i).draw();
    }
    ofPopMatrix();
    bottomLayer.end();
    
    maskLayer.begin();
    ofClear(0, 0, 0, 255);
    for(int i = 0; i < maskLayerSystems.size(); i++) {
        maskLayerSystems.at(i).update();
        maskLayerSystems.at(i).draw();
    }
    maskLayer.end();
    
    topLayer.begin();
    ofClear(0, 0, 0, 255);
    ofPushMatrix();
    ofTranslate(width * 0.5, height * 0.5);
    ofRotateZ(ofMap(faster, -1, 1, 135, 45));
    ofTranslate(-width * 0.5, -height * 0.5);
    for(int i = 0; i < topLayerSystems.size(); i++) {
        topLayerSystems.at(i).update();
        topLayerSystems.at(i).draw();
    }
    ofPopMatrix();
    topLayer.end();
}

void ofApp::drawAnim() {
    bottomLayer.draw(0, 0);
    
    maskShader.begin();
    glActiveTexture(GL_TEXTURE0_ARB);
    topLayer.getTextureReference().bind();
    glActiveTexture(GL_TEXTURE1_ARB);
    maskLayer.getTextureReference().bind();
    
    glBegin(GL_QUADS);
    
    glMultiTexCoord2d(GL_TEXTURE0_ARB, 0, 0);
    glMultiTexCoord2d(GL_TEXTURE1_ARB, 0, 0);
    glVertex2f(0, 0);
    glMultiTexCoord2d(GL_TEXTURE0_ARB, topLayer.getWidth(), 0);
    glMultiTexCoord2d(GL_TEXTURE1_ARB, maskLayer.getWidth(), 0);
    glVertex2f(width, 0);
    glMultiTexCoord2d(GL_TEXTURE0_ARB, topLayer.getWidth(), topLayer.getHeight());
    glMultiTexCoord2d(GL_TEXTURE1_ARB, maskLayer.getWidth(), maskLayer.getHeight());
    glVertex2f(width, height);
    glMultiTexCoord2d(GL_TEXTURE0_ARB, 0, topLayer.getHeight());
    glMultiTexCoord2d(GL_TEXTURE1_ARB, 0, maskLayer.getHeight());
    glVertex2f(0, height);
    
    glEnd();
    
    glActiveTexture(GL_TEXTURE1_ARB);
    maskLayer.getTextureReference().unbind();
    glActiveTexture(GL_TEXTURE0_ARB);
    topLayer.getTextureReference().unbind();
    maskShader.end();
    
    if(ofGetFrameNum() == 63) {
        renderGif();
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