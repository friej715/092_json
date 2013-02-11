//
//  Player.cpp
//  springs
//
//  Created by Jane Friedhoff on 1/27/13.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "Player.h"

//void Player::setup(int player) {
//    
//    maxSpeed = 6.0f;
//    isHit = false;
//    
//    height = 30;
//    width = height/2;
//    
//    if (player == 1) { 
//        pos.x = ofGetWidth()/4;
//        pos.y = ofGetHeight()/4;
//    }
//    
//    if (player == 2) {
//        pos.x = ofGetWidth()*.75;
//        pos.y = ofGetHeight()*.75;
//    }
//    
//    
//    col.set(10, 10, 10);
//}

void Player::update() {
   
    // determining direction facing
    if (abs(angle) > 0.05) {
        lastAngle = angle;
    } else {
        angle = lastAngle;
    }
    
    // making diagonal speed not exceed fastest left/right/up/down
    float speedRatio = maxSpeed / (abs(velocity.x)+abs(velocity.y));
    if (speedRatio < 1) {
        velocity.x *= speedRatio;
        velocity.y *= speedRatio;
    }
    
    // reg'lar movement
    velocity*=.7;
    pos += velocity;
    
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
//    
    if (isAttacking) {
        attack();
    }
//
//    
}
//
//void Player::draw() {
//    
//    ofFill();
//    ofPushMatrix();
//    ofTranslate(pos.x, pos.y);
//    ofRotateZ(ofRadToDeg(lastAngle));
//    ofSetColor(col);
//    ofEllipse(0, 0, width, height);
//    ofSetColor(0, 0, 255);
//    ofLine(0, 0, 0 + width, 0);
//   
//    if (isBlocking) {
//        ofEllipse(10 + cos(lastAngle), 0, 20, 20);
//        
//        shieldLocation.x = 10 + cos(lastAngle) + pos.x;
//        shieldLocation.y = pos.y;
//    }
//    
//    ofPopMatrix();
//
//    
//}
//
void Player::attack() {
    //cout << "attacking" << endl;
    currentWeaponAngle = ofDegToRad(ofMap(startTimeAttack + intervalAttack - ofGetElapsedTimef(), 0, intervalAttack, startWeaponAngle, endWeaponAngle));
    
    if (ofGetElapsedTimef() > startTimeAttack + intervalAttack) {
        //cout << "end attack timer" << endl;
        isAttacking = false;
        canAttack = true; // not enough to provide cooldown, if that matters
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
    
}
