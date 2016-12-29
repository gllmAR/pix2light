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
    guiOrbit.add(trailOpacity.set("trail Opacity ", 0, 0, 1));
    guiOrbit.add(trailFuzz.set("trail Fuzz",1 ,0, 1 ));
    guiOrbit.add(trailLength.set("trail Length",200 ,200, 100000 ));
    guiOrbit.add(trailReset.setup("trail Reset"));


    resize(w,h);
    trailReset.addListener(this, &Orbit::trailResetChanged);
    trailPath.setMode(ofPath::POLYLINES);
}

ofPoint Orbit::update(ofPoint cursorPos, int w, int h, int xSampler, int ySampler, int xSamplerRes, int ySamplerRes, float magnification ) {
    
    // calcul le centre du curseur
    int cursorCentreX = cursorPos.x +xSampler*xSamplerRes/2*magnification;
    int cursorCentreY = cursorPos.y +ySampler*ySamplerRes/2*magnification;
    
    cursorCentre.set(cursorCentreX,cursorCentreY);
    
    trailLine.addVertex(cursorCentre);

    for (auto &vert : trailLine.getVertices()){
        vert.x += ofRandom(-0.1*trailFuzz,0.1*trailFuzz);
        vert.y += ofRandom(-0.1*trailFuzz,0.1*trailFuzz);
        
    }
    
    if (trailLine.size() > trailLength){
        
        for (int i = 0;i<trailLine.size()-trailLength;i++){
            trailLine.getVertices().erase(trailLine.getVertices().begin());
        }
        
        
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
    
//    if (trailShow){
//        trailFbo.draw(0,0,canvasWidth,canvasHeight);
//    }
    
    if(trailShow){
        
        ofSetColor(trailOpacity*255, trailOpacity*255, trailOpacity*255);
        trailLine.draw();
    }


}

void Orbit::resize(int width, int height){
//    canvasWidth = width;
//    canvasHeight = height;
//    trailFbo.allocate(canvasWidth, canvasHeight, GL_RGBA);
//    trailFboH.allocate(canvasWidth, canvasHeight, GL_RGBA);
}


void Orbit::trailResetChanged(){

    
    trailLine.clear();
}
