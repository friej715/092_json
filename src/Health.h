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
class Health
{
public:
	Health(string myPlayerName, ofVec2f myPos, ofVec2f myVel);
	~Health(void);
    
	void update();
	void draw();
    
	string playerName;
	ofVec2f pos;
	ofVec2f vel;
    
    int size;
    
    ofTrueTypeFont airshipLittle;
};


#endif
