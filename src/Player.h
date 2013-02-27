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
#include "GameObject.h"

class Player : public GameObject {
public:    
    void setup(float x, float y);
    
    
 //   int health;
    
    float lastAngle;
    bool isAttacking;
    bool canAttack;
    bool isBlocking;
   // bool isHolding;
    bool isDashing; //set to true if the player is dashing

    float maxSpeed;

    void draw() override;
    void customUpdate() override;
    
    bool amIHit(GameObject * attacker) override;
    
    void attack();
    
    //float width, height;
    
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

    //float angle;
    
    ofColor col;

    void turn(int dir);

    ofTrueTypeFont healthFont;
    
};
