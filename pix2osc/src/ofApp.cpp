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
    gui.add(sampler.set("sampler", 2, 1, 15));
    gui.add(palco.set("palco",1, 0, 1));
    //gui.add(brightnessPalco.set("brightPalco", 127, 0, 255));
   // gui.add(fboOverlay.set( "FBO overlay", .5, .0, 1. ));
    
    



    
    
    source.load("space3.jpg");
    imgHeight =source.getHeight();
    imgWidth = source.getWidth();
    imgRatio = source.getHeight()/ source.getWidth();
    canvasWidth = ofGetWindowWidth();
    canvasHeight = ofGetWindowHeight();
   
    
  
    
    
    sender.setup(HOST, PORT);
    


    gui.loadFromFile("settings.xml");
    
    frameBuffer.begin();
    frameBuffer.resize(sampler);
    frameBuffer.clear();
    
    for(int i; i<sampler ; i++){
        frameBuffer[i].allocate(crop[2],crop[3],GL_RGB);
    }
    pixels.resize(sampler);
    
        init = false;
}

void ofApp::samplerChanged(int & sampler){
    destination.resize(sampler);
    reallocFrameBuffer();
}


void ofApp::cropWidthChanged(int & cropWidth){
     crop[2]=cropWidth;
    reallocFrameBuffer();
}


void ofApp::cropHeightChanged(int & cropHeight){
    crop[3]=cropHeight;
    reallocFrameBuffer();
}

void ofApp::reallocFrameBuffer(){
    
    
    if (!init){
        alloc = true;
    }
}


//--------------------------------------------------------------
void ofApp::update(){
    

    if(alloc){
        frameBuffer.begin();
        frameBuffer.resize(sampler);
        frameBuffer.clear();
        
        for(int i; i<sampler ; i++){
            frameBuffer[i].allocate(crop[2],crop[3],GL_RGB);
        }
        pixels.resize(sampler);
        alloc = false;
    }
    
    
    if (walker){
        crop[0] =ofClamp(crop[0]+ofRandom(-1,2), 0, canvasWidth);
        crop[1] =ofClamp(crop[1]+ofRandom(-1,2), 0, canvasHeight);
    }
    
    ofxOscMessage m;
    m.setAddress("/pix");
    ofxOscMessage n;
    n.setAddress("/avg");

    // lire la valeur de brightness dans framme buffer et append la valeur dans un message OSC
    
    for (int i = 0; i<sampler;i++){
        destination[i].cropFrom(source, ofClamp(crop[0],0,imgWidth) +ofClamp(i*crop[2],0,imgHeight), crop[1], crop[2], crop[3]);
        frameBuffer[i].readToPixels(pixels[i]);
       int rgb [3]{0,0,0};
        
        // calculer l'etendu de ce qui a a faire
        int maxJ =pixels[i].getWidth()*pixels[i].getHeight() * pixels[i].getNumChannels();
    

        
        for (int j = -2; j<=maxJ; j=j+3){
            float br = (pixels[i][j]+pixels[i][j+1]+pixels[i][j+2])/3;
            rgb[0] = rgb[0]+pixels[i][j];
            rgb[1] = rgb[1]+pixels[i][j+1];
            rgb[2] = rgb[2]+pixels[i][j+2];
            m.addIntArg(br);
    }
        if (palco){
            int palcoBrightness = (rgb[0]+rgb[1]+rgb[2])/(maxJ);
            m.addIntArg(255);               //Shutter, strobe:
            m.addIntArg(255-palcoBrightness );// bright
            
           //cout<<255-(rgb[0]+rgb[1]+rgb[2])/(maxJ)<<endl;
           
            m.addIntArg(255-palcoBrightness*rgb[2]/(maxJ/3)/255);   // R
            m.addIntArg(255-palcoBrightness*rgb[0]/(maxJ/3)/255);   // g
            m.addIntArg(255-palcoBrightness*rgb[1]/(maxJ/3)/255);   // b
            m.addIntArg(0);                 // Color corection
            m.addIntArg(0);                 // internal program
            m.addIntArg(0);                 // color mode
        
        }

 sender.sendMessage(m, false);
sender.sendMessage(n, false);

}
}

    // THE OLD WAY pour lire ce qu'il y a comme valeur de brightness dans l'image
    
    //    for (int i = 0; i < sampler; i++){
    //
    //    destination[i].cropFrom(source, crop[0] +i*crop[2], crop[1], crop[2], crop[3]);
    //    numPixels = crop[2]*crop[3];
    //
    //    ofPixels & loadedPixels = destination[i].getPixels();
    //    int numChannels = loadedPixels.getNumChannels();
    //
    //    if(numChannels >= 3)
    //    {
    //        for (int i=0; i<numPixels; i++)
    //        {
    //            int pix = i * numChannels;
    //            int r_totalPixelVal = loadedPixels[pix]; // red pixels
    //            int g_totalPixelVal = loadedPixels[pix+1]; // green pixels
    //            int b_totalPixelVal = loadedPixels[pix+2]; // blue pixels
    //            int gs_averagePixelVal =(r_totalPixelVal+g_totalPixelVal+b_totalPixelVal)/3;
    //            m.addIntArg(gs_averagePixelVal);
    //        }
    //    }
    //
    //    else if (numChannels == 1 )
    //    {
    //        for (int i=0; i<numPixels; i++)
    //        {
    //            int gs_totalPixelVal = loadedPixels[i]; // grayscale
    //        }
    //    };
    //        
    //    }
    



//--------------------------------------------------------------
void ofApp::draw(){
    source.draw(0, 0);
    

    
    // calculer le offset et la magnification
    for (int i = 0; i < sampler; i++){
        
        int dX = crop[0]+(crop[2]/2) - crop[2]*magnification/2 +i*crop[2]*magnification ;
        int dY = crop[1]+(crop[3]/2) - crop[3]*magnification/2;
        int dW = crop[2]*magnification;
        int dH = crop[3]*magnification;
    
        destination[i].draw(dX,dY,crop[2], crop[3]);
        
        frameBuffer[i].begin();
        destination[i].draw(0,0,crop[2], crop[3]);
        frameBuffer[i].end();
        
        
       
        frameBuffer[i].draw(dX,dY,dW, dH);
        ofDrawRectangle(dX,dY,dW, dH);
    }
    
    
    ofEnableAlphaBlending();
    ofEnableBlendMode(OF_BLENDMODE_SCREEN);
    
    ofSetColor(255, 255, 255, 255);
    ofSetLineWidth(1);
    ofNoFill();
        ofDisableAlphaBlending();

    
        if (alloc){
        
        }
    
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
