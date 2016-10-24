//
//  pixSampler.hpp
//  pbo2osc
//
//  Created by Guillaume Arseneault on 16-10-23.
//
//

#ifndef pixSampler_hpp
#define pixSampler_hpp

#include "ofMain.h"

class PixSampler {

public:
    
    void setup(int xSampler, int ySampler, int xSize, int ySize, ofFbo source);
        //resolution
        //passer la reference du fbo a traiter et l
        //le nombre
        // le x y
    void update(ofFbo source, int x, int y);
    void draw();
    void printBrightness();
    
    
    vector<ofFbo> samplerFbo;
    vector<ofPixels> samplerPixels;
    vector<int> samplersBrightness;
    
    int xSampler, ySampler, xSize, ySize, xResolution, yResolution;
    ofFbo source;

};


#endif /* pixSampler_hpp */
