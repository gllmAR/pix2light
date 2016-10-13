#pragma once

#include "ofMain.h"
#include "ofxOsc.h"
#include "ofxGui.h"

#define HOST "localhost"
#define PORT 12345

class Particle {
    public :
    Particle();
    void setup();
    void update(int x, int y);
    void draw();
    
    ofPoint pos;
    ofPoint vel;
    float time;
    float lifeTime;
    bool live;
};




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
    
    ofParameter <float> magnification;
    ofParameter <int> cropWidth;
    ofParameter <int> cropHeight;
    ofParameter <int> sampler;
    ofParameter <float> fboOverlay;
    ofParameter <bool> hideMouse;


    ofParameter <float> caramel;
    ofParameter <bool> showFBO;
    ofParameter <float> speedX;
    ofParameter <float> speedY;
    ofParameter <bool> appFullScreen;
    ofParameter <bool> trail;
    ofParameter <float> trailTime;
    ofParameter <bool> palco;
    ofParameter <bool> palcoAsserv;
    ofParameter <float> brightnessPalco;
    ofParameter <ofColor> palcoColor;
    ofParameter <int> palcoColorCorrect;
    ofParameter <int> palcoPgmChange;
    ofParameter <int > palcoColorMode;
    ofParameter <bool> walker;
    ofParameter <string> serveurDMXip;
    ofParameter <int> serveurDMXport;
    ofParameter <string> imgSource;

    //ofParameter <bool> mouvement;
    ofxPanel gui;
    
  


    
    bool guiHide = true;
    bool mouseAttached = true;

    bool init = true;
    bool alloc  = false;

    bool fullscreenFlag = false;
    
    

    
    
};



/*
 
 
mettre l'envoi osc dans un thread...!
le tout pourrait servir ˆ 
 afficher 
 rezise en respect du ratio?
good practice to planificate
 

 

*/
