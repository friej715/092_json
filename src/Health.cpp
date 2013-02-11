//
//  Health.cpp
//  json
//
//  Created by Jane Friedhoff on 2/1/13.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "Health.h"


Health::Health(string myPlayerName, ofVec2f myPos, ofVec2f myVel)
{
	playerName = myPlayerName;
	pos = myPos;
	vel = myVel;
    
    size = int(ofRandom(25, 35));
    
    airshipLittle.loadFont("airship.ttf", 20);
}


Health::~Health(void)
{
}

void Health::update(){
	pos += vel;
	if(pos.x > 2000 || pos.x < -2000 || pos.y > 2000 || pos.y < 2000){
		//remove this health from healthList
	}
}

void Health::draw(){
	ofSetColor(0, 100, 240);
	ofCircle(pos, size);
    ofSetColor(100, 255, 255);
    airshipLittle.drawString(ofToString(playerName), pos.x - airshipLittle.stringWidth(ofToString(playerName))/2, pos.y + 10);
}
