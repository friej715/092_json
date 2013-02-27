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
    generalSetup();
    width = 70;
    height = 70;
    isAlive = true;
    isActive = true;
    canAttack = true;
    health = 100;
    
    intervalAttack = 1.0;
    
    resetPos();
    
    player1 = NULL;
    player2 = NULL;
    
    objectType = CREATURE;
    
}

void Creature::update(Player pA, Player pB) {
    
    
}

void Creature::customUpdate() {

    if (player1 != NULL && player2 != NULL) {
        float p1D = ofDist(player1->pos.x, player1->pos.y, pos.x, pos.y); 
        float p2D = ofDist(player2->pos.x, player2->pos.y, pos.x, pos.y);
        
        if (p1D >= p2D) {
            isFollowingPA = false;
        } else {
            isFollowingPA = true;
        }
        
        if (isAlive) {
            if (isFollowingPA) {
                angle = atan2(player1->pos.y - pos.y, player1->pos.x - pos.x);
            } else {
                angle = atan2(player2->pos.y - pos.y, player2->pos.x - pos.x);
            }
            
            cout <<"changing vel" << endl;
            vel.x = 2 * cos(angle);
            vel.y = 2 * sin(angle);
            
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
        
        if (ofDist(pos.x, pos.y, player1->pos.x, player1->pos.y) < height && canAttack == true) {
            canAttack = false;
            startTimeAttack = ofGetElapsedTimef();
            player1->health -= 20;
        }

        if (ofDist(pos.x, pos.y, player2->pos.x, player2->pos.y) < height && canAttack == true) {
            canAttack = false;
            startTimeAttack = ofGetElapsedTimef();
            player2->health -= 20;
        }
    }
    
    
}

void Creature::draw() {
    
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
    /*
    float moveX = vel.x;
    float moveY = vel.y;
    
    ofPoint posNextX = pos;
    posNextX.x += moveX;
    
    if (ofDist(posNextX.x, posNextX.y, y.pos.x, y.pos.y) > height + y.width) {
        pos.x += vel.x;
    }
    
    ofPoint posNextY = pos;
    posNextY.y += moveY;
    
    if (ofDist(posNextY.x, posNextY.y, y.pos.x, y.pos.y) > height + y.width) {
        pos.y += vel.y;
    }
     */
}

void Creature::attack() {
}