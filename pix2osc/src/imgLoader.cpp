//
//  imgLoader.cpp
//  pix2osc
//
//  Created by Guillaume Arseneault on 16-10-16.
//
//

#include "imgLoader.hpp"

void imgLoader::setup(string folder){
    
    
    images.resize(3);
    imgWidth.resize(3);
    imgHeight.resize(3);
    
    string path = folder;
    ofDirectory dir(path);
    dir.allowExt("jpg");
    dir.listDir();
    dir.sort();
    dir.listDir();
    frameTotal = dir.size();
    
    // erreur a catcher s'il n y a pas de folder.
    
    // storer les path des images dans un vector de string
    for (int i = 0; i < dir.size(); i++){
        imagePath.push_back (dir.getPath(i));
    }
    
    
    // identifier la resolution optimale afin d allouer un fbo assez grand
    
    swapperFbo.allocate(1920, 1080, GL_RGBA);
    
    

    
}


void imgLoader::load(int id, int index){
    
    
     for(int i = 0; i< images.size(); i++ ){
         
    loader.loadFromDisk(images[id+i], imagePath[index+i]);

    cout<<"loading "<< imagePath[index]<<" in "<<id<<" "<<imgHeight[id+i]<<" X "<< imgWidth[id+i]<<endl;

         
     }

}


void imgLoader::next(){
// loader dans une slot vide une image next, partir la transition vers la next
    //nextFrame = 1;
    
    if(lastDirection == -1) {
        frameNow = (frameNow+frameTotal+3)%frameTotal;
        cout << "vers +"<<endl;
    }
    
    else {
        frameNow = (frameNow+frameTotal+1)%frameTotal;
        
    }
    playHead = (playHead+images.size()+1)%images.size();
    loadHead = (playHead+images.size()+1)%images.size();
    loader.loadFromDisk(images[loadHead], imagePath[frameNow]);
    
    
    cout<< "frame now " << frameNow << " playHead " <<playHead << " loadHead "<< loadHead << " path "<<imagePath[frameNow]<< endl;
    lastDirection = 1;
    
}

void imgLoader::prev(){
// loader dans une slot vide une image prev, partir la transition vers la prev
    //prevFrame = 1;
    
    //prevFrame = 0 ;
    
    if (lastDirection == 1 ){
        frameNow = (frameNow+frameTotal-3)%frameTotal;
        cout << "arg-----"<<endl;
    }
    else {
        frameNow = (frameNow+frameTotal-1)%frameTotal;
    }
    
    playHead = (playHead+images.size()-1)%images.size();
    loadHead = (playHead+images.size()-1)%images.size();
    loader.loadFromDisk(images[loadHead], imagePath[frameNow]);
    
    //loader.loadFromDisk(images[loadHead], "of"+ofToString(frameNow)+".JPG");
    cout<< "frame now " << frameNow << " playHead " <<playHead << " loadHead "<< loadHead << " path "<<imagePath[frameNow]<< endl;
    
    lastDirection = -1;
}


void imgLoader::update(){
    

    swapperFbo.begin();
    ofClear(0);
    ofSetColor(255);
    images[playHead].draw(0, 0, swapperFbo.getWidth() , swapperFbo.getHeight());
    
    // draw the array of images
    for(int i = 0; i < (int)images.size(); ++i) {
        int x = (i%8);
        int y = (i/8);
        images[i].draw(x*64,y*64, 64,64);
    }
    
    ofSetColor(255, 0, 0);
    ofDrawRectangle(playHead*64+32, 64, 10, 10);
    
    
    // draw the FPS
    ofDrawRectangle(0,ofGetHeight()-20,30,20);
    
    ofSetColor(0);
    ofDrawBitmapString(ofToString(ofGetFrameRate(),0),5,ofGetHeight()-5);
    
    
    swapperFbo.end();
   

}

void imgLoader::draw(){
    
    
    
    swapperFbo.draw(0, 0, 640,480);
    

    
    

}
