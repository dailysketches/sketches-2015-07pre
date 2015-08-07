#include "ofApp.h"

void ofApp::setup(){
    playing = true;
    note = 60;

    manager.setup();
    manager.toggleDebugUI();
    manager.add(&chain1, "tal-1", ofColor::blue);
    manager.add(&chain2, "tal-2", ofColor::red);

    bpm.setBpm(160);
    ofAddListener(bpm.beatEvent, this, &ofApp::play);
    bpm.start();
}

void ofApp::play(void){
    cout << "playing" << endl;
    if(playing) {
        chain1.midi()->sendNoteOn(1, note);
        //chain2.midi()->sendNoteOn(1, note);
    }
}

void ofApp::togglePlaying() {
    playing = !playing;
    if(!playing) {
        chain1.midi()->sendNoteOff(1, note);
        //chain2.midi()->sendNoteOff(1, note);
    }
}

void ofApp::update(){
    manager.update();

    val = ofMap(sin(ofGetFrameNum() * 0.04), -1, 1, 30, 59);
    chain1.getReverb()->set(kReverbParam_DryWetMix, val);

    val = ofMap(cos(ofGetFrameNum() * 0.005), -1, 1, 0, 100);
    chain1.getSynth()->set(TALNoiseMaker_osc1tune, val);
    
    val = ofMap(cos(ofGetFrameNum() * 0.0005), -1, 1, 50  , 2 50);
    chain1.getFilter()->set(kLowPassParam_CutoffFrequency, val);
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