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
    
    // gui group
    
    guiSampler.setup("Sampler");
    guiSampler.setName("sampler");
    guiSampler.add(xSamplerGui.set("X Sampler", 1, 1, 15));
    guiSampler.add(ySamplerGui.set("Y Sampler", 1, 1, 15));
    guiSampler.add(xSizeGui.set("X Size Pixels ", 15, 1, 100));
    guiSampler.add(ySizeGui.set("Y Size Pixels ", 15, 1, 100));
    guiSampler.add(magnification.set("magnification ", 10, 0.5, 20));
    guiSampler.add(caramel.set("caramel ", 0.5, 0.5, 1));
    guiSampler.add(showCaramel.set("show Caramel  ", 1, 0, 1));
    guiSampler.add(showSamplersBrightness.set("show samplers bright ", 1, 0, 1));
    

    
    // alloc
    allocateFbo();
    

}

void PixSampler::resizeResolution(ofFbo source){

    xResolution = source.getWidth();
    yResolution = source.getHeight();
    
}

void PixSampler::allocateFbo(){
    
    // redimension
    samplerFbo.resize(xSampler*ySampler);
    samplerFboH.resize(xSampler*ySampler);
    samplerFboS.resize(xSampler*ySampler);
    samplerPixels.resize(xSampler*ySampler);
    samplerBrightness.resize(xSampler*ySampler);
    
    
    // allocation
    for (int i = 0; i < samplerFbo.size();i++){
        samplerFbo[i].allocate(xSize, ySize);
        samplerFboH[i].allocate(xSize, ySize);
        samplerFboS[i].allocate(xSize, ySize);
        samplerBrightness[i].allocate(xSize, ySize, OF_IMAGE_GRAYSCALE);

    }
    
    // redimenssion
    //samplersBrightness.resize(xSampler*ySampler*xSize*ySize);
    

    
    
    // vider les fbo de tout contenu potentiel
    for (int i = 0; i<xSampler; i++){
        for (int j = 0; j<ySampler; j++){
        int k =j+ySampler*i;
            samplerFbo[k].begin();
            ofClear(0, 0, 0,0);
            samplerFbo[k].end();
            samplerFboH[k].begin();
            ofClear(0, 0, 0,0);
            samplerFboH[k].end();
            samplerFboS[k].begin();
            ofClear(0, 0, 0,0);
            samplerFboS[k].end();
            
            
        }
    }
    
}

void PixSampler::checkGuiChanged(){
    // parce que ce sont des param sensible qui doivent etre changer
    // dans l equivalent d'un malloc.
    // aussi parce que je n ai pas reussi a adequatement attacher un
    // attachEvent
    if (
        xSamplerGui!=xSampler||
        ySamplerGui!=ySampler||
        xSizeGui!=xSize||
        ySizeGui!=ySize
        ){
        xSampler =xSamplerGui;
        ySampler =ySamplerGui;
        xSize = xSizeGui;
        ySize = ySizeGui;
        allocFlag = 1;
    }

}


void PixSampler::update(ofFbo source, int x, int y){
    
    checkGuiChanged();
    
    if (allocFlag){allocateFbo();}
        
// passer a travers tout les x sampler et les y sampler dans l ordre
    // pour allouer la bonne partie d image (offset)
    //
    
    
    // convertir les fbo en pixel
   
    for (int i = 0; i<xSampler; i++){
        for (int j = 0; j<ySampler; j++){
            int k =j+ySampler*i;
            
            ofEnableBlendMode(OF_BLENDMODE_ALPHA);
            ofSetColor(255,255,255,255);
            
            samplerFboS[k].begin();
            ofClear(0);
//                source.draw(-x-i*xSize+xSampler*xSize/2,
//                        -y-j*ySize+ySampler*ySize/2,
//                        xResolution,
//                        yResolution
//                        );
            source.draw(-x-i*xSize+xSampler*xSize/2,
                        -y-j*ySize+ySampler*ySize/2,
                        xResolution,
                        yResolution
                        );
            samplerFboS[k].end();
            
            ofEnableBlendMode(OF_BLENDMODE_ADD);
            ofSetColor(255);
            
            samplerFbo[k].begin();
           
            ofClear(0);
            
            samplerFboH[k].draw(0,0,xSize,ySize);
            samplerFboS[k].draw(0,0,xSize,ySize);
            
            //samplerFbo[k].draw(0,0,xSize,ySize);


            samplerFbo[k].end();
   
            
        
            ofEnableBlendMode(OF_BLENDMODE_ADD);
            ofSetColor(255);
            
            samplerFboH[k].begin();
            
            samplerFbo[k].draw(0,0,xSize,ySize);
            samplerFboH[k].end();
            
            ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    
            
// lire le brightness dans les pixels
            // faire un gros tas de donne
            
            samplerFbo[k].readToPixels(samplerPixels[k]);
            
            for (int m = 0; m<xSize*ySize;m++){
                //samplersBrightness[m+xSize*ySize*k]=
                samplerBrightness[k][m]=
                    (samplerPixels[k][m*4]+
                     samplerPixels[k][m*4+1]+
                     samplerPixels[k][m*4+2])/3;
            }
          
            
        }

    }
}

void PixSampler::draw(int x, int y){
    
 
    ofSetColor(255,255,255,255);
    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    
    for (int i = 0; i<xSampler; i++){
        for (int j = 0; j<ySampler; j++){
             int k =j+ySampler*i;
            if(showCaramel){
            samplerFbo[k].draw(x+i*xSize*magnification,y+j*ySize*magnification,xSize*magnification,ySize*magnification);
            }else{
            samplerFboS[k].draw(x+i*xSize*magnification,y+j*ySize*magnification,xSize*magnification,ySize*magnification);
            }
        }
    }
    
    if(showSamplersBrightness){
        ofEnableBlendMode(OF_BLENDMODE_SCREEN);
        
        float rectWidth = float(xResolution)/float(samplerBrightness.size()*samplerBrightness[0].size());
        
        ofFill();
        ofSetColor(127,127,127,127);
        
        for (int i = 0; i<samplerBrightness.size();i++){
            for (int j = 0; j<samplerBrightness[i].size();j++){
                ofDrawRectangle(
                    i*rectWidth*samplerBrightness[i].size()+ j*rectWidth,yResolution-samplerBrightness[i][j],
                    rectWidth,
                    samplerBrightness[i][j]);
            }
        }

        ofNoFill();
        ofEnableBlendMode(OF_BLENDMODE_ALPHA);

    }
    
    ofSetColor(255, 255, 255, 255);
     samplerFboH[0].draw(10,10, 100, 100);
    


}

void PixSampler::printBrightness(){
    
    // broken

    for (int i = 0; i<samplerBrightness.size();i++){
        for (int j = 0; j<samplerBrightness[i].size();j++){
            cout<<samplerBrightness[i][j]<<endl;
        }
    }
    
    cout<<endl;
        cout<<samplerBrightness.size()*samplerBrightness[0].size()<<endl;
//    for (int i = 0; i<samplersBrightness.size(); i++){
//        
//        cout<<samplersBrightness[i]<<" ";
//        
//    }
//    cout<<endl;
//    cout<<samplersBrightness.size()<<endl;
    
}
