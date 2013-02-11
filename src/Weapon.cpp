//
//  Weapon.cpp
//  json
//
//  Created by Jane Friedhoff on 2/6/13.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "Weapon.h"

void Weapon::setup() {
    pos.x = ofRandom(ofGetWidth());
    pos.y = ofRandom(ofGetHeight());
    
    isHeld = false;
    
    angle = ofRandom(ofDegToRad(360));
    
    image.loadImage("sword.png");
}

void Weapon::update(float a, ofPoint p) {
    if (isHeld) {
        angle = a;
        pos = p;
    }
}

void Weapon::draw() {
    ofPushMatrix();
    ofTranslate(pos.x + image.width/2, pos.y);
    ofRotateZ(ofRadToDeg(angle) - ofRadToDeg(90));
    ofFill();
    ofSetColor(255);
    image.draw(0, 0);
    ofPopMatrix();
    
}