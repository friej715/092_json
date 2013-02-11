//
//  Bullet.h
//  json
//
//  Created by Jane Friedhoff on 2/1/13.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#ifndef json_Bullet_h
#define json_Bullet_h
#include "ofMain.h"

class Bullet
{
public:
	Bullet(string myPlayerName, ofVec2f myPos, ofVec2f myVel);
	~Bullet(void);
    
	void update();
	void draw();
    
	string playerName;
	ofVec2f pos;
	ofVec2f vel;
    
    int size;
    
    ofTrueTypeFont airshipLittle;
};


#endif
