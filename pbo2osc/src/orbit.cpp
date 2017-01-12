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
    guiOrbit.add(applyOrbit.set("active", 1, 0, 1));
    guiOrbit.add(xOrbitSpeed.set("speedX", 1, 0, 50));
    guiOrbit.add(yOrbitSpeed.set("speedY", 1, 0, 50));
    guiOrbit.add(lfoX.set("lfoX", 0, -0.01, 0.01));
    guiOrbit.add(lfoY.set("lfoY", 0, -0.01, 0.01));
    guiOrbit.add(shuffleLfo.setup("shuffleLfo"));
    shuffleLfo.addListener(this, &Orbit::shuffle);
    guiOrbit.add(shuffleRange.set("shuffleRange", 0.01, 0.0, 1.0));
    
    guiTrail.setup("trail");
    guiTrail.setName("trail");
    guiTrail.add(trailShow.set("show", 1, 0, 1));
    guiTrail.add(trailReset.setup("reset"));
    guiTrail.add(trailLength.set("length",200 ,200, 100000 ));
    guiTrail.add(trailFuzz.set("fuzz",1 ,0, 1 ));
    guiTrail.add(trailOpacity.set("opacity", 0, 0, 1));


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
        
        trailLfoX = cos(ofGetFrameNum()*lfoX+3.1416);
        trailLfoY = cos(ofGetFrameNum()*lfoY+3.1416);
        

        int time =ofGetElapsedTimeMillis();
        

        xPos = ofMap(trailLfoX*sin(time*xOrbitSpeed*0.00001+3.1416),
                  -1,
                  1,
                  0,
                  w-xSampler*xSamplerRes *magnification);
        
        yPos = ofMap(trailLfoY*cos(time*yOrbitSpeed*0.00001+3.1416),
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
    

    
    if(trailShow){
        
        ofSetColor(trailOpacity*255, trailOpacity*255, trailOpacity*255);
        trailLine.draw();
    }


}

void Orbit::resize(int width, int height){
}


void Orbit::trailResetChanged(){
    trailLine.clear();
}

void Orbit::shuffle(){
    float calculLfoX = lfoX + ofRandom(-1., 1.)*shuffleRange*0.01;
    lfoX = ofClamp(calculLfoX, -0.01, 0.01);
    float calculLfoY = lfoY + ofRandom(-1., 1.)*shuffleRange*0.01;
    lfoY = ofClamp(calculLfoY, -0.01, 0.01);
}
