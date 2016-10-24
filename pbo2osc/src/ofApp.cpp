#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){

    imgLoader.setup(1920,1080);
    imgLoader.loadDir("calib");
    pixSampler.setup(2, 2, 15, 15, imgLoader.canvasFbo);
}

//--------------------------------------------------------------
void ofApp::update(){
    imgLoader.update();
    pixSampler.update(imgLoader.canvasFbo, cursorX, cursorY);

}

//--------------------------------------------------------------
void ofApp::draw(){
    
    imgLoader.canvasFbo.draw(0,0,1920,1080);
    pixSampler.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    if(key == OF_KEY_RIGHT){
        imgLoader.next();
    }
    
    if(key == OF_KEY_LEFT){
        imgLoader.prev();
    }
    
    if(key == 'p'){
        pixSampler.printBrightness();
    }

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
    cursorX = x;
    cursorY = y;
    


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
