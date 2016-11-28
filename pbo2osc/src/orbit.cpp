//
//  orbit.cpp
//  pbo2osc
//
//  Created by Guillaume Arseneault on 16-11-05.
//
//

#include "orbit.hpp"

void Orbit::setup(int w,int h){
    
    
    
    guiOrbit.setup("orbit");
    guiOrbit.setName("orbit");
    guiOrbit.add(applyOrbit.set("apply Orbit ", 1, 0, 1));
    guiOrbit.add(xOrbitSpeed.set("x Orbit Speed ", 1, 0, 50));
    guiOrbit.add(yOrbitSpeed.set("y Orbit Speed ", 1, 0, 50));
    guiOrbit.add(trailShow.set("show trail", 1, 0, 1));
    guiOrbit.add(trailAmmount.set("trail Ammount ", 0, 0, 1));
    guiOrbit.add(trailSize.set("trail Size",1 ,0, 25 ));
    guiOrbit.add(trailReset.setup("trail Reset"));


    resize(w,h);
    trailReset.addListener(this, &Orbit::trailResetChanged);

}

ofPoint Orbit::update(ofPoint cursorPos, int w, int h, int xSampler, int ySampler, int xSamplerRes, int ySamplerRes, float magnification ) {
    
    // calcul le centre du curseur
    int cursorCentreX = cursorPos.x +xSampler*xSamplerRes/2*magnification;
    int cursorCentreY = cursorPos.y +ySampler*ySamplerRes/2*magnification;
    
    cursorCentre.set(cursorCentreX,cursorCentreY);
    
    // updater les fbo
    
    if (trailShow){
        
        
        trailFbo.begin();
        ofEnableBlendMode(OF_BLENDMODE_ALPHA);
        
        ofClear(0);
        ofSetColor(trailAmmount*255);
        trailFboH.draw(0,0,canvasWidth,canvasHeight);

        
        ofFill();
        ofDrawRectangle(cursorCentre, trailSize, trailSize);
        trailFbo.end();
        
        
        trailFboH.begin();
        ofSetColor(255);
        ofEnableBlendMode(OF_BLENDMODE_ADD);
        trailFbo.draw(0,0,canvasWidth,canvasHeight);
        trailFboH.end();
        
    }
    
    
    // faire deriver l orbit
    if(applyOrbit){
        
        xLfoAccum = xLfoAccum+1;
        yLfoAccum = yLfoAccum+1;

        int time =ofGetElapsedTimeMillis();
        

        
      
        xPos = ofMap(sin(time*xOrbitSpeed*0.00001+3.1416),
                  -1,
                  1,
                  0,
                  w-xSampler*xSamplerRes *magnification);
        
        yPos = ofMap(cos(time*yOrbitSpeed*0.00001+3.1416),
                     -1,
                     1,
                     0,
                     h-ySampler*ySamplerRes*magnification );
        
        
        cursorPos.set(xPos, yPos);
        
    
        return cursorPos;
    } else{
        return cursorPos;
    }
    
    
}

void Orbit::draw(){
    
    if (trailShow){
        trailFbo.draw(0,0,canvasWidth,canvasHeight);
    }


}

void Orbit::resize(int width, int height){
    canvasWidth = width;
    canvasHeight = height;
    trailFbo.allocate(canvasWidth, canvasHeight, GL_RGBA);
    trailFboH.allocate(canvasWidth, canvasHeight, GL_RGBA);
}


void Orbit::trailResetChanged(){
    trailFboH.begin();
    ofClear(0);
    trailFboH.end();
}
