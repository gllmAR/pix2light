#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    //at first you must specify the Ip address of this machine
//    artnet.setup("10.0.0.4"); //make sure the firewall is deactivated at this point
//    artnet.setup("10.0.1.1", 6454, 0);
//     artnet.setup("10.0.0.1", 6454, 0);
    artnet.setup("192.168.47.101");
    ofSetFrameRate(40);
    fbo.allocate(512, 1, GL_RGB);

}

//--------------------------------------------------------------
void ofApp::update(){
    ofSetWindowTitle(ofToString(ofGetFrameRate(), 2));
    
    //create send buffer by ofFbo
    {
        fbo.begin();
        ofClear(0);
        float colorR = (sin(ofGetElapsedTimeMillis() / 1000.f) / 2.f + 0.5f) * 255.f;
        float colorG = (sin((ofGetElapsedTimeMillis() / 1000.f) + PI / 3.f) / 2.f + 0.5f) * 255.f;
        float colorB = (sin((ofGetElapsedTimeMillis() / 1000.f)  + PI * 2.f / 3.f) / 2.f + 0.5f) * 255.f;
        ofSetColor((int)colorR, (int)colorG, (int)colorB);
        ofDrawRectangle(0, 0, 512, 1);
        fbo.end();
        fbo.readToPixels(testImage.getPixelsRef());
    }
    
    
    artnet.sendDmx("192.168.47.102", 0, 0, testImage.getPixels().getData(), 512);
    artnet.sendDmx("192.168.47.102", 0, 1, testImage.getPixels().getData(), 512);
    artnet.sendDmx("192.168.47.102", 1, 1, testImage.getPixels().getData(), 512);
    artnet.sendDmx("192.168.47.102", 1, 0, testImage.getPixels().getData(), 512);

    //list nodes for sending
     //   troll.sendDmx(ip, testImage.getPixels(), 512);
//    artnet.sendDmx("10.0.0.149", testImage.getPixels(), 512);
   //     artnet.sendDmx("10.0.1.97", testImage.getPixels().getData(), 512);
//    artnet.sendDmx("10.0.0.100", 0, 0, testImage.getPixels().getData(), 512);
//    artnet.sendDmx("10.0.0.100", 0, 1, testImage.getPixels().getData(), 512);
//    artnet.sendDmx("10.0.0.100", 0, 2, testImage.getPixels().getData(), 512);

//    artnet.sendDmx("192.168.47.102", 0, 0, testImage.getPixels().getData(), 512);
//     artnet.sendDmx("192.168.47.102", 0, 1, testImage.getPixels().getData(), 512);
//     artnet.sendDmx("192.168.47.102", 1, 1, testImage.getPixels().getData(), 512);
//     artnet.sendDmx("192.168.47.102", 1, 0, testImage.getPixels().getData(), 512);

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0);
    float scalex = ofGetWidth() / fbo.getWidth();
    float scaley = ofGetHeight() / fbo.getHeight();
    ofScale(scalex, scaley);
    fbo.draw(0, 0);
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
