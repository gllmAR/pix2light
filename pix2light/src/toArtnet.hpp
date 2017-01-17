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
#include "ofxGui.h"
#include "ofxXmlSettings.h"


class ToArtnet {

public:
    void setupGui();
    void setup(int xSampler, int ySampler);
    void update(vector<ofPixels> samplerPixels);
    void draw(vector<ofPixels> samplerPixels);
    void resize(int sizeX, int sizeY);
    void exit();
    
    ofxArtnet artnet;
    //ofImage testImage;

    ofxGuiGroup guiArtnet;
    
    ofxXmlSettings XML;
    string hostIP;
    vector<string> fixturesIP;
    
    ofParameter<bool> sendArtnet;
    ofParameter<bool>  showBrightness;
    ofParameter<float>  showBrightnessOpacity;
    ofParameter<float>  outputTrim;
    
    int resolutionX = 600, resolutionY = 600;
    
    
private:
    int totalSampler;
    

    
};

#endif /* toArtnet_hpp */
