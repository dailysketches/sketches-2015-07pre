#include "ofApp.h"

void ofApp::setup(){
    manager.setup();
    manager.toggleDebugUI();

    playing = true;
    note = 60;
    
    for(int i = 0; i < 4; i++){
        chains.push_back(chain);
    }
    
    for(int i = 0; i < chains.size(); i++){
        manager.add(&chains.at(i), "tal-" + ofToString(i), ofColor::fromHsb((i * 255 / chains.size()), 255, 255));
        chains.at(i).midi()->sendNoteOn(1, note);
    }
    
    bpm.setBpm(160);
    ofAddListener(bpm.beatEvent, this, &ofApp::play);
    bpm.start();
}

void ofApp::play(void){
    if(playing) {
        for(int i = 0; i < chains.size(); i++){
            val = currentChain == i ? 1 : 0;
            chains.at(i).getSynth()->set(TALNoiseMaker_volume, val);
        }

        currentChain = currentChain == chains.size() - 1 ? 0 : currentChain + 1;
    }
}

void ofApp::togglePlaying() {
    playing = !playing;
    if(!playing) {
        for(int i = 0; i < chains.size(); i++){
            chains.at(i).midi()->sendNoteOff(1, note);
        }
    }
}

void ofApp::update(){
    manager.update();
    
    val = ofMap(cos(ofGetFrameNum() * 0.04), -1, 1, 0, 1);
    chains.at(0).getSynth()->set(TALNoiseMaker_osc1tune, val);
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