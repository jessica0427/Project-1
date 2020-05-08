#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{

    public:
        void setup();
        void update();
        void draw();
        void raindrops();
        void SetFrameRate();
        void keyPressed(int key);
//        void keyReleased(int key);
        
    vector <ofVec2f> pos;   //a position of the raindrop
    vector <float> length;  //a length of the raindop
    vector <ofVec2f> velocity;  //a speed of the raindrop
    vector <float> noise;   //a noise of a slant of the raidrop
    
    float theta;   //general slant of raindrops
    
    bool control;   //switch of log log on/off

};
