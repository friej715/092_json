//
//  Weapon.cpp
//  json
//
//  Created by Jane Friedhoff on 2/6/13.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "Weapon.h"

void Weapon::setup() {
    generalSetup();
    canBeHeld = true;
    canCollide = false;
    canBeHit = false;
    canAttack = false;
    
    pos.x = ofRandom(ofGetWidth());
    pos.y = ofRandom(ofGetHeight());
    
    isHeld = false;
    
    angle = ofRandom(ofDegToRad(360));
    
    image.loadImage("sword.png");
    
    player = NULL;
    
    objectType = WEAPON;
}

/*
void Weapon::customUpdate(float a, ofPoint p) {
    if (isHeld) {
        angle = a;
        pos = p;
    }
}
 */

void Weapon::customUpdate(){
    
    if (isHeld && player != NULL){
        if(player->isAttacking == false) {
            //cout << "a is not attacking" << endl;
            angle = player->lastAngle;
            pos = player->pos;
        }
    } 
    
    if (isHeld && player != NULL) {
        if (player->isAttacking == true){
            angle = player->currentWeaponAngle;
            pos = player->pos;
        }
    }

}

void Weapon::draw() {
    if (!isHeld || (isHeld && player->isAttacking)) {    
        ofPushMatrix();
        ofTranslate(pos.x + image.width/2, pos.y);
        ofRotateZ(ofRadToDeg(angle) - ofRadToDeg(90));
        ofFill();
        ofSetColor(255);
        image.draw(0, 0);
        ofPopMatrix();
    }
    
}
/*
void Weapon::collisionLogic(GameObject collider){
    if(collider.objectType == PLAYER && !collider.isHolding){
        isHeld = true;
        player = *collider;
    }
}
*/