//
//  Health.h
//  json
//
//  Created by Jane Friedhoff on 2/1/13.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#ifndef json_Health_h
#define json_Health_h
#include "ofMain.h" 
#include "GameObject.h"

class Health : public GameObject
{
public:
	void setup(string myPlayerName, ofVec2f myPos, ofVec2f myVel);
    
	void customUpdate() override;
	void draw() override;
    
    void doThingsThatHappenWhenImHit(float damage) override;
    void affectThingTouchingMe(GameObject * toucher) override;
    
	string playerName;
    
    ofTrueTypeFont airshipLittle;
};


#endif
