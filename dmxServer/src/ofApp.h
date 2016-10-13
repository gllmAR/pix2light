#pragma once

#include "ofMain.h"
#include "ofxDmx.h"
#include "ofxGui.h"
#include "ofxOsc.h"



//#define PORT 12345

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
        void exit();
    
    void connectUsbDmx(std::string deviceID);

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    	ofxDmx dmx;
        ofSerial serial;
    		int total = 512;
        int dmxValue[512];
    
        ofxOscReceiver receiver;
    
    ofParameter<string> deviceName;
    ofParameter<int> port;
    
    ofxPanel gui;
    
    bool guiHide = true;

    


};
