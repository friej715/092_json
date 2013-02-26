//
//  Blocker.h
//  spectation
//
//  Created by Jane Friedhoff on 2/25/13.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#pragma once
#include "ofMain.h"
#include "GameObject.h"

class Blocker : public GameObject {
public: 
    
    void draw() override;
    void customUpdate() override;
    void setup();
    
};
