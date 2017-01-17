//
//  annotation.cpp
//  pix2light
//
//  Created by Guillaume Arseneault on 17-01-12.
//
//

#include "annotation.hpp"

void Annotation::setup(){
    ofTrueTypeFont::setGlobalDpi(72);
    myFont.load("fonts/verdana.ttf", fontSize, true, true);
    myFont.setLineHeight(fontLineHeight);
    myFont.setLetterSpacing(fontLetterSpacing);

}

void Annotation::loadXml(string imgName){

    if( XML.loadFile("annotations.xml") ){
        annotationText = XML.getValue(imgName, "");
    }else{
        cout<<"unable to load annotation.xml check data/ folder"<<endl;
    }

}


void Annotation::setupGui(){
    annotationGui.setup("annotation");
    annotationGui.setName("annotation");
    annotationGui.add(fontSize.set("fontSize",14 ,4 ,48));
    annotationGui.add(fontLetterSpacing.set("fontLetterSpacing",1 ,0.5 ,2));
    annotationGui.add(posX.set("posX",0.5,0.0,1.0));
    annotationGui.add(posY.set("posY",0.5,0.0,1.0));
    annotationGui.add(fontColor.set("fontColor", ofColor(100,100,140, 100),ofColor(0,0),ofColor(255,255)));
    

}

void Annotation::update(string imgLoaderImageString){
    if (imgLoaderImageString != oldImgName){
        loadXml(imgLoaderImageString);
        oldImgName = imgLoaderImageString;
    }
    
    if (fontSize!=oldFontSize || fontLineHeight!=oldFontLineHeight ||fontLetterSpacing != oldFontLetterSpacing ){
        setup();
        oldFontSize = fontSize;
        oldFontLineHeight = fontLineHeight;
        oldFontLetterSpacing = fontLetterSpacing;
    }
   
    
    
    
}

void Annotation::draw(){
    ofPushStyle();
    ofSetColor(fontColor);
    myFont.drawString(annotationText, appWidth*posX, appHeight*posY);
    
    ofPopStyle();
}


void Annotation::resize(int w, int h){
    appWidth = w;
    appHeight = h;

}
