//
//  Creature.cpp
//  json
//
//  Created by Jane Friedhoff on 2/13/13.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "Creature.h"

void Creature::setup() {
    width = 70;
    height = 50;
    isAlive = false;
    isActive = false;
    canAttack = true;
    health = 100;
    
    intervalAttack = 1.0;
    
    resetPos();
    
//    for (int i = 0; i < 5; i++) {
//        ofPoint p;
//        p.set(ofGetWidth()/2 - (i * radius), ofGetHeight()/2);
//        positions.push_back(p);
//        cout << "point set" << endl;
//    }
    
}

void Creature::update(Player pA, Player pB) {
    // follow the circle ahead of you
//    angles.clear();
//    
//    float mainAngle = atan2(positions[0].y - ofGetMouseY(), positions[0].x - ofGetMouseX());
//    angles.push_back(mainAngle);
//    
//    positions[0].x -= 2 * cos(angles[0]);
//    positions[0].y -= 2 * sin(angles[0]);
//
//    for (int i = positions.size(); i > 0; i--) {
//        float a = atan2(positions[i].y - positions[i-1].y, positions[i].x - positions[i-1].x);
//        angles.push_back(a);
//    }
//    
//    
//    for (int i = positions.size(); i > 0; i--) {
//        positions[i].x = i * 2* cos(angles[i]);
//        positions[i].y = i * 2 * sin(angles[i]);
//    }
    
    if (isAlive) {
        if (isFollowingPA) {
            angle = atan2(pA.pos.y - pos.y, pA.pos.x - pos.x);
        } else {
            angle = atan2(pB.pos.y - pos.y, pB.pos.x - pos.x);
        }
        
        velocity.x = 2 * cos(angle);
        velocity.y = 2 * sin(angle);
        
        //pos+=velocity;
        
    }
    
    if (health <= 0) {
        isAlive = false;
        isActive = false;
        
        resetPos();
        health = 100;
    }
    
    if (ofGetElapsedTimef() > startTimeAttack + intervalAttack) {
        canAttack = true;
    }
    
    
}

void Creature::draw() {
//    if (isActive) {
//        ofSetColor(255);
//        ofFill();
//        for (int i = 0; i < 5; i++) {
//            ofCircle(positions[i].x, positions[i].y, radius);
//        }
//    }
    
    ofDrawBitmapString(ofToString(health), 100, 100);
    
    if (isAlive) {
        ofEnableAlphaBlending();
        ofSetColor(255, 100);
        ofFill();    
        ofPushMatrix();
        ofTranslate(pos.x, pos.y);
        ofRotateZ(ofRadToDeg(angle));
        ofEllipse(0, 0, width, height);
        ofPopMatrix();
        ofDisableAlphaBlending();
    }
}

void Creature::figureOutCloser(Player p1, Player p2) {
    float p1D = ofDist(p1.pos.x, p1.pos.y, pos.x, pos.y); 
    float p2D = ofDist(p2.pos.x, p2.pos.y, pos.x, pos.y);
    
    if (p1D >= p2D) {
        isFollowingPA = false;
    } else {
        isFollowingPA = true;
    }
    
    
    
}

void Creature::resetPos() {
    pos.x = ofRandom(ofGetWidth());
    
    int randomDoor = int(ofRandom(0, 4));
    
    switch (randomDoor) {
        case 0: // bottom
            pos.x = ofRandom(ofGetWidth());
            pos.y = ofRandom(ofGetHeight() + 100, ofGetHeight() + 150);
            break;
            
        case 1: // top
            pos.x = ofRandom(ofGetWidth());
            pos.y = ofRandom(-150, -100);
            break;
            
        case 2: // left
            pos.x = ofRandom(-150, -100);
            pos.y = ofRandom(ofGetHeight());
            break;
            
        case 3: // right
            pos.x = ofRandom(ofGetWidth() + 100, ofGetWidth() + 150);
            pos.y = ofRandom(ofGetHeight());
            break;
    }
}

void Creature::checkIsColliding(Player y) {
    float moveX = velocity.x;
    float moveY = velocity.y;
    
    ofPoint posNextX = pos;
    posNextX.x += moveX;
    
    if (ofDist(posNextX.x, posNextX.y, y.pos.x, y.pos.y) > height + y.size) {
        pos.x += velocity.x;
    }
    
    ofPoint posNextY = pos;
    posNextY.y += moveY;
    
    if (ofDist(posNextY.x, posNextY.y, y.pos.x, y.pos.y) > height + y.size) {
        pos.y += velocity.y;
    }
}

void Creature::attack() {
}