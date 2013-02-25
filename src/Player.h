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
    bool isDashing; //set to true if the player is dashing
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
    
    int attackCooldown; //if this is above 0, you can't start a new attack
    int attackCooldownMax = 30; //this is what the timer will be set to when an attack begins
    
    int sprintTimer;
    int sprintTimerMax;
    int sprintCooldown;
    int sprintCooldownMax;
    
    void sprintLogic();
    
    float speed; //multiplier for how fast the player moves
 
//    ofColor col;

    
    ofVec2f pos;
    float angle;
    
    float size;
    
    ofColor col;
    
    void setup(float x, float y);
    void turn(int dir);
    void draw();
    
    void checkIsColliding(Player y);

    ofTrueTypeFont healthFont;
    
};
