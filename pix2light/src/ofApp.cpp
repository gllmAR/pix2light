#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){
    
    updateWindowSize();

    // setups Classes
    
    imgLoader.setup(640,480);
    imgLoader.loadDir("calib");
    pixSampler.setup(2, 2, 15, 15, imgLoader.canvasFbo);
    orbit.setup(640,480);
    
    // Setup GUIS
    pixSampler.setupGui();
    toArtnet.setupGui();
    imgLoader.setupGui();

    // build settings guiGroup
    settings.setup("settings");
    settings.setName("settings");
    settings.add(savePresetToXml.setup("savePreset"));
    savePresetToXml.addListener(this, &ofApp::savePreset);
    settings.add(mouseControlled.set("mouseCtl", 1, 0, 1));
    settings.add(screenShotFlag.set("screenShot", 0, 0, 1));
    
    // Build Gui
    gui.setup("pix2light");
    gui.setName("pix2light");
    gui.add(&settings);
    gui.add(&imgLoader.imgLoaderGui);
    gui.add(&orbit.guiOrbit);
    gui.add(&orbit.guiTrail);
    gui.add(&pixSampler.guiSampler);
    gui.add(&toArtnet.guiArtnet);
    
    //  Read settings
    gui.loadFromFile("settings.xml");
    
    // setup artnet with readed settings
    toArtnet.setup(pixSampler.xSampler, pixSampler.ySampler);

    // setup Sync
    sync.setup((ofParameterGroup&)gui.getParameter(),6666,"localhost",6667);
    
    // set fullscreen on start
    ofToggleFullscreen();
    updateWindowSizeFlag = true ;
}

//--------------------------------------------------------------
void ofApp::update(){
    imgLoader.update();
    cursorPos = orbit.update(cursorPos,  appWidth , appHeight, pixSampler.xSampler, pixSampler.ySampler, pixSampler.xSize, pixSampler.ySize,  pixSampler.magnification);
    
    pixSampler.update(imgLoader.canvasFbo, cursorPos.x, cursorPos.y);
    toArtnet.update(pixSampler.samplerBrightness);
    
    sync.update();

}

//--------------------------------------------------------------
void ofApp::draw(){
    imgLoader.draw(0,0,appWidth,appHeight);
    ofSetColor(255);
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    orbit.draw();
    
    pixSampler.draw(cursorPos.x, cursorPos.y);
    toArtnet.draw(pixSampler.samplerBrightness);
    
    if (screenShotFlag){takeScreenShot();}
    if (guiShow){
        gui.draw();
        ofShowCursor();
    } else {
        ofHideCursor();
    }
    if (updateWindowSizeFlag){updateWindowSize();}
}
//--------------------------------------------------------------

void ofApp::exit(){
    imgLoader.exit();
    toArtnet.exit();
    cout<<"exiting"<<endl;

}

//--------------------------------------------------------------

void ofApp::updateWindowSize(){
    
    appWidth = ofGetWidth();
    appHeight = ofGetHeight();
    imgLoader.resize(appWidth, appHeight);
    pixSampler.resizeResolution(imgLoader.canvasFbo);
    orbit.resize(appWidth, appHeight);
    toArtnet.resize(appWidth, appHeight);
    
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
    

    if(key == 'e'){
        
       // cout<<pixSampler.samplersBrightness[1]<<endl;
    }
    
    if(key == 'f'){
        ofToggleFullscreen();
        updateWindowSizeFlag = true ;
    }
    if(key == 'g'){
        guiShow = !guiShow;
    }
    
    if(key == 'x'){
        screenShotFlag = true;
            }

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}


//--------------------------------------------------------------

void ofApp::takeScreenShot(){
//    screenGrab.grabScreen(0, 0 , ofGetWidth(), ofGetHeight());
    // bug avec le fullscreen
    screenGrab.grabScreen(0, 0 ,1920, ofGetHeight());
    cout<<ofGetTimestampString()<<endl;
    screenGrab.save("screenShots/"+(ofGetTimestampString()+".png"));
    screenShotFlag = false;
}

//--------------------------------------------------------------


void ofApp::savePreset(){

    gui.saveToFile("settings.xml");
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
