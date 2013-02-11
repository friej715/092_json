//
//  Enemy.cpp
//  springs
//
//  Created by Jane Friedhoff on 1/23/13.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "Enemy.h"

void Enemy::setup() {
    
    // instead of the following, set up a few starting points offscreen and just randomly choose
    
    type = int(ofRandom(3));
    //type = 2;
    
    // type 0: quick, little, no wiggle
    if (type == 0) {
        health = 1;
        width = 10;
        speed = 2.5;
    }
    
    // type 1: mid-sized, mid-speed, fast wiggle
    if (type == 1) {
        health = 1;
        width = 20;
        speed = 2;
    }
    
    // type 2: big, slow-speed, slow wiggle
    if (type == 2) {
        health = 1;
        width = 30;
        speed = 1.5;
    }
    
    pos.x = ofRandom(ofGetWidth());
    pos.y = ofRandom(ofGetHeight());
    
    isDead = isHit = false;
    
    hitInterval = 2;
    
}

void Enemy::update() {
    
    startVelocity.x = cos(angle) * speed;
    startVelocity.y = sin(angle) * speed;

    // if it gets hit, it should get knocked back
    if (isHit) { // isDead should be reserved for when it actually dies
        velocity = -startVelocity;
        if (ofGetElapsedTimef() > startHit + hitInterval) {
            isHit = false;
        }
        
        
    } else {
        velocity.x = cos(angle) * speed;
        velocity.y = sin(angle) * speed;
    
        velocity.x += cos(ofGetElapsedTimef() * type * 5) * (type * 2);
        velocity.y += sin(ofGetElapsedTimef() * type * 5) * (type * 2);
    }
    
    pos += velocity;
    
}

void Enemy::draw() {
    ofRectMode(OF_RECTMODE_CENTER);
    
    if (isHit && !isDead) {
        ofSetColor(255, 0, 0);
    } else if (!isHit && isDead) {
        ofSetColor(0, 0, 255);
    } else if (isHit && isDead) {
        ofSetColor(255, 0, 255);
    } else {
        ofSetColor(0, 255, 0);
    }
    
    if (type == 0) {
        ofCircle(pos.x, pos.y, width);
    } else if (type == 1) {
        ofRect(pos.x, pos.y, width, width);
    } else {
        ofEllipse(pos.x, pos.y, width, width*1.5);
    }
}