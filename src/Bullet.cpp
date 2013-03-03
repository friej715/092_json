//
//  Bullet.cpp
//  json
//
//  Created by Jane Friedhoff on 2/1/13.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "Bullet.h"

void Bullet::setup(string myPlayerName, ofVec2f myPos, ofVec2f myVel)

{
    dead = false;
    generalSetup();
	playerName = myPlayerName;
	pos = myPos;
	vel = myVel;
    shouldPassivelyCheckCollision = true;
    canAttack = true;
    
    width = 20;
    height = 20;
    
    health = 10;
    
    angle = atan2(pos.y - pos.y + vel.y, pos.x - pos.x + vel.x);
    
    airshipLittle.loadFont("airship.ttf", 20);
    
    objectType = BULLET;
}



void Bullet::customUpdate(){
	pos += vel;
	if(pos.x > 2000 || pos.x < -2000 || pos.y > 2000 || pos.y < 2000){
		//dead = true;
	}
    
    cout << "dead? " << dead << endl;
}

void Bullet::draw(){
    if (!dead) {    
        ofSetColor(178, 34, 34);
        ofCircle(pos, width);
        ofSetColor(255, 120, 120);
        //airshipLittle.drawString(ofToString(playerName), pos.x, pos.y + 35);
        airshipLittle.drawString(ofToString(health), pos.x, pos.y + 35);
        ofRectMode(OF_RECTMODE_CORNER);
    }
}

void Bullet::affectThingTouchingMe(GameObject * toucher) {
    
    toucher->health-=10;
    dead = true;
    
}

void Bullet::doThingsThatHappenWhenImHit(float damage) {
    dead = true;
}

