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

void GameObject::collisionLogic(GameObject collider){
    
}

void GameObject::checkValidMovement(GameObject * obj) {
    float moveX = vel.x;
    float moveY = vel.y;
    
    ofPoint posNextX = pos;
    posNextX.x += moveX;
    
    if (!ofDist(posNextX.x, posNextX.y, obj->pos.x, obj->pos.y) > width + obj->width) {
        canMoveHorizontal = false;
    }
    
    ofPoint posNextY = pos;
    posNextY.y += moveY;
    
    if (!ofDist(posNextY.x, posNextY.y, obj->pos.x, obj->pos.y) > width + obj->width) {
        canMoveVertical = false;
    }

    
}

bool GameObject::amIHit(GameObject * obj) {
    
}

