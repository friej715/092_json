#ifndef _TEST_APP
#define _TEST_APP

#include "ofMain.h"
#include "particle.h"
#include "spring.h"
#include "Enemy.h"
#include "Player.h"
#include "ofxJSONElement.h"
#include "ofxGamepadHandler.h"
#include "ofxOsc.h"
#include "Health.h"
#include "Bullet.h"
#include "Weapon.h"


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
		//void windowResized(int w, int h);
		
    
    // gamepad functions
    void axisChanged(ofxGamepadAxisEvent &e);
    void buttonPressed(ofxGamepadButtonEvent &e);
    void buttonReleased(ofxGamepadButtonEvent &e);
    void povChanged(ofxGamepadPovEvent &e);		

    
    Player a;
    Player b;
    
    float angleRange;
    
    void checkPlayerInRange(Player &pA, Player &pB);
    void checkPlayerHit(Player &pA, Player &pB);
    
    //Weapon weapon;
    vector<Weapon> weapons;
    
    
    // enemiessszzzz
    vector<Enemy> enemies;
    
    float startTimeWave;
    float intervalWave;
    
    void newEnemyWave();
    
    
    // interactivity
    int numViewers;
    int lastNumViewers; // might be useful to hold so can see change over time?
    
    void cursePlayer();
    float startTimeCurse;
    float intervalCurse;
    
    int steadyNumParticles;
    
    ofxJSONElement justinTV;
    
    float channelCount;
    float channelViewCount;
    
    float lastCheckTime;
    
    bool isOnline;
    
    float scrapeValue(string field, string rawText); // thanks to andy wallace for this
    

    ofTrueTypeFont airship;
    ofTrueTypeFont airshipLittle;
    
    int gameState;
    void reset();
    
    
    
    
    
    // OSC ----------
    
    
    // Client side:
    
    ofxOscSender clientSender; // all-important ofxOscSender object
    string clientDestination; // IP address we're sending to
    int clientSendPort; // port we're sending to
    string clientTyping; // what we're going to send: some stuff you typed
    
    ofxOscReceiver clientReceiver; // OSC receiver
    int clientRecvPort; // port where we listen for messages
    string clientMessages; // string containing the received messages for display
    
    //----------------------------------------
    // Server side:
    ofxOscReceiver serverReceiver; // OSC receiver
    int serverRecvPort; // port we're listening on: must match port from sender!
    string serverTyping; //messages you've received from the clientes
    
    // Message display variables
    vector<string>serverMessages; //vector containing the received messages for display
    unsigned int maxServerMessages; //nr of messages fitting on the screen
    
    vector<string>knownClients; //collected IP's of chat participants
    ofxOscSender serverSender;
    
    //Distribute a received message among the known hosts
    void broadcastReceivedMessage(string chatmessage);
    
    // Parse an OscMessage into a string for easy logging
    string getOscMsgAsString(ofxOscMessage m);
    
    void updateOSC();
    
    
    
    // ramiro code
    void evaluateChat(string chat, int newLength);
    void createChatObject(string player, string action, string location);
    void collisionLogic();
    
    vector <string> keywordList;
    vector <Health> healthList;
    vector <Bullet> bulletList;
};

#endif	

