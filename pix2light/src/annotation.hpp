//
//  annotation.hpp
//  pix2light
//
//  Created by Guillaume Arseneault on 17-01-12.
//
//

#ifndef annotation_hpp
#define annotation_hpp

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxXmlSettings.h"

class Annotation{

public:
    void setup();
    void setupGui();
    void update(string imgLoaderImageString);
    void draw();
    void resize(int w, int h);
    void loadXml(string imgName);
    
    ofxGuiGroup annotationGui;
    ofParameter <int> fontSize = 14;
    ofParameter <float> fontLineHeight = 18; //avait un f avant, no clues.
    ofParameter <float> fontLetterSpacing = 1.037;
    ofParameter <float> posX;
    ofParameter <float> posY;
    ofParameter <ofColor> fontColor;
    ofxXmlSettings XML;
   
    
private:
    ofTrueTypeFont	myFont;
    int oldFontSize = 0;
    float oldFontLineHeight = 0;
    float oldFontLetterSpacing = 0;
    int appWidth = 100;
    int appHeight = 100;
    string annotationText = "hello world";
    string imgName;
    string oldImgName;
    
    
    
};

#endif /* annotation_hpp */
