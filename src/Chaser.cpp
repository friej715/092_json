#include "Chaser.h"


void Chaser::setup(ofPoint myPos, Player* myTarget, string myComingFrom) {
	target = myTarget;
	pos = myPos;
	comingFrom = myComingFrom;
	speed = 5;
	speedIncrease = .5f;
	maxSpeed = 4;
	width = 20;
    dead = false;
    shouldPassivelyCheckCollision = true;

	//set the starting speed based on the direction from which the Chaser is coming
	if(comingFrom == "left"){
		velf.x = speed;
		velf.y = 0;
	}
	else if (comingFrom == "right"){
		velf.x = -speed;
		velf.y = 0;
	}
	else if (comingFrom == "top"){
		velf.x = 0;
		velf.y = speed;
	}
	else if (comingFrom == "bottom"){
		velf.x = 0;
		velf.y = -speed;
	}
}

void Chaser::customUpdate(){
	ofPoint targetPos = target->pos;
	
	//if coming from the sides, change the velf.y to make it move slightly more toward the target
	if(comingFrom == "left" || comingFrom == "right"){
		if(targetPos.y > pos.y){
			velf.y += speedIncrease;
		}
		else if (targetPos.y < pos.y){
			velf.y -= speedIncrease;
		}
	}

	//if coming form above/below, change the velf.x to make it move slightly more toward the target
	else if(comingFrom == "top" || comingFrom == "bottom"){
		if(targetPos.x > pos.x){
			velf.x += speedIncrease;
		}
		else if (targetPos.x < pos.x){
			velf.x -= speedIncrease;
		}
	}
	if(velf.x > maxSpeed) velf.x = maxSpeed;
	else if (velf.x < -maxSpeed) velf.x = -maxSpeed;
	if(velf.y > maxSpeed) velf.y = maxSpeed;
	else if (velf.y < -maxSpeed) velf.y = -maxSpeed;

	vel = (ofPoint)velf; //set the vel to velf (could skip this step and just increase pos by (ofPoint)velf, but being thorough just in case
	pos += vel; //move object by vel
}

void Chaser::draw(){
    if (dead == false) {
        ofCircle(pos.x, pos.y, width);
    }
}

void Chaser::doThingsThatHappenWhenImHit(float damage) {
    dead = true;
}

void Chaser::affectThingTouchingMe(GameObject *toucher) {
    toucher->health-=30;
}


