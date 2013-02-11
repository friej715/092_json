//
//  Enemy.h
//  springs
//
//  Created by Jane Friedhoff on 1/23/13.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#pragma once
#include "ofMain.h"

class Enemy {
public:
    ofPoint pos;
    ofPoint velocity;
    float speed; // lol bad naming
    ofPoint startVelocity;
    
    float angle;
    
    int type;
    
    float width, height;
    float health;
    
    bool isHit, isDead;
    
    void setup();
    void update();
    void draw();
    
    float hitInterval;
    float startHit;
    
};