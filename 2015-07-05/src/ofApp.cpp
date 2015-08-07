#include "ofApp.h"

void ofApp::setup(){
    ofSetWindowShape(1000, 900);
    bpm = 60;
    playing = false;

    utils.setup();
    manager.setup();
    manager.toggleDebugUI();
    setupAudioUnits();
    setupTimeline();
}

void ofApp::setupAudioUnits() {
    manager.add(&chain1, "tal-one", ofColor::blue);
    chain1.link(&noiseMaker1).toMixer();
    manager.loadPresets(&chain1);
}

void ofApp::setupTimeline() {
    timeline.setup();
    timeline.setLoopType(OF_LOOP_NORMAL);
    timeline.setShowBPMGrid(true);
    timeline.enableSnapToBPM(true);
    timeline.setBPM(bpm);
    timeline.setDurationInSeconds(30);
    timeline.setOffset(ofVec2f(10, 480));
    timeline.setWidth(ofGetWidth() - 400);
    timeline.addCurves("lfo rate");
    timeline.addCurves("delay wet");
    timeline.addSwitches("midi events");
    ofAddListener(timeline.events().switched, this, &ofApp::switchFired);
}

void ofApp::update(){
    noiseMaker1.set(TALNoiseMaker_lfo2rate, timeline.getValue("lfo rate"));
    noiseMaker1.set(TALNoiseMaker_delaywet, timeline.getValue("delay wet"));
}

void ofApp::switchFired(ofxTLSwitchEventArgs &args) {
    string command = args.switchName + (args.on ? " ON" : " OFF");
    cout << endl << ofGetTimestampString() << endl;
    cout << "switch fired: " << command << endl;
    utils.executeMidiCommand(command, chain1.midi());
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