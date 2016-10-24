//
//  pixSampler.cpp
//  pbo2osc
//
//  Created by Guillaume Arseneault on 16-10-23.
//
//

#include "pixSampler.hpp"


void PixSampler::setup(int xSamplerSetup, int ySamplerSetup, int xSizeSetup, int ySizeSetup, ofFbo sourceSetup){
    
    xSampler = xSamplerSetup;
    ySampler = ySamplerSetup;
    xSize = xSizeSetup;
    ySize = ySizeSetup;
    source = sourceSetup;
    
    xResolution = source.getWidth();
    yResolution = source.getHeight();


    
    samplerFbo.resize(xSampler*ySampler);
    samplerPixels.resize(xSampler*ySampler);
    

  
    for (int i = 0; i < samplerFbo.size();i++){
        samplerFbo[i].allocate(xSize, ySize);

    }

    samplersBrightness.resize(xSampler*ySampler*xSize*ySize);
    
    

}

void PixSampler::update(ofFbo source, int x, int y){
    

    for (int i = 0; i<xSampler; i++){
        for (int j = 0; j<ySampler; j++){
            int k =j+ySampler*i;
            samplerFbo[k].begin();
            ofClear(0, 0, 0);
            source.draw(-x-i*xSize+xSampler*xSize/2,
                        -y-j*ySize+ySampler*ySize/2,
                        xResolution,
                        yResolution
                        );
            samplerFbo[k].end();
            samplerFbo[k].readToPixels(samplerPixels[k]);
            

            for (int m = 0; m<xSize*ySize;m++){
                samplersBrightness[m+xSize*ySize*k]=
                    (samplerPixels[k][m*4]+
                    samplerPixels[k][m*4+1]+
                     samplerPixels[k][m*4+2])/3;
            }
            
        }

    }
}

void PixSampler::draw(){
    
    for (int i = 0; i<xSampler; i++){
        for (int j = 0; j<ySampler; j++){
             int k =j+ySampler*i;
            samplerFbo[k].draw(15+i*100,15+j*100,100,100);
        }
    }
    
    


}

void PixSampler::printBrightness(){

    for (int i = 0; i<samplersBrightness.size(); i++){
        
        cout<<samplersBrightness[i]<<" ";
        
    }
    cout<<endl;
    cout<<samplersBrightness.size()<<endl;
    
}
