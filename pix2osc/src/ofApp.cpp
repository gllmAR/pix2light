#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    cout<<"start"<<endl;
    
    walker.addListener(this, &ofApp::walkerChanged);
    sampler.addListener(this, &ofApp::samplerChanged);
    cropWidth.addListener(this, &ofApp::cropWidthChanged);
    cropHeight.addListener(this, &ofApp::cropHeightChanged);
    hideMouse.addListener(this, &ofApp::hideMouseChanged);
    appFullScreen.addListener(this, &ofApp::appFullScreenChanged);
    
    ofSetVerticalSync(true);
    
    

    

    gui.setup("Pix2OSC");
    gui.add(hideMouse.set("hide Mouse",0, 0, 1));
    gui.add(appFullScreen.set("Fullscreen",0, 0, 1));
    gui.add(magnification.set( "magnification", 4, .01, 10 ));
    gui.add(cropWidth.set( "crop Width", 10, 1, 100 ));
    gui.add(cropHeight.set( "crop Height", 10, 1, 100 ));
    gui.add(sampler.set("sampler", 1, 1, 15));
    gui.add(palco.set("palco",1, 0, 1));
    gui.add(brightnessPalco.set("brightness Palco", 127, 0, 255));
    gui.add(trail.set("trail", 0.1, 0, 1));
    gui.add(showFBO.set("show Fbo", 0, 0, 1));
    gui.add(walker.set("Walker", 0, 0, 1));
    gui.add(speedX.set("speedX", 0.1, -10, 10));
    gui.add(speedY.set("speedY", 0.1, -10, 10));

    //gui.add(mouvement.set("mouvement", 0, 0, 1));
    
   // gui.add(fboOverlay.set( "FBO overlay", .5, .0, 1. ));
    
    source.load("space0.jpg");

    imgHeight =source.getHeight();
    imgWidth = source.getWidth();
    imgRatio = source.getHeight()/ source.getWidth();
    canvasWidth = ofGetWindowWidth();
    canvasHeight = ofGetWindowHeight();
    
    sender.setup(HOST, PORT);
    gui.loadFromFile("settings.xml");
    init = false;

    cout<<"finishSetup"<<endl;
}

void ofApp::samplerChanged(int & sampler){
    alloc = true;
    }


void ofApp::cropWidthChanged(int & cropWidth){
     crop[2]=cropWidth;
    alloc = true;
}


void ofApp::cropHeightChanged(int & cropHeight){
    crop[3]=cropHeight;
    alloc = true;
}

void ofApp::hideMouseChanged(bool & hideMouse){
    if(hideMouse){
        ofHideCursor();
    }else{
        ofShowCursor();
    }
}

void ofApp::appFullScreenChanged(bool & appFullScreen){
    
    fullscreenFlag=1;

}

void ofApp::walkerChanged(bool & walker){

}



void ofApp::allocFbo(){
    
    crop[2]=cropWidth;
    crop[3]=cropHeight;


    destination.resize(sampler);
    frameBuffer.resize(sampler);
    frameBufferH.resize(sampler);
    pixels.resize(sampler);

    
    
    for(int i = 0; i<sampler ; i++){
        frameBuffer[i].allocate(crop[2],crop[3],GL_RGB);
        frameBufferH[i].allocate(crop[2],crop[3],GL_RGB);
    }

    alloc = false;
    
    cout<<"finiAlloc"<<endl;


}


//--------------------------------------------------------------
void ofApp::update(){
    

    

    if(alloc){allocFbo();}
    

    if (!alloc){
    
    if (walker){
        
        
        
        float xPos = ofMap(sin(ofGetElapsedTimeMillis()*speedX*0.00001+3.14), -1, 1, 0.5*crop[2], canvasWidth-sampler*crop[2]*magnification - 0.5*crop[2]);
        float yPos = ofMap(cos(ofGetElapsedTimeMillis()*speedY*0.00001+3.14), -1, 1, 0.5*crop[3], canvasHeight-crop[3]*magnification -0.5*crop[3]);
        
        crop[0] =ofClamp(xPos, 0, canvasWidth);
        crop[1] =ofClamp(yPos, 0, canvasHeight);
    }
    
    
    ofxOscMessage m;
    m.setAddress("/pix");
    ofxOscMessage n;
    n.setAddress("/avg");

    // lire la valeur de brightness dans framme buffer et append la valeur dans un message OSC
    
    for (int i = 0; i<sampler;i++){
        
        int sampleX =ofClamp(crop[0],0,imgWidth)+ofClamp(i*crop[2],0,imgHeight);
       // cout<<"sampleX "<<sampleX<<endl;
       // cout<<"sampleX "<<crop[1]<<endl;
        
        destination[i].cropFrom(source, sampleX, crop[1], crop[2], crop[3]);
        frameBuffer[i].readToPixels(pixels[i]);
       int rgb [3]{0,0,0};
        
        // calculer l'etendu de ce qui a a faire
        int maxJ =pixels[i].getWidth()*pixels[i].getHeight() * pixels[i].getNumChannels();
        //cout<<maxJ<<endl;
    
        if (maxJ!=0){

        // ici -2 au depart de j pour ajuster le offset.....?
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
            
            m.addIntArg(brightnessPalco);
            //m.addIntArg(255-palcoBrightness*rgb[2]/(maxJ/3)/255 );// bright
            
           //cout<<255-(rgb[0]+rgb[1]+rgb[2])/(maxJ)<<endl;
           
            m.addIntArg(255-rgb[2]/(maxJ/3));   // R
            //cout<<"r"<<255-rgb[2]/(maxJ/3)<<"g"<<(255-rgb[0]/(maxJ/3))<<"b"<<(255-rgb[1]/(maxJ/3))<<endl;
            m.addIntArg(255-rgb[0]/(maxJ/3));   // g
            m.addIntArg(255-rgb[1]/(maxJ/3));   // b
            m.addIntArg(0);                 // Color corection
            m.addIntArg(0);                 // internal program
            m.addIntArg(0);                 // color mode
        
        }
        }

 sender.sendMessage(m, false);
sender.sendMessage(n, false);

    }
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
    
    if (fullscreenFlag){
        ofToggleFullscreen();
        fullscreenFlag = 0;
        canvasWidth = ofGetWindowWidth();
        canvasHeight = ofGetWindowHeight();
    }

    
    if (!alloc){
    source.draw(0, 0);
    

    
    // calculer le offset et la magnification
    for (int i = 0; i < sampler; i++){
        
        int dX = crop[0]+(crop[2]/2) - crop[2]*magnification/2 +i*crop[2]*magnification ;
        int dY = crop[1]+(crop[3]/2) - crop[3]*magnification/2;
        int dW = crop[2]*magnification;
        int dH = crop[3]*magnification;
    
       // destination[i].draw(dX,dY,crop[2], crop[3]);
        
        frameBuffer[i].begin();
            ofClear(0.);
            ofEnableBlendMode(OF_BLENDMODE_ADD);
            ofSetColor(trail*255);
            frameBufferH[i].draw(0,0,crop[2], crop[3]);
        ofSetColor(ofClamp(255-trail*254,0,255));
            destination[i].draw(0,0,crop[2], crop[3]);
        frameBuffer[i].end();
        
        frameBufferH[i].begin();
        ofClear(0.);
            frameBuffer[i].draw(0,0,crop[2], crop[3]);
        frameBufferH[i].end();
        
        
        if (showFBO){
        frameBuffer[i].draw(dX,dY,dW, dH);
        }
        if (!showFBO){
            destination[i].draw(dX,dY,dW, dH);
        }
        ofNoFill();
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
    if (key == 'h'){
        hideMouse = !hideMouse;
    }
    
    if (key == 'f'){
        appFullScreen = !appFullScreen;
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
    canvasWidth = w;
    canvasHeight = h;


}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
