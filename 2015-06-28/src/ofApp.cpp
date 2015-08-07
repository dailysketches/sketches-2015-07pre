#include "ofApp.h"

void ofApp::setup(){
    ofSetWindowShape(1000, 1000);
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
    timeline.setOffset(ofVec2f(10, 450));
    timeline.setWidth(ofGetWidth() - 400);
    timeline.addCurves("master osc 1 (pulse)", ofRange(0, 1));
    timeline.addCurves("master osc 2 (triangle)", ofRange(0, 1));
    timeline.addCurves("envelope amount (x8)", ofRange(0, 1));
    timeline.addCurves("lfo 2 rate", ofRange(0, 1));
    timeline.addBangs("midi events");
    ofAddListener(timeline.events().bangFired, this, &ofApp::bang);
}

void ofApp::update(){
    noiseMaker.set(TALNoiseMaker_osc1volume, timeline.getValue("master osc 1 (pulse)"));
    noiseMaker.set(TALNoiseMaker_osc2volume, timeline.getValue("master osc 2 (triangle)"));
    noiseMaker.set(TALNoiseMaker_envelopeeditoramount, timeline.getValue("envelope amount (x8)"));
    noiseMaker.set(TALNoiseMaker_lfo2rate, timeline.getValue("lfo 2 rate"));
}

void ofApp::bang(ofxTLBangEventArgs &args) {
    if(args.flag == "") {
        chain.midi()->sendNoteOn(1, note);
    } else {
        chain.midi()->sendNoteOn(1, ofToInt(args.flag));
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