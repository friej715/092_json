//
//  GameObject.h
//  spectation
//
//  Created by Jane Friedhoff on 2/25/13.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#pragma once
#include "ofMain.h"
//#include "Player.h"


class GameObject {
public:
    
    ofPoint pos;
    ofPoint vel;
    
    float angle;
    float health;
    
    float width, height;
    
    bool canBeHeld;
    bool isHeld;
    bool canCollide;
    bool canBeHit;
    
    bool canMoveHorizontal;
    bool canMoveVertical;
    
    bool canAttack;
    
    
    void preUpdate(); // for collision purposes
    void update();
    virtual void customUpdate();
    virtual void draw();

    virtual bool amIHit(GameObject * attacker);
    
    virtual void doThingsThatHappenWhenImHit(float damage);

    void generalSetup();
    void checkValidMovement(GameObject * obj);
    
    enum ObjectType {PLAYER, BULLET, HEALTH, CREATURE, BLOCKER, WEAPON};
    ObjectType objectType;
    
    bool isHolding;
    bool dead;
    
    
};