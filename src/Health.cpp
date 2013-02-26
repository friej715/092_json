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
    
    width = 40;
    height = 40;
    
    airshipLittle.loadFont("airship.ttf", 20);
    
    objectType = HEALTH;
}


void Health::customUpdate(){
	pos += vel;
	if(pos.x > 2000 || pos.x < -2000 || pos.y > 2000 || pos.y < 2000){
		//remove this health from healthList
	}
}

void Health::draw(){
	ofSetColor(78, 34, 134);
	ofRect(pos, width, height);
    ofSetColor(255, 120, 120);
    airshipLittle.drawString(ofToString(playerName), pos.x, pos.y + 35);
    ofRectMode(OF_RECTMODE_CORNER);
}
