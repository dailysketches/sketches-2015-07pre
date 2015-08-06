#include "ofApp.h"
/* Begin description
{
    More of a remix.
}
End description */

/* Snippet begin */
void ofApp::setup(){
    ofSetWindowShape(1000, 1000);
    gif.setupPaused(ofGetTimestampString("out/%Y-%m-%d"), 496, 576, 500, 500);
    gif.fadeInOut(3, 6, ofColor::white);
    gif.enableTextOverlay();

    //Anim 1
    numTissues = 16;
    numRoads = 4;
    masker1.setup(gif.size(), numRoads, ISOLATE_LAYERS);
    road.setup("road.png", gif.size(), 1.0, TEXTURE_OFFSET_MIDDLE_CENTER);
    road.incrementTextureOffsetX(0.5);
    for(int i = 0; i < numRoads; i++) {
        scale = ofMap(i, 0, numRoads-1, 2, 0.5);
        road.setTextureScale(scale);
        road.setTextureOffsetY(ofRandom(2));
        roads.push_back(road);

        tissuesLoader.clear();
        scale = ofMap(i, 0, numRoads-1, 8, 0.5);
        tissue.setup("tissue.png", gif.size(), scale, TEXTURE_OFFSET_MIDDLE_CENTER);
        tissue.incrementTextureOffsetX(-0.5);
        tissue.setTextureOffsetY(ofRandom(2));
        for(int j = 0; j < numTissues; j++) {
            tissuesLoader.push_back(tissue);
        }
        tissues.push_back(tissuesLoader);
    }

    //Anim 2
    numLayers = 6;
    masker2.setup(gif.size(), numLayers, ISOLATE_LAYERS);
    masker2.toggleOverlay();
    wbw.setup("wbw.png", gif.size(), 1.0);
    for(int i = 0; i < numLayers; i++) {
        wbw.setTextureOffset(i);
        wbws.push_back(wbw);
    }
    bwb.setup("bwb.png", gif.size(), 2.0);
    for(int i = 0; i < numLayers; i++) {
        bwb.setTextureOffset(8-i);
        bwbs.push_back(bwb);
    }
}

void ofApp::update(){
    //Anim 1
    for(int i = 0; i < numRoads; i++) {
        masker1.beginLayer(i);
        {
            ofSetColor(i % 2 == 0 ? ofColor::red : ofColor::white);
            roads.at(i).incrementTextureOffsetY(ofMap(i, 0, numRoads-1, -0.002, 0.002));
            roads.at(i).draw();
        }
        masker1.endLayer(i);
        
        masker1.beginMask(i);
        {
            ofSetColor(ofColor::white);
            ofBackground(ofColor::white);
            for(int j = 0; j < tissues.size(); j++) {
                tissues.at(i).at(j).incrementTextureOffsetY((j+1) * 0.0006);
                tissues.at(i).at(j).draw();
            }
        }
        masker1.endMask(i);
    }
    
    //Anim 2
    for(int i = 0; i < numLayers; i++) {
        wbws.at(i).incrementTextureOffset(-0.01, i % 2 == 0 ? -0.01 : 0.01);
        bwbs.at(i).incrementTextureOffset(i % 2 == 0 ? 0.01 : 0, i % 2 == 0 ? -0.01 : 0.01);
        
        masker2.beginLayer(i);
        {
            if(i % 2 == 0) {
                ofSetColor(ofColor:: red);
                for(int y = i * 2; y < gif.height; y+=10) {
                    ofLine(0, y, gif.width, y);
                }
            } else {
                wbws.at(i).draw();
            }
        }
        masker2.endLayer(i);
        
        masker2.beginMask(i);
        {
            bwbs.at(i).draw();
        }
        masker2.endMask(i);
    }
}

void ofApp::draw(){
    gif.begin();
    {
        masker1.draw();
        masker2.draw();
    }
    gif.endCaptureDraw();
    masker1.drawOverlay();
    masker2.drawOverlay();
}
/* Snippet end */

void ofApp::keyPressed(int key){
    if(key == '1') {
        masker1.toggleOverlay();
    }
    if(key == '2') {
        masker2.toggleOverlay();
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