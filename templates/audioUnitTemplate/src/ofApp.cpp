#include "ofApp.h"

void ofApp::setup(){
    manager.setup();
    manager.toggleDebugUI();
    manager.add(&talChain, "tal-one", ofColor::blue);

    playing = false;
    note = 60;
    
    ofAddListener(bpm.beatEvent, this, &ofApp::play);
    bpm.start();
}

void ofApp::play(void){
    if(playing) {
        talChain.midi()->sendNoteOn(1, note);
    }
}

void ofApp::togglePlaying() {
    playing = !playing;
    if(!playing) {
        talChain.midi()->sendNoteOff(1, note);
    }
}

void ofApp::update(){
    manager.update();

    lfo2Rate = ofMap(sin(ofGetFrameNum() * 0.03), -1, 1, 0.4, 0.6);
    talChain.getSynth()->set(TALNoiseMaker_lfo2rate, lfo2Rate);
}

void ofApp::draw(){
    manager.draw();
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