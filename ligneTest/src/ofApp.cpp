#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0 , 0, 0);
}

//--------------------------------------------------------------
void ofApp::update(){
    for (auto &vert : line.getVertices()){
        vert.x += ofRandom(-0.1,0.1);
        vert.y += ofRandom(-0.1,0.1);
    }
    
    if (line.size()>1000){
        line.getVertices().erase(line.getVertices().begin());
    }
    
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetColor(255, 255, 255);
    line.draw();

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
    ofPoint pt;
    pt.set(x,y);
    line.addVertex(pt);

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
