#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetVerticalSync(true);
    
    
    sampler.addListener(this, &ofApp::samplerChanged);
    cropWidth.addListener(this, &ofApp::cropWidthChanged);
    cropHeight.addListener(this, &ofApp::cropHeightChanged);


    gui.setup("panel"); // most of the time you don't need a name but don't forget to call setup
    gui.add(magnification.set( "magnification", 4, .01, 10 ));
    gui.add(cropWidth.set( "crop Width", 10, 1, 100 ));
    gui.add(cropHeight.set( "crop Height", 10, 1, 100 ));
    gui.add(sampler.set("sampler", 1, 1, 15));
  

    
    source.load("darkrift.jpg");
    imgHeight =source.getHeight();
    imgWidth = source.getWidth();
    imgRatio = source.getHeight()/ source.getWidth();
    canvasWidth = ofGetWindowWidth();
    canvasHeight = ofGetWindowHeight();
    gui.loadFromFile("settings.xml");
    
    sender.setup(HOST, PORT);
    
}

void ofApp::samplerChanged(int & sampler){
    destination.resize(sampler);
    
}


void ofApp::cropWidthChanged(int & cropWidth){
     crop[2]=cropWidth;

}


void ofApp::cropHeightChanged(int & cropHeight){
    crop[3]=cropHeight;
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    if (walker){
        crop[0] =ofClamp(crop[0]+ofRandom(-1,2), 0, canvasWidth);
        crop[1] =ofClamp(crop[1]+ofRandom(-1,2), 0, canvasHeight);
    }
    
    ofxOscMessage m;
    m.setAddress("/pix");

    
    for (int i = 0; i < sampler; i++){
    
    destination[i].cropFrom(source, crop[0] +i*crop[2], crop[1], crop[2], crop[3]);
    numPixels = crop[2]*crop[3];
    
    ofPixels & loadedPixels = destination[i].getPixels();
    int numChannels = loadedPixels.getNumChannels();
    
    if(numChannels >= 3)
    {
        for (int i=0; i<numPixels; i++)
        {
            int pix = i * numChannels;
            int r_totalPixelVal = loadedPixels[pix]; // red pixels
            int g_totalPixelVal = loadedPixels[pix+1]; // green pixels
            int b_totalPixelVal = loadedPixels[pix+2]; // blue pixels
            int gs_averagePixelVal =(r_totalPixelVal+g_totalPixelVal+b_totalPixelVal)/3;
            m.addIntArg(gs_averagePixelVal);
        }
    }
    
    else if (numChannels == 1 )
    {
        for (int i=0; i<numPixels; i++)
        {
            int gs_totalPixelVal = loadedPixels[i]; // grayscale
        }
    };
        
    }
    sender.sendMessage(m, false);

  

}

//--------------------------------------------------------------
void ofApp::draw(){
    source.draw(0, 0);
    

    
    for (int i = 0; i < sampler; i++){
        
        int dX = crop[0]+(crop[2]/2) - crop[2]*magnification/2 +i*crop[2]*magnification ;
        int dY = crop[1]+(crop[3]/2) - crop[3]*magnification/2;
        int dW = crop[2]*magnification;
        int dH = crop[3]*magnification;
    

    destination[i].draw(dX,dY,dW, dH);
    
    ofDrawRectangle(dX,dY,dW, dH);
    }
    
    ofEnableAlphaBlending();
    ofEnableBlendMode(OF_BLENDMODE_SCREEN);
    
    ofSetColor(255, 255, 255, 255);
    ofSetLineWidth(1);
    ofNoFill();
        ofDisableAlphaBlending();
    
    if( !guiHide ){
        gui.draw();
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    if( key == 'g' ){
        guiHide = !guiHide;
    }
    if(key == 's') {
        gui.saveToFile("settings.xml");
    }
    if(key == 'l') {
        gui.loadFromFile("settings.xml");
    }
    if (key == 'm' ){
        mouseAttached = !mouseAttached;
    }
    if (key == 'w'){
        walker = !walker;
    }


}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
    if (mouseAttached){
    
    if (x > 0 && x < imgWidth)
    {
        crop[0]=x;
    }
    
    if (y > 0 && y < imgHeight)
    {
        crop[1]=y;
    }
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


}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
