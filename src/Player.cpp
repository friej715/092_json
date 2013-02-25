//
//  Player.cpp
//  springs
//
//  Created by Jane Friedhoff on 1/27/13.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "Player.h"

void Player::update() {
   
    // determining direction facing
    if (abs(angle) > 0.05) {
        lastAngle = angle;
    } else {
        angle = lastAngle;
    }
    
    //set speed based on isDashing
    if(isDashing) { speed = 2.0; }
    else if(isBlocking) {speed = 0.2;}
    else { speed = 0.6; }
    
    // making diagonal speed not exceed fastest left/right/up/down
    float speedRatio = maxSpeed / (abs(velocity.x)+abs(velocity.y));
    if (speedRatio < 1) {
        velocity.x *= speedRatio;
        velocity.y *= speedRatio;
    }
    
    // reg'lar movement (and also dashing movement -Ramiro)
    velocity *= speed;

//    if (health > 0) {
//        pos += velocity;
//    }
    
    // limiting to bounds of screen
    if (pos.x > ofGetWidth() - size/2)    pos.x = ofGetWidth() - size/2;
    if (pos.x < 0 + size/2)               pos.x = size/2;
    if (pos.y > ofGetHeight() - size/2)  pos.y = ofGetHeight() - size/2;
    if (pos.y < 0 + size/2)              pos.y = size/2;

//    
//    if (isTriggered) {
//   
//    } else {
//        
//    }
//    
//    if (isHit) {
//      //  cout << "invincible" << endl;
//        if (ofGetElapsedTimef() > startTimeHit + intervalHit) {
//            cout << "end" << endl;
//            isHit = false;
//        }
//    }

    if(attackCooldown > 0) {
        attackCooldown--;
        canAttack = false;
    }
    else { canAttack = true; }
//    
    if (isAttacking) {
        attack();
    }
//
//
    
    sprintLogic();
}

void Player::attack() {
    //cout << "attacking" << endl;
    currentWeaponAngle = ofDegToRad(ofMap(startTimeAttack + intervalAttack - ofGetElapsedTimef(), 0, intervalAttack, startWeaponAngle, endWeaponAngle));
    
    if (ofGetElapsedTimef() > startTimeAttack + intervalAttack) {
        //cout << "end attack timer" << endl;
        isAttacking = false;
     //   canAttack = true; // not enough to provide cooldown, if that matters
    }
    
}

void Player::setup(float x, float y){
    col = ofColor::gray;
    angle = 0;
    pos.set(x,y);
    size = 40;
//    canAttack = true;
    
    maxSpeed = 6.0f;
    intervalAttack = .2; // this should probably be in weapon?
    health = 100;
    
    sprintTimerMax = 30;
    sprintCooldownMax = 120;
    
    healthFont.loadFont("Candara.ttf", 24);
    
}

void Player::draw(){
    ofSetColor(col);
    ofCircle(pos.x, pos.y, size);
    
    ofSetColor(0);
    float lineSize = size*0.9;
    ofLine(pos.x,pos.y, pos.x+cos(angle)*lineSize, pos.y+sin(angle)*lineSize);
    
    ofSetColor(255, 0, 0);
    
    if (isBlocking) {
        // draw the shield
        ofSetColor(255);
        ofPushMatrix();
        ofTranslate(pos.x, pos.y);
        ofRotateZ(ofRadToDeg(angle));
        ofEllipse(0 + size, 0, 10, 40);
        ofPopMatrix();
    }
    
    healthFont.drawString(ofToString(health), pos.x - healthFont.stringWidth(ofToString(health))/2, pos.y);
    
}

void Player::sprintLogic() {
    if (sprintTimer > 0) {
        isDashing = true;
        sprintTimer--;
    } else {
        isDashing = false;
    }
    
    if (sprintCooldown > 0) {
        sprintCooldown--;
    }
    
    
}

void Player::checkIsColliding(Player y) {
    float moveX = velocity.x;
    float moveY = velocity.y;
    
    ofPoint posNextX = pos;
    posNextX.x += moveX;
    
    if (ofDist(posNextX.x, posNextX.y, y.pos.x, y.pos.y) > size + size) {
        pos.x += velocity.x;
    }
    
    ofPoint posNextY = pos;
    posNextY.y += moveY;
    
    if (ofDist(posNextY.x, posNextY.y, y.pos.x, y.pos.y) > size + size) {
        pos.y += velocity.y;
    }
}
