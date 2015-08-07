#include "ofApp.h"
/* Begin description
{
    Layer wipes
}
End description */

/* Snippet begin */
void ofApp::setup(){
    increment = 0.005;
    ofSetWindowShape(500, 500);
    gif.setupPaused(ofGetTimestampString("out/%Y-%m-%d"), 210, 250);
    gif.fadeInOut(8, 2, ofColor::white, 1);
    masker.setup(6);
    transp1.setup("foil-large-transp.png");
    transp1.setTexturePositionY(0.5);
    transp2.setup("road-transp.png");
    transp2.setTexturePositionY(0.5);
    transp3.setup("road-transp.png");
    transp3.setTexturePositionY(0.5);
    transp4.setup("foil-large-transp.png");
    transp4.setTexturePositionY(0.5);
    transp5.setup("foil-large-transp.png");
    transp5.setTexturePositionY(0.5);
    transp6.setup("road-transp.png");
    transp6.setTexturePositionY(0.5);
}

void ofApp::update(){
    masker.beginLayer(0);
    {
        ofSetColor(ofColor::red);
        //transp1.incrementTextureOffsetY(-increment);
        transp1.incrementTextureScale(-increment);
        transp1.draw();
    }
    masker.endLayer(0);
    
    masker.beginMask(0);
    {
        //transp2.incrementTextureOffsetY(-increment);
        transp2.incrementTextureScale(-increment*0.5);
        ofBackground(ofColor::white);
        ofSetColor(ofColor::white);
        transp2.draw();
    }
    masker.endMask(0);
    
    masker.beginLayer(1);
    {
        ofSetColor(ofColor::green);
        transp3.incrementTextureOffsetX(increment);
        transp3.incrementTextureScale(increment);
        transp3.draw();
    }
    masker.endLayer(1);
    
    masker.beginMask(1);
    {
        transp4.incrementTextureOffsetX(increment);
        transp4.incrementTextureScale(increment*0.5);
        ofBackground(ofColor::white);
        ofSetColor(ofColor::white);
        transp4.draw();
    }
    masker.endMask(1);
    
    masker.beginLayer(2);
    {
        transp5.incrementTextureOffset(increment * 8, increment);
        transp5.incrementTextureScale(-increment);
        transp5.draw();
    }
    masker.endLayer(2);
    
    masker.beginMask(2);
    {
        transp6.incrementTextureOffset(-increment * 8, -increment);
        transp6.incrementTextureScale(increment*0.5);
        ofBackground(ofColor::white);
        ofSetColor(ofColor::white);
        transp6.draw();
    }
    masker.endMask(2);
    
    masker.beginLayer(3);
    {
        ofSetColor(ofColor::red);
        //transp1.incrementTextureOffsetY(-increment);
        transp1.incrementTextureScale(-increment);
        transp1.draw();
    }
    masker.endLayer(3);
    
    masker.beginMask(3);
    {
        //transp2.incrementTextureOffsetY(-increment);
        transp2.incrementTextureScale(-increment*0.5);
        ofBackground(ofColor::white);
        ofSetColor(ofColor::white);
        transp2.draw();
    }
    masker.endMask(3);
    
    masker.beginLayer(4);
    {
        ofSetColor(ofColor::green);
        transp3.incrementTextureOffsetX(increment);
        transp3.incrementTextureScale(increment);
        transp3.draw();
    }
    masker.endLayer(4);
    
    masker.beginMask(4);
    {
        transp4.incrementTextureOffsetX(increment);
        transp4.incrementTextureScale(increment*0.5);
        ofBackground(ofColor::white);
        ofSetColor(ofColor::white);
        transp4.draw();
    }
    masker.endMask(4);
    
    masker.beginLayer(5);
    {
        transp5.incrementTextureOffset(increment * 8, increment);
        transp5.incrementTextureScale(-increment);
        transp5.draw();
    }
    masker.endLayer(5);
    
    masker.beginMask(5);
    {
        transp6.incrementTextureOffset(-increment * 8, -increment);
        transp6.incrementTextureScale(increment*0.5);
        ofBackground(ofColor::white);
        ofSetColor(ofColor::white);
        transp6.draw();
    }
    masker.endMask(5);
}

void ofApp::draw(){
    gif.begin();
    {
        ofBackground(ofColor::white);
        masker.draw();
    }
    gif.endAndCaptureFrame();
    gif.draw();
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