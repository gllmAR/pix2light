#pragma once

#include "ofMain.h"
#include "ofxOsc.h"
#include "ofxGui.h"

#define HOST "localhost"
#define PORT 12345


class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

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
    
    
    void cropWidthChanged(int & cropWidth);
    void cropHeightChanged(int & cropHeight);
    void samplerChanged(int & sampler);
    
    
    ofxOscSender sender;
    
    ofImage source;
    vector<ofImage> destination;
    ofPixels pix;
    float imgRatio;
    int imgWidth;
    int imgHeight;
    int canvasWidth;
    int canvasHeight;
    int crop[4] ={0,0,10,10} ;
    int numPixels;
    
    ofParameter <float> magnification;
    ofParameter <int> cropWidth;
    ofParameter <int> cropHeight;
    ofParameter <int> sampler;
    ofxPanel gui;

    bool guiHide = true;
    bool mouseAttached = true;
    bool walker = false;
    
    
    
};



/*
 
 
mettre l'envoi osc dans un thread...!
le tout pourrait servir ˆ 
 afficher 
 rezise en respect du ratio?
good practice to planificate
 

 

*/
