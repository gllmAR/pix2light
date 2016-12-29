;//
//  pixSampler.hpp
//  pbo2osc
//
//  Created by Guillaume Arseneault on 16-10-23.
//
//

#ifndef pixSampler_hpp
#define pixSampler_hpp

#include "ofMain.h"
#include "ofxGui.h"


class PixSampler {

public:
    
    void setup(int xSampler, int ySampler, int xSize, int ySize, ofFbo source);
        //resolution
        //passer la reference du fbo a traiter et l
        //le nombre
        // le x y
    void resizeResolution(ofFbo source);
    void allocateFbo();
    void checkGuiChanged();
    void update(ofFbo source, int posX, int posY);
    void draw(int x, int y);
    void printBrightness();
    void exit();
    
    void updatesFbos(ofFbo source, int posX, int posY);
    
    
    vector<ofFbo> samplerFbo; //fbo mou
    vector<ofFbo> samplerFboH; // fbo de feedback
    vector<ofFbo> samplerFboS; // fbo Source :
    
    
    vector<ofPixels> samplerPixels;
    vector<ofPixels> samplerBrightness;
    //vector<int> samplersBrightness;
    //ofPixels samplersBrightness;
    
    
    
    bool allocFlag = true;
    int xSampler, ySampler, xSize, ySize, xResolution, yResolution;
    ofFbo source;
    
    ofxGuiGroup guiSampler;
    
    ofParameter <int> xSamplerGui;
    ofParameter <int> ySamplerGui;
    ofParameter <int> xSizeGui;
    ofParameter <int> ySizeGui;
    ofParameter <float> magnification;
    ofParameter <float> caramel;
    ofParameter <bool> showCaramel;
    
    ofParameter <bool> showSamplersBrightness;
    
    int positionX, positionY;
    

};


#endif /* pixSampler_hpp */
