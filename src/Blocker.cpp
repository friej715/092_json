//
//  Blocker.cpp
//  spectation
//
//  Created by Jane Friedhoff on 2/25/13.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "Blocker.h"

void Blocker::setup(){
    generalSetup();
    
    objectType = BLOCKER;
    
    width = 50;
    canBeHit = false;
    
    pos.set(300,300);
}

void Blocker::draw() {
    ofCircle(pos.x, pos.y, width);
}

void Blocker::customUpdate() {
    
    
}