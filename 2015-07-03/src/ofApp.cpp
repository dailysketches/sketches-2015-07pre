#include "ofApp.h"

void ofApp::setup(){
    ofSetWindowShape(1000, 800);
    manager.setup();
    manager.toggleDebugUI();
    setupAudioUnits();
    setupTimeline();

    playing = false;
    note = 60;
}

void ofApp::setupAudioUnits() {
    manager.add(&chain, "tal-one", ofColor::blue);
    chain.link(&noiseMaker).toMixer();
    manager.loadPresets(&chain);
}

void ofApp::setupTimeline() {
    timeline.setup();
    timeline.setLoopType(OF_LOOP_NORMAL);
    timeline.setDurationInSeconds(30);
    timeline.setOffset(ofVec2f(10, 480));
    timeline.setWidth(ofGetWidth() - 400);
    timeline.addFlags("midi events");
    ofAddListener(timeline.events().bangFired, this, &ofApp::bang);
}

void ofApp::update(){
    
}

void ofApp::bang(ofxTLBangEventArgs &args) {
    if(args.flag == "") {
        chain.midi()->sendNoteOn(1, note);
    } else {
        interpretMidiFlag(args.flag);
    }
}

void ofApp::interpretMidiFlag(string flag) {
    vector<string> args = ofSplitString(flag, " ");
    int note = ofToInt(args.at(0));
    bool onCommand = args.at(1) == "ON";
    if(onCommand) {
        chain.midi()->sendNoteOn(1, note);
    } else {
        chain.midi()->sendNoteOff(1, note);
    }
}

void ofApp::draw(){
    manager.draw();
    timeline.draw();
}

void ofApp::togglePlaying() {
    playing = !playing;
    if(!playing) {
        chain.midi()->sendNoteOff(1, note);
    }
}

void ofApp::exit() {
    manager.exit();
}

void ofApp::keyPressed(int key){
    if(key == ' ') {
        togglePlaying();
    } else if(key == '[') {
        togglePlaying();
        note--;
        togglePlaying();
    } else if(key == ']') {
        togglePlaying();
        note++;
        togglePlaying();
    } else {
        manager.keyPressed(key);
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