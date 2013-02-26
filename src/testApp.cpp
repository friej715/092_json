#include "testApp.h"

/*
 
 to-do: 
 need now:
 - fix size of players
 - slower movement when blocking
 
 
 need soon:
 - vector of player positions to prevent kickback from joystick issues
 - integration of weapons/health/baddie drops
 - integrate secondary weapon
 - add in drop button
 */


//--------------------------------------------------------------
class threadedIRC : public ofThread{
    
public:
    
    
    IRC conn;
    int (*pntr)(char* params, irc_reply_data* hostd, void* conn);
    
    //char (*myBuffer)[1024];
    bool * shouldCheck;
    char * myString;
    
    //--------------------------
    threadedIRC(char* _myString, bool * _shouldCheck){
        myString = _myString;
        shouldCheck = _shouldCheck;
    }
    
    void start(){
        startThread(true, false);   // blocking, verbose
    }
    
    void stop(){
        stopThread();
    }
    
    //--------------------------
    void threadedFunction(){
        
        pntr = ((testApp*)ofGetAppPtr())->end_of_motd;
        conn.hook_irc_command("376", ((testApp*)ofGetAppPtr())->end_of_motd);
        
        // Mozilla's IRC rooms are easy to test with. They do seem to require 6697 r/t 6667 though
        conn.start("irc.foonetic.net", 6667, "jln", "jln", "jln", ""); // !FILL THESE IN! It's basically like, name, name, name, password
        
        conn.join("#janelastname"); // make sure to choose the right channel AND change it at the bottom
        
        while( isThreadRunning() != 0 ){
            if( lock() ){
                //printf("hey fucker\n");
                //cout<<"testo "<<(*testoPntr)<<"\n";

                conn.message_loop(myString, shouldCheck);
            
                unlock();
            }
        }
        
    }
};


//--------------------------------------------------------------
void testApp::setup(){	
    reset();
    
    tIRC = new threadedIRC(myString, &weShouldCheck);
    
    ((threadedIRC*)tIRC)->start();
    
    weShouldCheck = false;
}

//--------------------------------------------------------------
void testApp::update(){
    
    //cout<<"should check: "<<weShouldCheck<<endl;
    
    if ( ((threadedIRC*)tIRC)->conn.someoneHasJoined ) {
        // spawn a spectator
        
        Spectator s;
        s.name = ((threadedIRC*)tIRC)->conn.nameOfJoiner;
        spectators.push_back(s);
        cout << "joiner's name: " << s.name << endl;
        cout << "spec size: " << spectators.size() << endl;
        
        ((threadedIRC*)tIRC)->conn.someoneHasJoined = false;
    }
    
    if ( ((threadedIRC*)tIRC)->conn.someoneHasQuit ) {
        // delete that spectator
        string name = ((threadedIRC*)tIRC)->conn.nameOfQuitter;
        
        for (int i = 0; i < spectators.size(); i++) {
            if (spectators[i].name == name) {
                spectators.erase(spectators.begin() + i);
            }
        }
        
        cout << "quitter's name: " << name << endl;
        cout << "spec size: " << spectators.size() << endl;
        
        ((threadedIRC*)tIRC)->conn.someoneHasQuit = false;
        
    }
    
    if (weShouldCheck){
        cout << "hai brosz, this is ur name: " << ((threadedIRC*)tIRC)->conn.name << endl;
        cout << "hai brosz, this is ur msg: " << ((threadedIRC*)tIRC)->conn.message << endl;
        evaluateIrcChat(((threadedIRC*)tIRC)->conn.name, ((threadedIRC*)tIRC)->conn.message);
        
        ((threadedIRC*)tIRC)->conn.name = "";
        ((threadedIRC*)tIRC)->conn.message = "";
        
        //cout<<"call it!"<<endl;
        weShouldCheck = false;
        
        myIRCline = "";
        for (int i=0; i<1024; i++){
            //cout<<"letter "<<i<<endl;
            if ( myString[i] == '\0'){
               // cout<<"it's fucking done!"<<endl;
                break;
            }else{
                myIRCline+= myString[i];
            }
        
        
        }

        
        //cout<<endl<<"They said: "<<myIRCline<<endl;
        
    }
    
    ofxGamepad* pad1 = ofxGamepadHandler::get()->getGamepad(0);
    ofxGamepad* pad2 = ofxGamepadHandler::get()->getGamepad(1);
    
    if (pad1->getButtonValue(10) == true) {
        a.isBlocking = false; // yes, this is ridiculous--somehow this library is backwards
        //   a.canAttack = true;
    } else {
        a.isBlocking = true;
        a.canAttack = false;
    }
    
    if (pad1->getButtonValue(11) == false && a.isAttacking == false && a.canAttack == true && a.isHolding == true) {
        a.startTimeAttack = ofGetElapsedTimef();
        a.startWeaponAngle = ofRadToDeg(a.lastAngle);
        a.endWeaponAngle = a.startWeaponAngle + 90;
        a.currentWeaponAngle = a.startWeaponAngle;
        
        a.isAttacking = true;
        a.canAttack = false;
        
        a.attackCooldown = a.attackCooldownMax;
        
        checkPlayerInRange(a, b);
        checkCreatureInRange(a, creature);
    }
    
    if (pad1->getButtonValue(9) == false && a.sprintCooldown < 1) {
        a.sprintTimer = a.sprintTimerMax;
        a.sprintCooldown = a.sprintCooldownMax;
    }
    
    if (pad2->getButtonValue(10) == true) {
        b.isBlocking = false;
        //    b.canAttack = true;
    } else {
        b.isBlocking = true;
        b.canAttack = false;
    }
    
    if (pad2->getButtonValue(11) == false && b.isAttacking == false && b.canAttack == true && b.isHolding == true) {
        b.startTimeAttack = ofGetElapsedTimef();
        b.startWeaponAngle = ofRadToDeg(b.lastAngle);
        b.endWeaponAngle = b.startWeaponAngle + 90;
        b.currentWeaponAngle = b.startWeaponAngle;
        
        b.isAttacking = true;
        b.canAttack = false;
        
        b.attackCooldown = b.attackCooldownMax;
        
        checkPlayerInRange(b, a);
        checkCreatureInRange(b, creature);
    }
    
    if (pad2->getButtonValue(9) == false && b.sprintCooldown < 1) {
        b.sprintTimer = b.sprintTimerMax;
        b.sprintCooldown = b.sprintCooldownMax;
    }
    
    
    // a little easier to just adjust the vel by gamepad here rather than in player1
    a.vel.x = 0;
    a.vel.y = 0;
    
    b.vel.x = 0;
    b.vel.y = 0;
    
    a.vel.x+=(pad1->getAxisValue(0))*a.maxSpeed;
    a.vel.y+=(pad1->getAxisValue(1))*a.maxSpeed;
    
    b.vel.x+=(pad2->getAxisValue(0))*b.maxSpeed;
    b.vel.y+=(pad2->getAxisValue(1))*b.maxSpeed;
    
    a.angle = atan2(pad1->getAxisValue(3), pad1->getAxisValue(2));
    b.angle = atan2(pad2->getAxisValue(3), pad2->getAxisValue(2));

    cout<<"PLAYER A VEL "<<a.vel<<endl;
    
    
    
    
    for (int i = 0; i < objects.size(); i++) {
        objects[i]->preUpdate();
    }
    
    for (int i = 0; i < objects.size(); i++) {
        for (int k = 0; k < i; k++) {
            objects[i]->checkValidMovement(objects[k]);
        }
    }
    
    for (int i = 0; i < objects.size(); i++) {
        objects[i]->update();
    }
    
    
//    a.checkIsColliding(b);
//    b.checkIsColliding(a);

    
    
    
    for (int i = 0; i < weapons.size(); i++) {
        if (ofDist(a.pos.x, a.pos.y, weapons[i]->pos.x, weapons[i]->pos.y) < weapons[i]->image.width && weapons[i]->isHeld == false && a.isHolding == false) {
            weapons[i]->isHeld = true;
            weapons[i]->player = &a;
            a.isHolding = true;
        }
        
        if (ofDist(b.pos.x, b.pos.y, weapons[i]->pos.x, weapons[i]->pos.y) < weapons[i]->image.width && weapons[i]->isHeld == false && b.isHolding == false) {
            weapons[i]->isHeld = true;
            weapons[i]->player = &b;
            b.isHolding = true;
        }
    }
    

    
    creature.figureOutCloser(a, b);
    creature.update(a, b);
    creature.checkIsColliding(a);
    creature.checkIsColliding(b);
    
    if (ofDist(creature.pos.x, creature.pos.y, a.pos.x, a.pos.y) < creature.height && creature.canAttack == true) {
        creature.canAttack = false;
        creature.startTimeAttack = ofGetElapsedTimef();
        a.health -= 20;
    }

    if (ofDist(creature.pos.x, creature.pos.y, b.pos.x, b.pos.y) < creature.height && creature.canAttack == true) {
        creature.canAttack = false;
        creature.startTimeAttack = ofGetElapsedTimef();
        b.health -= 20;
    }
    
    collisionLogic();
    
    
    

    
    
}

//--------------------------------------------------------------
void testApp::draw(){
    
    for (int i = 0; i < objects.size(); i++) {
        objects[i]->draw();
    }
    
//    ofEnableAlphaBlending();
//    ofSetColor(255, 255, 255, 255);
//    for (int i = 0; i < weapons.size(); i++) {
//        if (!weapons[i]->isHeld) {
//            weapons[i]->draw();   
//        }
//        
//        int hBP = weapons[i]->heldByPlayer;
//        
//        if (hBP == 1) {
//            if (a.isAttacking) {
//                weapons[i]->draw();
//            }
//        }
//        
//        if (hBP == 2) {
//            if (b.isAttacking) {
//                weapons[i]->draw();
//            }
//        }
//    }
//    ofDisableAlphaBlending();
    
    
    creature.draw();

    
    //tetsing the line
    ofSetColor(255);
    ofDrawBitmapString(myIRCline, 10, 500);
    
}

//--------------------------------------------------------------
void testApp::keyPressed  (int key){ 
    //    if (key=='a')   a.turn(1);
    //    if (key=='s')   a.turn(-1);
    //    
    //    if (key==358)   b.turn(1);
    //    if (key==356)   b.turn(-1);
    
//    cout<<"spawn a damn health"<<endl;
//    ofPoint pnt;
//    pnt.set(50,50) ;
//    ofPoint vel;
//    vel.set(1,0) ;
//    Health * myHealth = new Health();
//    myHealth->setup("harry", pnt, vel);
//    objects.push_back(myHealth);
}

//--------------------------------------------------------------
void testApp::keyReleased  (int key){ 
    
    if (creature.isAlive == false) {
        creature.isAlive = true;
        creature.isActive = true;
    }
    
    
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
    //    a.pos.set(x, y);
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void testApp::mouseReleased(){
    
}
//--------------------------------------------------------------
void testApp::axisChanged(ofxGamepadAxisEvent& e)
{
    //cout << "AXIS " << e.axis << " VALUE " << ofToString(e.value) << endl;
}
//--------------------------------------------------------------
void testApp::buttonPressed(ofxGamepadButtonEvent& e)
{
    cout << "BUTTON " << e.button << endl;
}
//--------------------------------------------------------------
void testApp::buttonReleased(ofxGamepadButtonEvent& e)
{
    // some ass backwards nonsense going on over here??
    //cout << "BUTTON " << e.button << " PRESSED" << endl;
    
}
//--------------------------------------------------------------
void testApp::povChanged(ofxGamepadPovEvent &e)
{
	cout << "POV " << e.pov << " ";
    
	if( e.value & OIS::Pov::North ) //Going up
		std::cout << "North";
	else if( e.value & OIS::Pov::South ) //Going down
		std::cout << "South";
    
	if( e.value & OIS::Pov::East ) //Going right
		std::cout << "East";
	else if( e.value & OIS::Pov::West ) //Going left
		std::cout << "West";
    
	if( e.value == OIS::Pov::Centered ) //stopped/centered out
		std::cout << "Centered";
    
	cout << endl;
}

//--------------------------------------------------------------
void testApp::checkPlayerInRange(Player &x, Player &y) {
    // called when a player swings; prereq to calling below function
    cout << "seeing if in range" << endl;
    // if in range
    if (ofDist(x.pos.x, x.pos.y, y.pos.x, y.pos.y) < x.width*3) {
        checkPlayerHit(x, y);
    }
    
}

//--------------------------------------------------------------
void testApp::checkCreatureInRange(Player &x, Creature &c) {
    // called when a player swings; prereq to calling below function
    cout << "seeing if in range" << endl;
    // if in range
    if (ofDist(x.pos.x, x.pos.y, creature.pos.x, creature.pos.y) < creature.width + x.width) {
        checkHitCreature(x, creature);
    }
    
}


//--------------------------------------------------------------
void testApp::checkPlayerHit(Player &x, Player &y) { // thanks to andy wallace
    // in range and swinging
    float angleRange = ofDegToRad(45);
    
    //check if a is beating on b
    float diffAngle[3];
    //get the angle from a to b
    diffAngle[0] = atan2(y.pos.y - x.pos.y, y.pos.x - x.pos.x);
    //two alternate versions to check when this is on the line where the angle wraps around
    diffAngle[1] = diffAngle[0]+TWO_PI; // 180 degrees
    diffAngle[2] = diffAngle[0]-TWO_PI;
    
    bool wasFacing = false; //assume a was not facing b
    
    for (int i=0; i<3; i++){
        if ( abs(x.angle-diffAngle[i]) < angleRange){
            //a is facing b
            //x.col = ofColor::cyan;
            wasFacing = true;
            
            //check if b is facing a - if it is, then b is blocking
            float diffAngle2[3];
            //now get the angle from b to a
            diffAngle2[0] = atan2(x.pos.y - y.pos.y, x.pos.x - y.pos.x);
            
            //then make the two alternate verisons to check
            diffAngle2[1] = diffAngle2[0]+TWO_PI;
            diffAngle2[2] = diffAngle2[0]-TWO_PI;
            
            bool wasFacing2 = false;    //assume that b was facing away from a
            
            for (int k=0; k<3; k++){
                if (abs(y.angle-diffAngle2[k]) < angleRange){
                    wasFacing2 = true;
                }
                
            }
            
            if (wasFacing2 && y.isBlocking){
                //b is facing a and is blocking
                //y.col = ofColor::green;
                //   cout << "safe" << endl;
            } else {
                //b is facing away and can be hit
                //y.col = ofColor::red;
                cout << "hit" << endl;
                y.health-=10;
            }
            
        }
    }
    
    if (!wasFacing){
        //a is not even facing b
        //x.col = ofColor::gray;
        //y.col = ofColor::gray;
        // cout << "not even facing" << endl;
    }
    
    
}

//--------------------------------------------------------------
void testApp::checkHitCreature(Player &x, Creature &c) { // thanks to andy wallace
    // in range and swinging
    float angleRange = ofDegToRad(45);
    
    //check if a is beating on b
    float diffAngle[3];
    //get the angle from a to b
    diffAngle[0] = atan2(creature.pos.y - x.pos.y, creature.pos.x - x.pos.x);
    //two alternate versions to check when this is on the line where the angle wraps around
    diffAngle[1] = diffAngle[0]+TWO_PI; // 180 degrees
    diffAngle[2] = diffAngle[0]-TWO_PI;
    
    bool wasFacing = false; //assume a was not facing b
    
    for (int i=0; i<3; i++){
        if ( abs(x.angle-diffAngle[i]) < angleRange){
            //a is facing b
            x.col = ofColor::cyan;
            wasFacing = true;
            
        }
    }
    
    if (wasFacing) {
        creature.health -= 30;
    }
    cout << "hit " << endl;
    
    
}

//--------------------------------------------------------------
float testApp::scrapeValue(string field, string rawText){
    string fieldText = "\""+field+"\" : ";
    int startPos=rawText.find(fieldText)+fieldText.size();
    int endPos = rawText.find("\"", startPos);
    
    string backerNumText = rawText.substr(startPos,endPos-startPos);
    return ofToFloat(backerNumText);
}

void updateOSC() {
}


//--------------------------------------------------------------
void testApp::evaluateChat(string chat, int newLength){
	// bool foundPhrase = false;
	// bool foundplayer1Name = false;
	bool foundPossibleAction = false;
	bool foundDefiniteAction = false;
	//string player1Name;
	string player1Name;
	string actionName;
	string positionName;
	int currentCharLocation = 0;
    
	////skip over any spaces that show up before any words - just to be safe
	//while(chat[currentCharLocation] == ' ' && currentCharLocation < chat.length()) { 
	//	currentCharLocation++;
	//	if (currentCharLocation >= chat.length()) {break;}
	//} 
    
	//look through chat until the first word ends. Put everything in that first word into player1name.
	while(chat[currentCharLocation] != ' ' && currentCharLocation < chat.length()) {
		player1Name += chat[currentCharLocation];
		currentCharLocation++;
		if (currentCharLocation >= chat.length()) {break;}
	}
    
	currentCharLocation++; //move forward by one to skip the space bar
    
	//look through chat until the first word ends. Put everything in that first word into actionName.
	while(chat[currentCharLocation] != ' ' && currentCharLocation < chat.length()) {
		actionName += chat[currentCharLocation];
		currentCharLocation++;
		if (currentCharLocation >= chat.length()) {break;}
	}
    
	currentCharLocation++; //move forward by one to skip the space bar
    
	////skip over any spaces that show up between the words
	//while(chat[currentCharLocation] == ' ' && currentCharLocation < chat.length()) { 
	//	currentCharLocation++;
	//	if (currentCharLocation >= chat.length()) {break;}
	//} 
    
	//look through the second word in chat. Put everything in that second word into positionName.
	while(chat[currentCharLocation] != ' ' && currentCharLocation < chat.length()) {
		positionName += chat[currentCharLocation];
		currentCharLocation++;
		if (currentCharLocation >= chat.length()) {break;}
	}
    
	//make sure that actionName and positionName are lower case
	for(int i = 0; i < actionName.length(); i++) { actionName[i] = tolower(actionName[i]); }
	for(int i = 0; i < positionName.length(); i++) { positionName[i] = tolower(positionName[i]); }
    
	for(int i = 0; i < keywordList.size(); i++)
	{
		if(actionName == keywordList[i]){
			if(positionName == "left" || positionName == "right" || positionName == "top" || positionName == "bottom") { createChatObject(player1Name, actionName, positionName); }
			else { createChatObject(player1Name, actionName, "random"); }
		}
	}
}

void testApp::evaluateIrcChat(string playerName, string chat){

	string actionName;
	string positionName;
	int currentCharLocation = 0;
	//int chatLength = chat.length();
    
    
	//skip over any spaces that show up before any words - just to be safe
	while(chat[currentCharLocation] == ' ' && currentCharLocation < chat.length()) { 
		currentCharLocation++;
		if (currentCharLocation >= chat.length()) {break;}
	}
    
	//look through chat until the first word ends. Put everything in that first word into actionName.
	while(chat[currentCharLocation] != ' ' && currentCharLocation < chat.length()) {
		actionName += chat[currentCharLocation];
		currentCharLocation++;
		if (currentCharLocation >= chat.length()) {break;}
	}
    
	//skip over any spaces that show up before the next words
	while(chat[currentCharLocation] == ' ' && currentCharLocation < chat.length()) { 
		currentCharLocation++;
		if (currentCharLocation >= chat.length()) {break;}
	}
    
	//look through the second word in chat. Put everything in that second word into positionName.
	while(chat[currentCharLocation] != ' ' && currentCharLocation < chat.length()) {
		positionName += chat[currentCharLocation];
		currentCharLocation++;
		if (currentCharLocation >= chat.length()) {break;}
	}
    
	//make sure that actionName and positionName are lower case
	for(int i = 0; i < actionName.length(); i++) { actionName[i] = tolower(actionName[i]); }
	for(int i = 0; i < positionName.length(); i++) { positionName[i] = tolower(positionName[i]); }
    
	for(int i = 0; i < keywordList.size(); i++)
	{
		if(actionName == keywordList[i]){
			if(positionName == "left" || positionName == "right" || positionName == "top" || positionName == "bottom") { createChatObject(playerName, actionName, positionName); }
			else { createChatObject(playerName, actionName, "random"); }
		}
	}
}

//--------------------------------------------------------------
void testApp::createChatObject(string player1Name, string action, string location){
	cout << "player1: " << player1Name << " Action: " << action << " Location: " << location << "\n";
    
	ofVec2f pos;
	ofVec2f vel;
    
	if(location == "left"){
		pos.x = -100;
		pos.y = ofRandom(200, 568);
		vel.x = ofRandom(5, 8);
		vel.y = 0;
	}
	else if(location == "right"){
		pos.x = 1100;
		pos.y = ofRandom(200, 568);
		vel.x = ofRandom(-8, -5);
		vel.y = 0;
	}
	else if(location == "top"){
		pos.x = ofRandom(200, 824);
		pos.y = -100;
		vel.x = 0;
		vel.y = ofRandom(5, 8);
	}
	else if(location == "bottom"){
		pos.x = ofRandom(200, 824);
		pos.y = 800;
		vel.x = 0;
		vel.y = ofRandom(-8, -5);
	}
    
	cout << "player1: " << player1Name << " Action: " << action << " pos.x: " << pos.x << " pos.y: " << pos.y << " vel.x: " << vel.x << " vel.y: " << vel.y << "\n";
    
//    for (int i = 0; i < spectators.size(); i++) {
//        if (player1Name == spectators[i].name) {
//            
//            if(action == "health" && spectators[i].points > 300) { 
//                Health myHealth(player1Name, pos, vel);
//                healthList.push_back(myHealth);
//                spectators[i].points -= 300;
//            }
//            else if (action == "bullet" && spectators[i].points > 300) { 
//                Bullet myBullet(player1Name, pos, vel);
//                bulletList.push_back(myBullet);
//                spectators[i].points -= 300;
//            } else if (action == "creature" && creature.isAlive == false && spectators[i].points > 1200) {
//                creature.isActive = true;
//                creature.isAlive = true;
//                cout << "OH LOOK THINGS ARE GREAT AND LIFE IS COOL"<< endl;
//                spectators[i].points-= 1200;
//            }
//        }
//    }
    
    
	if(action == "health") { 
		Health * myHealth = new Health();
        myHealth->setup(player1Name, pos, vel);
        objects.push_back(myHealth);
	}
	else if (action == "bullet") { 
		Bullet * myBullet = new Bullet();
        myBullet->setup(player1Name, pos, vel);
        objects.push_back(myBullet);
        
	} else if (action == "creature" && creature.isAlive == false) {
        creature.isActive = true;
        creature.isAlive = true;
        cout << "OH LOOK THINGS ARE GREAT AND LIFE IS COOL"<< endl;
    }

}
//--------------------------------------------------------------
void testApp::reset() {
    gameState = 1;   
    
	//CHECK IF THERE EVEN IS A GAMEPAD CONNECTED
	if(ofxGamepadHandler::get()->getNumPads()>0){
        cout << "num " << ofxGamepadHandler::get()->getNumPads() << endl;
        
        
        ofxGamepad* pad1 = ofxGamepadHandler::get()->getGamepad(0);
        ofAddListener(pad1->onAxisChanged, this, &testApp::axisChanged);
        ofAddListener(pad1->onButtonPressed, this, &testApp::buttonPressed);
        ofAddListener(pad1->onButtonReleased, this, &testApp::buttonReleased);
        ofAddListener(pad1->onPovChanged, this, &testApp::povChanged);
        
        ofxGamepad* pad2 = ofxGamepadHandler::get()->getGamepad(1);
        ofAddListener(pad2->onAxisChanged, this, &testApp::axisChanged);
        ofAddListener(pad2->onButtonPressed, this, &testApp::buttonPressed);
        ofAddListener(pad2->onButtonReleased, this, &testApp::buttonReleased);
        ofAddListener(pad2->onPovChanged, this, &testApp::povChanged);
	}
    
	ofBackground(0,0,0);
	
	ofSetVerticalSync(true);
	ofSetFrameRate(60);
    
    Blocker blocker;
    //objects.push_back(&blocker);
    
    
    a.setup(ofGetWidth()/4, ofGetHeight()/4);
    b.setup(ofGetWidth()*.75, ofGetHeight()*.75);
    
    objects.push_back(&a);
    objects.push_back(&b);
    
    creature.setup();
    
    for (int i = 0; i < 2; i++) {
        Weapon * w = new Weapon();
        w->setup();
        objects.push_back(w);
        weapons.push_back(w);
    }
    
    angleRange = ofDegToRad(45);
    airship.loadFont("airship.ttf", 36);
    airshipLittle.loadFont("airship.ttf", 12);
    
    keywordList.push_back("health");
	keywordList.push_back("bullet");
    keywordList.push_back("creature");
    keywordList.push_back("join");
    
}
//--------------------------------------------------------------
void testApp::collisionLogic(){
	for(int i = 0; i < healthList.size(); i++){
		if(ofDist(a.pos.x, a.pos.y, healthList[i].pos.x, healthList[i].pos.y) < (a.width + healthList[i].width)){
			a.health += 20;
			healthList.erase(healthList.begin() + i);
		}
	}
    
    for(int i = 0; i < healthList.size(); i++){
		if(ofDist(b.pos.x, b.pos.y, healthList[i].pos.x, healthList[i].pos.y) < (b.width + healthList[i].width)){
			b.health += 20;
			healthList.erase(healthList.begin() + i);
		}
	}
    
    
	for(int i = 0; i < bulletList.size(); i++){
		if(ofDist(a.pos.x, a.pos.y, bulletList[i].pos.x, bulletList[i].pos.y) < (a.width + bulletList[i].width)){
			a.health -= 5;
			bulletList.erase(bulletList.begin() + i);
		}
	}
    
    for(int i = 0; i < bulletList.size(); i++){
		if(ofDist(b.pos.x, b.pos.y, bulletList[i].pos.x, bulletList[i].pos.y) < (b.width + bulletList[i].width)){
			b.health -= 5;
			bulletList.erase(bulletList.begin() + i);
		}
	}
    
}

//--------------------------------------------------------------
void testApp::removeObject(int num){
    delete objects[num];
    objects.erase(objects.begin() + num);
}

//--------------------------------------------------------------
int testApp::end_of_motd(char* params, irc_reply_data* hostd, void* conn)
{
    IRC* irc_conn=(IRC*)conn; /* notice that you are passed a pointer to the connection object */
	
    irc_conn->join("#janelastname");
    
    return 0;
}
//--------------------------------------------------------------
void testApp::cmd_thread(void* irc_conn) /* another thread just to wait until a key is pressed, and then quit */
{
    IRC* conn=(IRC*)irc_conn;
    
    getc(stdin); /* read in a character from standard in */
    //conn->quit("Leaving"); /* send the Quit command to the IRC server */
    //   _endthread(); /* end the thread */
}

