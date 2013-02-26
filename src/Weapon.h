//
//  Weapon.h
//  json
//
//  Created by Jane Friedhoff on 2/6/13.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#pragma once
#include "ofMain.h"
#include "GameObject.h"
#include "Player.h"

class Weapon : public GameObject {
public:
    
    float angle;
    
    ofImage image;
    
    Player * player;
    
    void setup();
    //void customUpdate(float angle, ofPoint p);
    void customUpdate() override;
    void draw();
    
};