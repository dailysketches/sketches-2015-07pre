#include "ofApp.h"

/* This draws the animation */
void ofApp::setupAnim() {
    fontSize = 64;
    loadFonts();
    quarterHeight = halfHeight * 0.5;
}

void ofApp::updateAnim(){
    if(ofGetFrameNum() % 3 == 0) {
        random_shuffle(fonts.begin(), fonts.end());
    }
}

void ofApp::drawAnim() {
    ofBackground(ofColor::black);
    ofSetColor(ofColor::white);

    ofSetRectMode(OF_RECTMODE_CENTER);
    fonts.at(0).drawStringCentered("THREE", halfWidth, quarterHeight);
    fonts.at(1).drawStringCentered("DAYS", halfWidth, halfHeight + quarterHeight);
    ofSetRectMode(OF_RECTMODE_CORNER);

    if(ofGetFrameNum() == 60) {
        renderGif();
    }
}

void ofApp::loadFonts() {
    amaticSC.loadFont("fonts/Amatic_SC/AmaticSC-Regular.ttf", fontSize);
    fonts.push_back(amaticSC);
    
    anonymousPro.loadFont("fonts/Anonymous_Pro/AnonymousPro-BoldItalic.ttf", fontSize);
    fonts.push_back(anonymousPro);
    
    cinzelDecorative.loadFont("fonts/Cinzel_Decorative/CinzelDecorative-Regular.ttf", fontSize);
    fonts.push_back(cinzelDecorative);
    
    greatVibes.loadFont("fonts/Great_Vibes/GreatVibes-Regular.ttf", fontSize);
    fonts.push_back(greatVibes);
    
    megrim.loadFont("fonts/Megrim/Megrim.ttf", fontSize);
    fonts.push_back(megrim);
    
    meriendaOne.loadFont("fonts/Merienda_One/MeriendaOne-Regular.ttf", fontSize);
    fonts.push_back(meriendaOne);
    
    monoton.loadFont("fonts/Monoton/Monoton-Regular.ttf", fontSize);
    fonts.push_back(monoton);
    
    poiretOne.loadFont("fonts/Poiret_One/PoiretOne-Regular.ttf", fontSize);
    fonts.push_back(poiretOne);
    
    rockSalt.loadFont("fonts/Rock_Salt/RockSalt.ttf", fontSize);
    fonts.push_back(rockSalt);
    
    shadowsIntoLight.loadFont("fonts/Shadows_Into_Light/ShadowsIntoLight.ttf", fontSize);
    fonts.push_back(shadowsIntoLight);
    
    walterTurncoat.loadFont("fonts/Walter_Turncoat/WalterTurncoat.ttf", fontSize);
    fonts.push_back(walterTurncoat);
}

/* This handles the setup and GIF rendering, etc */
void ofApp::setup(){
    //Gif render values
    slowMode = false;
    paused = false;
    width = 400, height = 200;
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