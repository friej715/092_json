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
    objectType = BLOCKER;
}

void Blocker::draw() {
    ofRect(500, 500, 100, 50);
}

void Blocker::customUpdate() {
    
    
}