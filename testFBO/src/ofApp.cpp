#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    fboNombre = 2;
    
    fbo.resize(fboNombre);
    fboH.resize(fboNombre);
    
    for (int i= 0; i < fboNombre; i++){
        fbo[i].allocate(10, 10, GL_RGB);
        fboH[i].allocate(10, 10, GL_RGB);
    }
}

//--------------------------------------------------------------
void ofApp::update(){
    for (int i= 0; i < fboNombre; i++){
        fbo[i].draw(i*10, 10, 10, 10);
        fboH[i].draw(i*10, 400, 10, 10);

    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    

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
