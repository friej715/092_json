//
//  Player.h
//  springs
//
//  Created by Jane Friedhoff on 1/27/13.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#pragma once
#include "ofMain.h"
#include "particle.h"
#include "spring.h"

class Player {
public:    
    int health;
//    int height;
//    int width;
//    ofPoint shieldLocation;
//    
//    ofPoint pos;
    ofVec2f velocity;
//    float angle;
    float lastAngle;
//    
//    bool isCursed;
//    bool isTriggered;
    bool isAttacking;
    bool canAttack;
    bool isBlocking;
    bool isHolding;
//    bool isHit;
//    
//    float startTimeHit;
//    float intervalHit;
//    
    float maxSpeed;
//    
//    void setup(int player);
    void update();
//    void draw();
    
    void attack();
    
    float startTimeAttack;
    float intervalAttack;
    float startWeaponAngle;
    float currentWeaponAngle;
    float endWeaponAngle;
 
//    ofColor col;

    
    ofVec2f pos;
    float angle;
    
    float size;
    
    ofColor col;
    
    void setup(float x, float y);
    void turn(int dir);
    void draw();
    
};
