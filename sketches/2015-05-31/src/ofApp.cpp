#include "ofApp.h"

void ofApp::setup(){
    manager.setup();
    manager.toggleDebugUI();
    manager.add(&chain1, "tal-one", ofColor::blue);
    manager.add(&chain2, "tal-two", ofColor::blue);

    playing = false;
    note = 60;
    
    ofAddListener(bpm.beatEvent, this, &ofApp::play);
    bpm.start();
    chain1.midi()->sendNoteOn(1, note);
    chain2.midi()->sendNoteOn(1, note);
}

void ofApp::play(void){
    if(playing) {
        if(currentChain == 1) {
            chain1.getSynth()->set(TALNoiseMaker_volume, -10);
            chain2.getSynth()->set(TALNoiseMaker_volume, 0);
            currentChain = 2;
        } else {
            chain1.getSynth()->set(TALNoiseMaker_volume, 0);
            chain2.getSynth()->set(TALNoiseMaker_volume, -10);
            currentChain = 1;
        }
    }
}

void ofApp::togglePlaying() {
    playing = !playing;
    if(!playing) {
        chain1.midi()->sendNoteOff(1, note);
    }
}

void ofApp::update(){
    manager.update();
    
    //Animate everythung based on sin()
    val = ofMap(sin(ofGetFrameNum() * 0.03), -1, 1, 0.4, 0.6);
    chain1.getSynth()->set(TALNoiseMaker_lfo2rate, val);
    
    val = ofMap(sin(ofGetFrameNum() * 0.06), -1, 1, 0.3, 0.8);
    chain1.getSynth()->set(TALNoiseMaker_envelopeeditoramount, val);
    
    val = ofMap(sin(ofGetFrameNum() * 0.45), -1, 1, 6900, 4000);
    chain1.getFilter()->set(kLowPassParam_CutoffFrequency, val);
    
    val = ofMap(sin(ofGetFrameNum() * 0.2), -1, 1, 10, 26);
    chain1.getFilter()->set(kLowPassParam_Resonance, val);
    
    //Exactly the same, but with cos()
    val = ofMap(cos(ofGetFrameNum() * 0.03), -1, 1, 0.4, 0.6);
    chain2.getSynth()->set(TALNoiseMaker_lfo2rate, val);
    
    val = ofMap(cos(ofGetFrameNum() * 0.06), -1, 1, 0.3, 0.8);
    chain2.getSynth()->set(TALNoiseMaker_envelopeeditoramount, val);
    
    val = ofMap(cos(ofGetFrameNum() * 0.45), -1, 1, 6900, 4000);
    chain2.getFilter()->set(kLowPassParam_CutoffFrequency, val);
    
    val = ofMap(cos(ofGetFrameNum() * 0.2), -1, 1, 10, 26);
    chain2.getFilter()->set(kLowPassParam_Resonance, val);
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