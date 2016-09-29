#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    dmx.connect("tty.usbserial-ENSYD63O", total);
    dmx.update(true); // black on startup
    cout << "listening for osc messages on port " << PORT << "\n";
    receiver.setup(PORT);
    ofSetFrameRate(44);
}

//--------------------------------------------------------------

void ofApp::exit() {
     if(dmx.isConnected()) {
    dmx.clear();
    dmx.update(true); // black on shutdown
    dmx.disconnect();
     }
    

}

//--------------------------------------------------------------
void ofApp::update(){
    
    std::stringstream strm;
    strm << "fps: " << ofGetFrameRate();
    ofSetWindowTitle(strm.str());
    
    while(receiver.hasWaitingMessages()){
        // get the next message
        ofxOscMessage m;
        receiver.getNextMessage(m);
        //cout<<m.getAddress()<<endl;
        if(m.getAddress() == "/pix"){
            for (int i = 1; i<ofClamp(m.getNumArgs(),0,512); i++){
                dmxValue[i]=m.getArgAsInt(i);
              
            }
        }
    }
    
    

    



}

//--------------------------------------------------------------
void ofApp::draw(){
    if(dmx.isConnected()) {
        
        for(int channel = 1; channel <= total; channel++) {
            
            //dmx.setLevel(channel, ofRandom(0,255));
            dmx.setLevel(channel, dmxValue[channel]);
        }
        dmx.update();
    } else {
        ofSetColor(255);
        ofDrawBitmapString("Could not connect to dmx ", 250,20);
    }

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
