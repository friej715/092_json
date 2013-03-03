//
//  Health.cpp
//  json
//
//  Created by Jane Friedhoff on 2/1/13.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "Health.h"


void Health::setup(string myPlayerName, ofVec2f myPos, ofVec2f myVel)
{
    generalSetup();
	playerName = myPlayerName;
	pos = myPos;
	vel = myVel;
    shouldPassivelyCheckCollision = true;
    canCollide = false;
    
    //canAttack = true;
    
    width = 20;
    height = 20;
    
    airshipLittle.loadFont("airship.ttf", 20);
    
    angle = atan2(pos.y - pos.y + vel.y, pos.x - pos.x + vel.x);
    
    objectType = HEALTH;
    
    health = 10;
}


void Health::customUpdate(){
    
	pos += vel;
	if(pos.x > 2000 || pos.x < -2000 || pos.y > 2000 || pos.y < 2000){
		//remove this health from healthList
	}
}

void Health::draw(){
    if (health > 0) {
        ofSetColor(78, 34, 134);
        ofCircle(pos, width);
        ofSetColor(255, 120, 120);
        airshipLittle.drawString(ofToString(health), pos.x, pos.y + 35);
        ofRectMode(OF_RECTMODE_CORNER);
    }
}

void Health::doThingsThatHappenWhenImHit(float damage) {
    dead = true;
}

void Health::affectThingTouchingMe(GameObject *toucher) {
    if (toucher->objectType != BULLET && !dead) {
        toucher->health+=15;
    }
}