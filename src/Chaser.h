#pragma once
#include "ofMain.h"
#include "GameObject.h"
#include "Player.h"

/*
#include "d:\software\of_v0.7.4_vs2010_release\apps\myapps\spectation4\092_json\src\gameobject.h"
#include "d:\software\of_v0.7.4_vs2010_release\apps\myapps\spectation4\092_json\src\player.h"
*/
class Chaser :
	public GameObject
{
public:
	void setup(ofPoint myPos, Player* myTarget, string myComingFrom);
    
	void customUpdate() override;
	void draw() override;
    void doThingsThatHappenWhenImHit(float damage) override;
    void affectThingTouchingMe(GameObject * toucher) override;
    bool dead;
    
	Player* target;
	float speed;
	float speedIncrease;
	float maxSpeed;
	string comingFrom;
	ofVec2f velf;
};

