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
    generalSetup();
	playerName = myPlayerName;
	pos = myPos;
	vel = myVel;
    
    width = 40;
    height = 40;
    
    airshipLittle.loadFont("airship.ttf", 20);
    
    objectType = BULLET;
}



void Bullet::customUpdate(){
	pos += vel;
	if(pos.x > 2000 || pos.x < -2000 || pos.y > 2000 || pos.y < 2000){
		//remove this health from healthList
	}
}

void Bullet::draw(){
	ofSetColor(178, 34, 34);
	ofRect(pos, width, height);
    ofSetColor(255, 120, 120);
    airshipLittle.drawString(ofToString(playerName), pos.x, pos.y + 35);
    ofRectMode(OF_RECTMODE_CORNER);
}
