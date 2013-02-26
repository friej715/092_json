//
//  Player.cpp
//  springs
//
//  Created by Jane Friedhoff on 1/27/13.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "Player.h"

void Player::setup(float x, float y){
    col = ofColor::gray;
    angle = 0;
    pos.set(x,y);
    width = height = 40;
    //    canAttack = true;
    
    maxSpeed = 6.0f;
    intervalAttack = .2; // this should probably be in weapon?
    health = 100;
    
    sprintTimerMax = 30;
    sprintCooldownMax = 120;
    
    healthFont.loadFont("Candara.ttf", 24);
    
}

void Player::customUpdate() {
   
    cout << "HAI I'M BEING CALLED " << endl;
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
    float speedRatio = maxSpeed / (abs(vel.x)+abs(vel.y));
    if (speedRatio < 1) {
        vel.x *= speedRatio;
        vel.y *= speedRatio;
    }
    
    // reg'lar movement (and also dashing movement -Ramiro)
    vel *= speed;
    
    // limiting to bounds of screen
    if (pos.x > ofGetWidth() - width/2)    pos.x = ofGetWidth() - width/2;
    if (pos.x < 0 + width/2)               pos.x = width/2;
    if (pos.y > ofGetHeight() - height/2)  pos.y = ofGetHeight() - height/2;
    if (pos.y < 0 + height/2)              pos.y = height/2;


    if(attackCooldown > 0) {
        attackCooldown--;
        canAttack = false;
    } else { 
        canAttack = true; 
    }   
    
    if (isAttacking) {
        attack();
    }
    
    sprintLogic();
}

void Player::attack() {
    //cout << "attacking" << endl;
    currentWeaponAngle = ofDegToRad(ofMap(startTimeAttack + intervalAttack - ofGetElapsedTimef(), 0, intervalAttack, startWeaponAngle, endWeaponAngle));
    
    if (ofGetElapsedTimef() > startTimeAttack + intervalAttack) {
        isAttacking = false;
    }
    
}


void Player::draw(){
    ofSetColor(col);
    ofCircle(pos.x, pos.y, width);
    
    ofSetColor(0);
    float lineSize = width*0.9;
    ofLine(pos.x,pos.y, pos.x+cos(angle)*lineSize, pos.y+sin(angle)*lineSize);
    
    ofSetColor(255, 0, 0);
    
    if (isBlocking) {
        // draw the shield
        ofSetColor(255);
        ofPushMatrix();
        ofTranslate(pos.x, pos.y);
        ofRotateZ(ofRadToDeg(angle));
        ofEllipse(0 + width, 0, 10, 40);
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
