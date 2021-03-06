#ifndef _TEST_APP
#define _TEST_APP

#include "ofMain.h"
#include "Player.h"
#include "ofxGamepadHandler.h"
#include "Health.h"
#include "Bullet.h"
#include "Weapon.h"
#include "Creature.h"
#include "Spectator.h"
#include "Irc.h"
#include "Blocker.h"
#include "GameObject.h"
#include "Chaser.h"


class testApp : public ofBaseApp{
	
	public:
		
		void setup();
		void update();
		void draw();
		
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased();
    
    // IRC
    static int end_of_motd(char* params, irc_reply_data* hostd, void* conn);
    void cmd_thread(void* irc_conn);
    
    ofThread * tIRC;
    
    vector<string> messages;
    
    
    // gamepad functions
    void axisChanged(ofxGamepadAxisEvent &e);
    void buttonPressed(ofxGamepadButtonEvent &e);
    void buttonReleased(ofxGamepadButtonEvent &e);
    void povChanged(ofxGamepadPovEvent &e);		

    
    vector<GameObject *> objects;
    vector<Weapon *> weapons;
    vector<Creature *> creatures;
    
    Player a;
    Player b;
    
    vector<Spectator> spectators;
    
    float angleRange;
    
    void removeObject(int num);
    
    
    // interactivity
    
    float lastCheckTime;
    
    bool isOnline;
    
    float scrapeValue(string field, string rawText); // thanks to andy wallace for this

    ofTrueTypeFont airship;
    ofTrueTypeFont airshipLittle;
    
    int gameState;
    void reset();
    
    
    
    
    
    // ramiro code
    void evaluateChat(string chat, int newLength);
    void evaluateIrcChat(string playerName, string chatText);
    void createChatObject(string player1Name, string action, string location, string modifier);
    void collisionLogic();
    
    vector <string> keywordList;
    vector <Health> healthList;
    vector <Bullet> bulletList;
    
    //andy's code
    bool weShouldCheck;
    char myString[1024];
    string myIRCline;
};

#endif	

