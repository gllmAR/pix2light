//
//  toArtnet.cpp
//  pbo2osc
//
//  Created by Guillaume Arseneault on 16-11-21.
//
//

#include "toArtnet.hpp"

void ToArtnet::setupGui(){
   // guiArtnet.add
    guiArtnet.setup("Artnet");
    guiArtnet.setName("artnet");
    guiArtnet.add(sendArtnet.set("Send artnet",1, 0, 1));

}

void ToArtnet::setup(int xSampler, int ySampler){
    
    totalSampler = xSampler*ySampler;
    // reconnect function...
    // loader les params dans le
    if( XML.loadFile("artnet.xml") ){
        cout<<"artnet.xml loaded!"<<endl;
        hostIP = XML.getValue("CONFIG:HOST:IP", "10.0.0.1");
        cout<<"host ip config is : "<<hostIP<<endl;
        fixturesIP.resize(xSampler*ySampler);
        
        for (int i = 0; i<fixturesIP.size();i++){
          fixturesIP[i] = XML.getValue("CONFIG:FIXTURES:A"+ofToString(i), "10.0.1.10");
            
            cout<<"FixtureA"+ofToString(i)<<" : "<<fixturesIP[i]<<endl;
        }
    }else{
        cout<<"unable to load artnet.xml check data/ folder"<<endl;
    }
    
    //debug
    artnet.setup(hostIP.c_str(), 6454, 0);
    ofSetFrameRate(40);

}

void ToArtnet::update(vector<ofPixels> samplerPixels){
    
    // a tester avec des patentes qui sont sois unicaste
    // ou bien faudra gosser sur l'addressage des universe!
    
    if(sendArtnet){
        for(int i = 0; i<totalSampler;i++){
             artnet.sendDmx(fixturesIP[i].c_str(), 0, 0,samplerPixels[i].getData(), 512);
            //cout<<int(samplerPixels[0][i])<<" ";
    
        }
    }
    
//    artnet.sendDmx("10.239.1.5", 0, 0,samplerPixels[0].getData(), 512);
    
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
// pourrait etre pertinant de mettre le les rectangles icitte.

}


void ToArtnet::exit(){
    artnet.stopThread();
    cout<<"killing artnet Thread"<<endl;
}
