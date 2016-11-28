//
//  toArtnet.cpp
//  pbo2osc
//
//  Created by Guillaume Arseneault on 16-11-21.
//
//

#include "toArtnet.hpp"

void ToArtnet::setup(int xSampler, int ySampler){

    artnet.setup("10.0.1.1", 6454, 1);
    ofSetFrameRate(40);
   // fbo.allocate(512, 1, GL_RGB);

}

void ToArtnet::update(int xSampler, int ySampler, int xSize, int ySize, vector<ofPixels> samplerPixels){

    
    //list nodes for sending
    //   troll.sendDmx(ip, testImage.getPixels(), 512);
    //    artnet.sendDmx("10.0.0.149", testImage.getPixels(), 512);
    //     artnet.sendDmx("10.0.1.97", testImage.getPixels().getData(), 512);
    
    
//    artnet.sendDmx("10.0.1.97", 0, 0, testImage.getPixels().getData(), 512);
//    artnet.sendDmx("10.0.1.97", 0, 1, testImage.getPixels().getData(), 512);
//    artnet.sendDmx("10.0.1.97", 0, 2, testImage.getPixels().getData(), 512);
//
   // cout<<samplersBrightness.size()<<endl;
    
// nombre de fixture par univers  : 2
// list des addresse des fixture
    
    
    for(int i = 0; i<samplerPixels.size();i++){
    
        artnet.sendDmx("10.0.1.97", 0, 0,(samplerPixels[0].getData()), 512);

    }
    
    
    
    
    
    
    
    
}


void ToArtnet::draw(){


}

