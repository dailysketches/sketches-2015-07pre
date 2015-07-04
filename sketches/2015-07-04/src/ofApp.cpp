#include "ofApp.h"

void ofApp::setup(){
    ofSetWindowShape(1000, 900);
    utils.setup();
    manager.setup();
    manager.toggleDebugUI();
    setupAudioUnits();
    setupTimeline();

    playing = false;
}

void ofApp::setupAudioUnits() {
    manager.add(&chain1, "tal-one", ofColor::blue);
    manager.add(&chain2, "tal-two", ofColor::red);
    chain1.link(&noiseMaker1).toMixer();
    chain2.link(&noiseMaker2).toMixer();
    manager.loadPresets(&chain1);
    manager.loadPresets(&chain2);
}

void ofApp::setupTimeline() {
    timeline.setup();
    timeline.setLoopType(OF_LOOP_NORMAL);
    timeline.setDurationInSeconds(30);
    timeline.setOffset(ofVec2f(10, 480));
    timeline.setWidth(ofGetWidth() - 400);
    timeline.addCurves("portamento");
    timeline.addCurves("delay wet");
    timeline.addFlags("midi events");
    ofAddListener(timeline.events().bangFired, this, &ofApp::bang);
}

void ofApp::update(){
    noiseMaker1.set(TALNoiseMaker_portamento, timeline.getValue("portamento"));
    noiseMaker1.set(TALNoiseMaker_delaywet, timeline.getValue("delay wet"));
    noiseMaker2.set(TALNoiseMaker_portamento, timeline.getValue("portamento"));
    noiseMaker2.set(TALNoiseMaker_delaywet, timeline.getValue("delay wet"));
}

void ofApp::bang(ofxTLBangEventArgs &args) {
    cout << "bang fired: " << args.flag << endl;
    utils.executeMidiCommand(args.flag, chain1.midi());
    utils.executeMidiCommand(args.flag, chain2.midi());
}

void ofApp::draw(){
    manager.draw();
    timeline.draw();
}

void ofApp::togglePlaying() {
    playing = !playing;
    if(!playing) {
        //utils.executeMidiCommand("123 OFF", chain.midi());
    }
}

void ofApp::exit() {
    manager.exit();
}

void ofApp::keyPressed(int key){
    if(key == ' ') {
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