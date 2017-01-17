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
    guiArtnet.setup("artnet");
    guiArtnet.setName("artnet");
    guiArtnet.add(sendArtnet.set("sendArtnet",1, 0, 1));
    guiArtnet.add(outputTrim.set("outputTrim", 1, 0 , 2));
    guiArtnet.add(showBrightness.set("showBrightness ", 1, 0, 1));
    guiArtnet.add(showBrightnessOpacity.set("opacity", .2, 0 , 1));
    
                  

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
    

    
    if(sendArtnet){
        for(int i = 0; i<totalSampler;i++){
            //trimthe output
            for (int j = 0; j<samplerPixels[i].size(); j++){
                ofClamp(samplerPixels[i][j]=samplerPixels[i][j]*outputTrim, 0, 255);
            }

            artnet.sendDmx(fixturesIP[i].c_str(), 0, i,samplerPixels[i].getData(), 512);
                }
    }
}


void ToArtnet::draw(vector<ofPixels> samplerPixels){
    
    if(showBrightness){
        ofPushStyle();
        ofEnableBlendMode(OF_BLENDMODE_SCREEN);
        
        float rectWidth = float(resolutionX)/float(samplerPixels.size()*samplerPixels[0].size());
        
        ofFill();
        ofSetColor(showBrightnessOpacity*255);
        
        for (int i = 0; i<samplerPixels.size();i++){
            for (int j = 0; j<samplerPixels[i].size();j++){
                ofDrawRectangle(
                                i*rectWidth*samplerPixels[i].size()+ j*rectWidth,
                                resolutionY-samplerPixels[i][j],
                                rectWidth,
                                samplerPixels[i][j]);
            }
        }
        ofPopStyle();
        
    }
    

}

void ToArtnet::resize(int sizeX, int sizeY){

    resolutionX = sizeX;
    resolutionY = sizeY;

}


void ToArtnet::exit(){
    artnet.stopThread();
    cout<<"killing artnet Thread"<<endl;
}
