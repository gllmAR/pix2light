#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    fboNombre = 1;
    
    fbo.resize(fboNombre);
    fboH.resize(fboNombre);
    
    for (int i= 0; i < fboNombre; i++){
        fbo[i].allocate(800, 800, GL_RGBA);
        fboH[i].allocate(800, 800, GL_RGBA);
    }
}

//--------------------------------------------------------------
void ofApp::update(){
    for (int i= 0; i < fboNombre; i++){
        ofEnableBlendMode(OF_BLENDMODE_ALPHA);
        
        fbo[i].begin();
        ofSetColor(255, 255, 255, 254);
        fboH[i].draw(0,0, 800,800);
        ofDrawCircle(posX, posY, 100);
        fbo[i].end();
        
        fboH[i].begin();
        ofSetColor(0, 0, 0, 10);
        ofDrawRectangle(0, 0, 800, 800);
        ofSetColor(255, 255, 255, 255);
        fbo[i].draw(0,0, 800,800);
        fboH[i].end();

    }
    
    posX = ofClamp(posX +1, 0, 800);
    posY = ofClamp(posY+ 2, 0, 800);
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0);
    
    fbo[0].draw(0,0);

    

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
