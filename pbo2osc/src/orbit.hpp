//
//  orbit.hpp
//  pbo2osc
//
//  Created by Guillaume Arseneault on 16-11-05.
//
//

#ifndef orbit_hpp
#define orbit_hpp

#include <stdio.h>
#include "ofMain.h"
#include "ofxGui.h"


class Orbit {
 
    public :
    void setup(int w, int h);
    
    ofPoint update(ofPoint cursorPos, int w, int h, int xSampler, int ySampler, int xSamplerRes, int ySamplerRes, float magnification);
    
    void draw();
    void resize(int width, int height);
    
    
    void trailResetChanged();
    
    ofxGuiGroup guiOrbit;
    ofParameter <bool> applyOrbit;
    ofParameter <float> xOrbitSpeed;
    ofParameter <float> yOrbitSpeed;
    ofParameter <bool> trailShow;
    ofParameter <float> trailAmmount;
    ofParameter <float> trailSize;
    ofxButton trailReset;
    
    
    int xLfoAccum, yLfoAccum;
    int xPos, yPos;
    
    ofVec2f cursorCentre;
    ofFbo trailFbo, trailFboH;
    int canvasWidth, canvasHeight;
    
    
    
    
    
};



#endif /* orbit_hpp */
