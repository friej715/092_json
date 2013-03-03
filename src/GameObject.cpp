//
//  GameObject.cpp
//  spectation
//
//  Created by Jane Friedhoff on 2/25/13.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "GameObject.h"

void GameObject::generalSetup() {
    canBeHeld = false;
    canCollide = true;
    canAttack = false;
    canBeHit = true;
    shouldPassivelyCheckCollision = false;
    dead = false;
}

void GameObject::preUpdate() {
    // setting these to true--later functions will set them to false if needed
    canMoveVertical = true;
    canMoveHorizontal = true;
}

void GameObject::update() {
    customUpdate();
    
    if (canMoveVertical)    pos.y += vel.y;
    if (canMoveHorizontal)  pos.x += vel.x;

}

void GameObject::customUpdate() {
    
}

void GameObject::draw() {
    
    
}


bool GameObject::amIHit(GameObject * attacker) {
    if (ofDist(pos.x, pos.y, attacker->pos.x, attacker->pos.y) < width + attacker->width *2 ) { // x2 is a magic number--will need to accout for weapon size
        cout << "in range " << endl;
        // in range and swinging
        float angleRange = ofDegToRad(45);
        
        //check if a is beating on b
        float diffAngle[3];
        //get the angle from a to b
        diffAngle[0] = atan2(pos.y - attacker->pos.y, pos.x - attacker->pos.x);
        //two alternate versions to check when this is on the line where the angle wraps around
        diffAngle[1] = diffAngle[0]+TWO_PI; // 360 degrees
        diffAngle[2] = diffAngle[0]-TWO_PI;
        
        bool wasFacing = false; //assume a was not facing b
        
        for (int i=0; i<3; i++){
            if ( abs(attacker->angle-diffAngle[i]) < angleRange){
                //a is facing b
                wasFacing = true;
                //return true;
                cout << "facing other" << endl;
            }
        }
        
        if (wasFacing) {
            return true;
        }
    }
    return false;
}

bool GameObject::amITouching(GameObject * toucher) {
    if (ofDist(pos.x, pos.y, toucher->pos.x, toucher->pos.y) < width + toucher->width) {
        return true;
    }
    return false;
}


void GameObject::doThingsThatHappenWhenImHit(float damage) {
    health -= damage;
}

void GameObject::affectThingTouchingMe(GameObject * thing) {
    
}

void GameObject::checkValidMovement(GameObject * obj) {
    float moveX = vel.x;
    float moveY = vel.y;
    
    ofPoint posNextX = pos;
    posNextX.x += moveX;
    
//    cout<<"this width "<<width<<"   other fucker width "<<obj->width<<endl;
    
    if (ofDist(posNextX.x, posNextX.y, obj->pos.x, obj->pos.y) < width + obj->width) {
        //cout<<"hey fuck you - HORZ"<<endl;
        canMoveHorizontal = false;
    }
    
    ofPoint posNextY = pos;
    posNextY.y += moveY;
    
    if (ofDist(posNextY.x, posNextY.y, obj->pos.x, obj->pos.y) < width + obj->width) {
        //cout<<"hey fuck you - VERT"<<endl;
        canMoveVertical = false;
    }
    
}


