#pragma once

#include "ofMain.h"

#include "ofApp.h"
#include "ofxOsc.h"
#include "ofxGui.h"
#include "imgLoader.hpp"
#include "pixSampler.hpp"
#include "orbit.hpp"
#include "toArtnet.hpp"
#include "ofxOscParameterSync.h"


class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
        void exit();

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
    
        void updateWindowSize();
    
    bool guiShow = false;
    
    ofxOscParameterSync sync;

    
    ImgLoader imgLoader;
    PixSampler pixSampler;
    Orbit orbit;
    ofxOscSender sender;
    ToArtnet toArtnet;
    

    
    int cursorX, cursorY, appWidth, appHeight;
    ofVec2f cursorPos;
    
    ofParameter <bool> mouseControlled;
    
    ofxPanel gui;
    
    // workaround pour le pi ou la taille de l ecran nest pas mis a jour
    bool updateWindowSizeFlag = true;
 
		
};


//
