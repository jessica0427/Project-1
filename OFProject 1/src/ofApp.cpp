#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(60);
    ofSetBackgroundAuto(false);
    ofBackground(0, 0, 0);

    ofEnableBlendMode(OF_BLENDMODE_ALPHA);

    control = true;
}

//--------------------------------------------------------------
void ofApp::update(){

    theta = PI / 2 + PI / 2 / 700 * pos.size();  //theta of raindrops, perpendicular = PI / 2
    float speed = pos.size() / 15;;    //a speed of raindrops

    for(int i = 0; i < pos.size(); i++) {
        //convert speed from vector to x, y
        ofVec2f vel;
        vel.x = ofGetHeight() / 2300.0f * (length[i] + speed) * cos(theta + noise[i]);
        vel.y = ofGetHeight() / 2300.0f * (length[i] + speed) * sin(theta + noise[i]);

        pos[i].x += vel.x;
        pos[i].y += vel.y;

        //if a raindrop reaches the bottom of window, it will return to the first position
        
        if(pos[i].y - length[i] * sin(theta + noise[i]) > ofGetHeight()){
            pos[i].y = 0;
            pos[i].x -= vel.x * (ofGetHeight() / vel.y);
        }
    }


}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetColor(0, 0, 0, 150);
    ofRectangle(0, 0, ofGetWidth(), ofGetHeight());  //fadeout

    ofSetColor(173, 216, 230);  //color of letters and raindrops
    for(int i = 0; i < pos.size(); i++) {

        //coordinate of a raindrop
        float x1 = pos[i].x;
        float y1 = pos[i].y;
        float x2 = pos[i].x - length[i] * cos(theta + noise[i]);
        float y2 = pos[i].y - length[i] * sin(theta + noise[i]);

        ofSetLineWidth(length[i] / 30); //width of a raindrop
        ofDrawLine(x1, y1, x2, y2); //draw a raindrop
    }


    //log
    if(control == true){
        string log;
        log = "raindrops num = " + ofToString(pos.size(), 0) + "\n";
        log += "ofSetFrameRate = " + ofToString(ofGetFrameRate(), 4) + "\n";
        log += "1:add 5 raindrops, 2:subtract 5 raindrops \n";
        log += "c:clear raindrops num, f:fullScreen \n";
        log += "press spacekey to change log on/off";
        ofDrawBitmapString(log, 20, 20);
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == '1'){
        //add 5 raindrops
        for(int i = 0; i < 5; i++){
            //define first position
            ofVec2f p;
            float x = ofRandom(ofGetWidth() + ofGetHeight());
            p.set(x, 0);
            pos.push_back(p);

            //define length
            float l = ofRandom(ofGetHeight() / 60, ofGetHeight() / 10);
            length.push_back(l);

            //define speed
            ofVec2f v;
            float vx = length[length.size() - 1] / 10 * cos(theta);
            float vy = length[length.size() - 1] / 10 * sin(theta);
            v.set(vx, vy);
            velocity.push_back(v);

            //define noise of slant
            float n;
            n = ofRandom(-PI/90, PI/90);
            noise.push_back(n);
        }

    }

    if(key == '2'){
        //subtract 5 raindrops
        if(pos.size() > 0){
            for(int i = 0; i < 5; i++){
                pos.pop_back();
                length.pop_back();
                velocity.pop_back();
                noise.pop_back();
            }
        }
    }

    if(key == 'c'){
        //clear raindrops
        pos.clear();
        length.clear();
        velocity.clear();
        noise.clear();
    }

    if(key == 'f'){
        ofSetFullscreen(true);
    }
    if(key == ' '){
        //state of log log 
        control =! control;
    }
}
