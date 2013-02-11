//
//  Obstacle.h
//  json
//
//  Created by Jane Friedhoff on 1/31/13.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#pragma once
#include "ofMain.h"
#include "particle.h"
#include "spring.h"

class Obstacle {
public:
    ofPoint pos;
    
    float width;
    float height;
    
    vector <particle> particles;
    vector <spring> springs;
    
    void setup();
    void update();
    void draw();
    
};