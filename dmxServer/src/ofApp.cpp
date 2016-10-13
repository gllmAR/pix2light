#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    gui.setup("DMX-Server");

    ofSetFrameRate(44);

    gui.add(port.set("port", 12345 ,1000, 65000));
    gui.add(deviceName.set("device", "d"));
    gui.loadFromFile("settings.xml");
            
    connectUsbDmx(deviceName);
}

//--------------------------------------------------------------

void ofApp::connectUsbDmx(std::string deviceID){
    
    cout<<"connecting to " <<deviceID<<endl;
    
    if (!dmx.isConnected()){
        dmx.clear();
        dmx.update(true); // black on shutdown
        dmx.disconnect();
    }
    
    dmx.connect(deviceID, total);
    dmx.update(true); // black on startup
    if(dmx.isConnected()){
        cout << "listening for osc messages on port " << port << "\n";
        receiver.setup(port);
    } else {
        cout << "Error on connection to usb Dongle" <<endl;
    }

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


//    std::stringstream strm;
//    strm << "fps: " << ofGetFrameRate();
//    ofSetWindowTitle(strm.str());
    
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
        ofSetColor(0,255,0);
        
        ofDrawBitmapString("()"  , 0,20);
        
        for(int channel = 1; channel <= total; channel++) {
            dmx.setLevel(channel, dmxValue[channel]);
        }
        dmx.update();
    } else {
        ofSetColor(255, 0, 0);
        ofDrawBitmapString("Could not connect to dmx ", 0,20);
    }
    
    if (!guiHide){
        gui.draw();
    }

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    if( key == 'g' ){
        guiHide = !guiHide;
    }
    if(key == 's') {
        gui.saveToFile("settings.xml");
    }
    if(key == 'l') {
        gui.loadFromFile("settings.xml");
    }

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
