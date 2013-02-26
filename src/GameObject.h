//
//  GameObject.h
//  spectation
//
//  Created by Jane Friedhoff on 2/25/13.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#pragma once
#include "ofMain.h"


class GameObject {
public:
    
    ofPoint pos;
    ofPoint vel;
    
    float width, height;
    
    bool canBeHeld;
    bool isHeld;
    bool canCollide;
    
    bool canMoveHorizontal;
    bool canMoveVertical;
    
    
    void preUpdate(); // for collision purposes
    void update();
    virtual void customUpdate();
    virtual void draw();
    virtual void collisionLogic(GameObject collider);

    void generalSetup();
    void checkValidMovement(GameObject * obj);
    
    virtual bool amIHit(GameObject * obj);
    
    enum ObjectType {PLAYER, BULLET, HEALTH, CREATURE, BLOCKER, WEAPON};
    ObjectType objectType;
    
    bool isHolding;
    
    
};