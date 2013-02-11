//
//  Obstacle.cpp
//  json
//
//  Created by Jane Friedhoff on 1/31/13.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "Obstacle.h"

void Obstacle::setup() {
    pos.x = ofRandom(ofGetWidth());
    pos.y = ofRandom(ofGetHeight());
    
    width = 40;
    height = 40;
    
    particle myParticle;
	myParticle.setInitialCondition(pos.x,pos.y,0,0);
	particles.push_back(myParticle);
	
	myParticle.setInitialCondition(pos.x,pos.y + height,0,0);
	particles.push_back(myParticle);
	
	myParticle.setInitialCondition(pos.x + width, pos.y + height,0,0);
	particles.push_back(myParticle);
	
	myParticle.setInitialCondition(pos.x + width, pos.y,0,0);
	particles.push_back(myParticle);
	
	spring mySpring;
    
	for (int i = 0; i < particles.size(); i++){
		mySpring.distance		= 100;
		mySpring.springiness	= 0.2f;
		mySpring.particleA = & (particles[i  ]);
		mySpring.particleB = & (particles[(i+1) % particles.size()]);
		springs.push_back(mySpring);
	}
	
	
	// these hold the shape together: 
	
	mySpring.distance		= (particles[0].pos - particles[2].pos).length();
	mySpring.springiness	= 0.2f;
	mySpring.particleA = & (particles[0]);
	mySpring.particleB = & (particles[2]);
	springs.push_back(mySpring);
	
	
	mySpring.distance		= (particles[1].pos - particles[3].pos).length();
	mySpring.springiness	= 0.2f;
	mySpring.particleA = & (particles[1]);
	mySpring.particleB = & (particles[3]);
	springs.push_back(mySpring);	
}

void Obstacle::update() {
    for (int i = 0; i < particles.size(); i++){
		particles[i].resetForce();
	}
	
	for (int i = 0; i < springs.size(); i++){
		springs[i].update();
	}
	
	for (int i = 0; i < particles.size(); i++){
		particles[i].bounceOffWalls();
		particles[i].addDampingForce();
		particles[i].update();
	}
    
}

void Obstacle::draw() {
    for (int i = 0; i < particles.size(); i++){
		particles[i].draw();
	}
	
	for (int i = 0; i < springs.size(); i++){
		springs[i].draw();
	}
    
}

