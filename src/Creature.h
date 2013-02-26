//
//  Creature.h
//  json
//
//  Created by Jane Friedhoff on 2/13/13.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#pragma once
#include "ofMain.h"
#include "Player.h"

class Creature {
public:
    float width;
    float height;
    float health;
  
    ofPoint pos;
    ofPoint velocity;
    float angle;
    
    bool isAlive;
    bool isActive;
    bool isFollowingPA;
    bool canAttack;
    
    ofColor col;
    
    void setup();
    void update(Player p1, Player p2);
    void draw();
    
    void figureOutCloser(Player p1, Player p2);
    void resetPos();
    void checkIsColliding(Player y);
    
    void attack();
    
    float startTimeAttack;
    float intervalAttack;
    
};