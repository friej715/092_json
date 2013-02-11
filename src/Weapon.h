//
//  Weapon.h
//  json
//
//  Created by Jane Friedhoff on 2/6/13.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#pragma once
#include "ofMain.h"

class Weapon {
public:
    ofPoint pos; // starts randomly, will glue to player
    float angle;
    
    bool isHeld;
    int heldByPlayer;
    
    ofImage image;
    
    void setup();
    void update(float angle, ofPoint p);
    void draw();
    
};