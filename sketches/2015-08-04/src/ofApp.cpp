#include "ofApp.h"
/* Begin description
{
    No such thing as progress.
}
End description */

/* Snippet begin */
void ofApp::setup(){
    ofSetWindowShape(500, 500);
    gif.setupPaused(ofGetTimestampString("out/%Y-%m-%d"), 130, 180);
    gif.fadeInOut(3, 6, ofColor::white);
    gif.enableTextOverlay();
    masker.setup(3);
    numTissues = 16;
    numRoads = 3;

    tissue.setup("tissue.png", 2.0, TEXTURE_OFFSET_MIDDLE_CENTER);
    tissue.incrementTextureOffsetX(-0.5);
    for(int i = 0; i < numTissues; i++) {
        tissues.push_back(tissue);
    }

    road.setup("road.png", 0.5, TEXTURE_OFFSET_MIDDLE_CENTER);
    road.incrementTextureOffsetX(0.5);
    for(int i = 0; i < numRoads; i++) {
        roads.push_back(road);
    }
    roads.at(1).incrementTextureOffsetY(0.5);
    roads.at(1).setTextureScale(0.75);
}

void ofApp::update(){
    masker.beginLayer(0);
    {
        ofSetColor(ofColor(ofColor::white, 255));
        roads.at(0).incrementTextureOffsetY(0.0048);
        roads.at(0).draw();
    }
    masker.endLayer(0);
    
    masker.beginMask(0);
    {
        ofBackground(ofColor::black);
        for(int i = 0; i < tissues.size(); i++) {
            tissues.at(i).incrementTextureOffsetY((i+1) * 0.001);
            tissues.at(i).draw();
        }
        ofSetColor(ofColor(ofColor::black, 128));
        ofRect(200, 0, 100, gif.height);
    }
    masker.endMask(0);
    
    masker.beginLayer(1);
    {
        ofBackground(ofColor::black);
        ofSetColor(ofColor::white);
        masker.drawMask(0);
    }
    masker.endLayer(1);
    
    masker.beginMask(1);
    {
        ofBackground(ofColor::black);
        ofSetColor(ofColor::white);
        ofRect(120, 0, 30, gif.height);
        ofRect(350, 0, 30, gif.height);
    }
    masker.endMask(1);

    masker.beginLayer(2);
    {
        ofSetColor(ofColor(ofColor::white, 255));
        roads.at(2).incrementTextureOffsetY(-0.0012);
        roads.at(2).draw();
    }
    masker.endLayer(2);
    
    masker.beginMask(2);
    {
        ofBackground(ofColor::black);
        ofSetColor(ofColor::white);
        ofRect(0, 0, 120, gif.height);
        ofRect(380, 0, 120, gif.height);
    }
    masker.endMask(2);
}

void ofApp::draw(){
    gif.begin();
    {
        ofBackground(ofColor::black);
        ofSetColor(ofColor::red);
        roads.at(1).incrementTextureOffsetY(-0.006);
        roads.at(1).draw();
        masker.draw();
    }
    gif.endCaptureDraw();
    masker.drawOverlay();
}
/* Snippet end */

void ofApp::keyPressed(int key){
    if(key == 'o') {
        masker.toggleOverlay();
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