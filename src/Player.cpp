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
    generalSetup();
    
    col = ofColor::gray;
    angle = 0;
    pos.set(x,y);
    width = 40;
    height = 40;
    canAttack = true;
    
    maxSpeed = 6.0f;
    intervalAttack = .2; // this should probably be in weapon?
    health = 100;
    
    sprintTimerMax = 30;
    sprintCooldownMax = 120;
    
    healthFont.loadFont("Candara.ttf", 24);
    
    objectType = PLAYER;
    
    attackCooldownMax = 30;
    
}

void Player::customUpdate() {
   
    //cout << "HAI I'M BEING CALLED " << endl;
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


/*void Player::checkHit(GameObject * obj) {
    if (obj->objectType == PLAYER) {
        
    }
    
}
*/

bool Player::amIHit(GameObject * attacker) {
    // this is where all the code with blocking and stuff should go i think YEAH I BET IT IS DUDES (love, Andy)
    cout<<"player on player voilence is all of our problem"<<endl;
    //width*2 is a magic number put there for GAME FEEL(!)  ( . Y . )
    if (ofDist(pos.x, pos.y, attacker->pos.x, attacker->pos.y) < width*2 + attacker->width) {
        cout<<"In range like a dick"<<endl;
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
                //attacker is facing this
                wasFacing = true;
                
                cout<<"That fuck man attacker was facing my balls"<<endl;
                
                //check if this is facing attacker - if it is, then it is blocking
                float diffAngle2[3];
                //now get the angle from b to a
                diffAngle2[0] = atan2(attacker->pos.y - pos.y, attacker->pos.x - pos.x);
                
                //then make the two alternate verisons to check
                diffAngle2[1] = diffAngle2[0]+TWO_PI;
                diffAngle2[2] = diffAngle2[0]-TWO_PI;
                
                bool wasFacing2 = false;    //assume that this was facing away from attacker
                
                for (int k=0; k<3; k++){
                    if (abs(angle-diffAngle2[k]) < angleRange){
                        wasFacing2 = true;
                        cout<<"I face him! I do!"<<endl;
                    }
                    
                }
                
                if (wasFacing2 && isBlocking){
                    return false;
                    //IF ANYTHING FANCY HAPPENS WHEN A SHIELD IS HIT, PUT THAT CODE HERE
                    
                    //b is facing a and is blocking
                    //y.col = ofColor::green;
                    //   cout << "safe" << endl;
                } else {
                    //b is facing away and can be hit
                    //y.col = ofColor::red;
                    cout << "hit" << endl;
                    return true;
                    //y.health-=10;
                }
                
            }
        }
        
    }
    
    return false;
}






