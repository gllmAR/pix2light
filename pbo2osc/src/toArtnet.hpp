//
//  toArtnet.hpp
//  pbo2osc
//
//  Created by Guillaume Arseneault on 16-11-21.
//
//

#ifndef toArtnet_hpp
#define toArtnet_hpp

#include "ofMain.h"
#include "ofxArtnet.h"


class ToArtnet {

public:
    void setup(int xSampler, int ySampler);
    void update(vector<ofPixels> samplerPixels);
    void draw();
    
    ofxArtnet artnet;
    ofImage testImage;

};

#endif /* toArtnet_hpp */
