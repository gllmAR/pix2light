//
//  toArtnet.cpp
//  pbo2osc
//
//  Created by Guillaume Arseneault on 16-11-21.
//
//

#include "toArtnet.hpp"

void ToArtnet::setup(int xSampler, int ySampler){

    // reconnect function...
    
    artnet.setup("10.1.1.1", 6454, 0);
    ofSetFrameRate(40);

}

void ToArtnet::update(vector<ofPixels> samplerPixels){

    artnet.sendDmx("10.239.1.5", 0, 0,samplerPixels[0].getData(), 512);
    
//    for(int i = 0; i<samplerPixels[0].size();i++){
//        cout<<int(samplerPixels[0][i])<<" ";
//        
//    }
//    cout<<endl;
    
//    for(int i = 0; i<samplerPixels.size();i++){
//    //to do, ip address, correlation dans une liste.
//        artnet.sendDmx("10.239.1.5", 0, i,samplerPixels[i].getData(), samplerPixels[0].size());
//
//    }
//    
    
    
    
}


void ToArtnet::draw(){


}

