#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){
    
    updateWindowSize();

    imgLoader.setup(640,480);
    imgLoader.loadDir("calib");
    pixSampler.setup(2, 2, 15, 15, imgLoader.canvasFbo);
    orbit.setup(640,480);
    toArtnet.setup(pixSampler.xSampler, pixSampler.ySampler);
    // Setup GUIS
    

    
    gui.setup("Pbo2OSC");
    gui.setName("settings");
    gui.add(mouseControlled.set("mouseControlled  ", 1, 0, 1));
    gui.add(&orbit.guiOrbit);
    gui.add(&pixSampler.guiSampler);
    
    // GetSettings
    gui.loadFromFile("settings.xml");
    
}

//--------------------------------------------------------------
void ofApp::update(){
    imgLoader.update();
    cursorPos = orbit.update(cursorPos,  appWidth , appHeight, pixSampler.xSampler, pixSampler.ySampler, pixSampler.xSize, pixSampler.ySize,  pixSampler.magnification);
    
    pixSampler.update(imgLoader.canvasFbo, cursorPos.x, cursorPos.y);
    toArtnet.update(pixSampler.xSampler, pixSampler.ySampler, pixSampler.xSize, pixSampler.ySize, pixSampler.samplerBrightness);
    

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetColor(255);
    
    imgLoader.canvasFbo.draw(0,0,appWidth,appHeight);
    ofSetColor(255);
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    orbit.draw();
    
    pixSampler.draw(cursorPos.x, cursorPos.y);
    
    
    gui.draw();
    if (updateWindowSizeFlag){updateWindowSize();}
}
//--------------------------------------------------------------

void ofApp::updateWindowSize(){
    
    appWidth = ofGetWidth();
    appHeight = ofGetHeight();
    imgLoader.resize(appWidth, appHeight);
    pixSampler.resizeResolution(imgLoader.canvasFbo);
    orbit.resize(appWidth, appHeight);
    
    updateWindowSizeFlag=false;
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    if(key == OF_KEY_RIGHT){
        imgLoader.next();
    }
    
    if(key == OF_KEY_LEFT){
        imgLoader.prev();
    }
    
    if(key == 'p'){
        pixSampler.printBrightness();
    }
    if(key == 'e'){
        
       // cout<<pixSampler.samplersBrightness[1]<<endl;
    }
    
    if(key == 'f'){
        ofToggleFullscreen();
        updateWindowSizeFlag = true ;
    }

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
    if (mouseControlled){
    
    cursorPos.set(x,y);
    
    }


}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
     updateWindowSizeFlag = true ;
}
//--------------------------------------------------------------




//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
