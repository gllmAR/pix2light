#pragma once

#include "ofMain.h"
#include "ofxOsc.h"
#include "ofxGui.h"
#include "imgLoader.hpp"

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
    
    
    
        void walkerChanged(bool & walker);
        void hideMouseChanged(bool & hideMouse);
        void appFullScreenChanged(bool & appFullScreen);
        void cropWidthChanged(int & cropWidth);
        void cropHeightChanged(int & cropHeight);
        void samplerChanged(int & sampler);
        void serveurDMXportChanged(int & serveurDMXport);

    
        void allocFbo();
    
    imgLoader imgLoader;
    
    ofxOscSender sender;
    
    ofImage source;
    vector<ofImage> destination;
    vector<ofPixels> pixels;
    vector<ofFbo> frameBuffer, frameBufferH;
    ofFbo trailFbo, trailFboH;

    ofPixels pix;
    float imgRatio;
    int imgWidth;
    int imgHeight;
    int canvasWidth;
    int canvasHeight;
    int crop[4] ={0,0,10,10} ;
    int numPixels;
    
    
    ofParameter <bool> hideMouse;
    ofParameter <string> imgSource;
    ofParameter <string> serveurDMXip;
    ofParameter <int> serveurDMXport;
    ofParameter <bool> appFullScreen;
    
    
    ofParameter <int> sampler;
    ofParameter <float> magnification;
    ofParameter <int> cropWidth;
    ofParameter <int> cropHeight;
    ofParameter <float> fboOverlay;
    ofParameter <float> caramel;
    ofParameter <bool> showFBO;
    ofParameter <ofColor> samplerColor;
    
    ofParameter <bool> walker;
    ofParameter <float> speedX;
    ofParameter <float> speedY;
    ofParameter <bool> trail;
    ofParameter <float> trailSize;
    ofParameter <float> trailTime;
    ofParameter <ofColor> trailColor;
    
    
    ofParameter <bool> palco;
    ofParameter <bool> palcoAsserv;
    ofParameter <float> brightnessPalco;
    ofParameter <ofColor> palcoColor;
    ofParameter <int> palcoColorCorrect;
    ofParameter <int> palcoPgmChange;
    ofParameter <int > palcoColorMode;




    //ofParameter <bool> mouvement;
    ofxPanel gui;
    ofxGuiGroup guiSampler;
    ofxGuiGroup guiWalker;
    ofxGuiGroup guiTrail;
    ofxGuiGroup guiPalco;
    
    
  


    
    bool guiHide = true;
    bool mouseAttached = true;

    bool init = true;
    bool alloc  = false;

    bool fullscreenFlag = false;
    bool allocTrailFbo = false;

    
    

    
    
};



/*
 
 
mettre l'envoi osc dans un thread...!
le tout pourrait servir ˆ 
 afficher 
 rezise en respect du ratio?
good practice to planificate
 

 

*/
