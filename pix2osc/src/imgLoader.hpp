//
//  imgLoader.hpp
//  pix2osc
//
//  Created by Guillaume Arseneault on 16-10-16.
//
//

#ifndef imgLoader_hpp
#define imgLoader_hpp



#include "ofMain.h"

#include "ofxThreadedImageLoader.h"


class imgLoader {
    
public:
    void setup(string folder);
    void exit();
    void load(int id, int index);
    void next();
    void prev();
    void update();
    void draw();
    
    vector<int> imgWidth;
    vector<int> imgHeight;
    
    int canvasWidth;
    int canvasHeight;
    int frameTotal;
    
    int playhead;
    
    ofFbo swapperFbo;
    
    bool nextFrame = 0;
    bool prevFrame = 0;
    int lastDirection = 0;
    int frameNow = 0;
    int playHead = 0;
    int loadHead = 0;

    
    vector<ofImage> images;
    ofxThreadedImageLoader loader;
    vector<string> imagePath;
  
    
    
    
};

#endif /* imgLoader_hpp */
