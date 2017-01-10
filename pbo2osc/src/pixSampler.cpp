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

    
    // alloc
    allocateFbo();
    

    
}

void PixSampler::setupGui(){
    // gui group
    
    guiSampler.setup("Sampler");
    guiSampler.setName("sampler");
    guiSampler.add(xSamplerGui.set("samplerX", 1, 1, 15));
    guiSampler.add(ySamplerGui.set("samplerY", 1, 1, 15));
    guiSampler.add(xSizeGui.set("pixelX", 15, 1, 100));
    guiSampler.add(ySizeGui.set("pixelY", 15, 1, 100));
    guiSampler.add(magnification.set("magnification", 10, 0.5, 20));
    guiSampler.add(showCaramel.set("showCaramel", 1, 0, 1));
    guiSampler.add(caramel.set("caramel", 0.5, 0.5, 1));
    guiSampler.add(pixSamplerOpacity.set("opacity", 1, 0., 1.));
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
        samplerFbo[i].allocate(xSize, ySize,  GL_RGBA);
        samplerFboH[i].allocate(xSize, ySize, GL_RGBA);
        samplerFboS[i].allocate(xSize, ySize, GL_RGBA);
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
    allocFlag = false;
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


void PixSampler::update(ofFbo source, int posX, int posY){
    
    checkGuiChanged();
    
    if (allocFlag){allocateFbo();}
    

// passer a travers tout les x sampler et les y sampler dans l ordre
    // pour allouer la bonne partie d image (offset)
    for (int i = 0; i<xSampler; i++){
        for (int j = 0; j<ySampler; j++){
            int k =j+ySampler*i;
            

            
            
            // init et calcul de la surface a sampler
            samplerFboS[k].begin();
               // ofClear(0);
                source.draw(-posX-i*xSize,
                            -posY-j*ySize,
                            xResolution,
                            yResolution);
            samplerFboS[k].end();
         
        
            samplerFbo[k].begin();
                ofSetColor(255, 255, 255, 255);
            
                samplerFboS[k].draw(0,0,xSize,ySize);
                samplerFboH[k].draw(0,0,xSize,ySize);
            samplerFbo[k].end();
            
            
            samplerFboH[k].begin();
            ofSetColor(0, 0, 0, (1-caramel)*255);
            ofDrawRectangle(0, 0, xSize, ySize);
            ofSetColor(255, 255, 255, caramel*255);
            samplerFbo[k].draw(0,0, xSize,ySize);
            //samplerFboH[k].draw(0,0, xSize,ySize);
            samplerFboH[k].end();


            
            //read le fbo actuel en pixels
            samplerFbo[k].readToPixels(samplerPixels[k]);
            
            // convertir en brightness et storer dans samplerbrightness
            for (int m = 0; m<xSize*ySize;m++){
                samplerBrightness[k][m]=
                    (samplerPixels[k][m*4]+
                     samplerPixels[k][m*4+1]+
                     samplerPixels[k][m*4+2])/3;
            }
        }
    }
}

void PixSampler::draw(int x, int y){
    
    ofPushStyle();
    
    ofSetColor(pixSamplerOpacity*255);
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
    
    ofPopStyle();
    ofSetColor(255);
    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    


}


void PixSampler::exit(){


}

