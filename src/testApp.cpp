#include "testApp.h"

/*
 
 to-do: 
    need now:
        - dash button && recharge for dash (only when not blocking)
        - slower movement when blocking
        
 
    need soon:
        - vector of player positions to prevent kickback from joystick issues
        - integration of weapons/health/baddie drops
        - integrate secondary weapon
        - add in drop button
 */


//--------------------------------------------------------------
void testApp::setup(){	
    reset();
    
}

//--------------------------------------------------------------
void testApp::update(){
    
    cout << "a health : " << a.health << endl;
    cout << "b health : " << b.health << endl;

    
//    if (int(ofGetElapsedTimef()) > lastCheckTime + 5) {
//        bool success;
//        success=justinTV.open("http://api.justin.tv/api/stream/list.json?channel=janelastname");
//    
//        if (isOnline == false) {
//            string jtv;
//            jtv = justinTV.getRawString();
//            
//            if (jtv.length() > 4) { 
//                isOnline = true;
//            } else {
//                isOnline = false;
//            }
//        }
//        
//        if (isOnline) {
//            bool success;
//            success=justinTV.open("http://api.justin.tv/api/stream/list.json?channel=janelastname");
//            
//            channelCount = scrapeValue("channel_count", justinTV.getRawString());
//            numViewers = channelCount;
//        }
//        lastCheckTime = ofGetElapsedTimef();
//    }
    
//    if (gameState == 1) {
        ofxGamepad* pad1 = ofxGamepadHandler::get()->getGamepad(0);
        ofxGamepad* pad2 = ofxGamepadHandler::get()->getGamepad(1);
        
        if (pad1->getButtonValue(8) == true) {
            a.isBlocking = false; // yes, this is ridiculous--somehow this library is backwards
            a.canAttack = true;
        } else {
            a.isBlocking = true;
            a.canAttack = false;
        }
        
        if (pad1->getButtonValue(9) == false && a.isAttacking == false && a.canAttack == true && a.isHolding == true) {
            a.startTimeAttack = ofGetElapsedTimef();
            a.startWeaponAngle = ofRadToDeg(a.lastAngle);
            a.endWeaponAngle = a.startWeaponAngle + 90;
            a.currentWeaponAngle = a.startWeaponAngle;

            a.isAttacking = true;
            a.canAttack = false;
            
            checkPlayerInRange(a, b);
        }
        
        if (pad2->getButtonValue(8) == true) {
            b.isBlocking = false;
            b.canAttack = true;
        } else {
            b.isBlocking = true;
            b.canAttack = false;
        }
        
        if (pad2->getButtonValue(9) == false && b.isAttacking == false && b.canAttack == true && b.isHolding == true) {
            b.startTimeAttack = ofGetElapsedTimef();
            b.startWeaponAngle = ofRadToDeg(b.lastAngle);
            b.endWeaponAngle = b.startWeaponAngle + 90;
            b.currentWeaponAngle = b.startWeaponAngle;
            
            b.isAttacking = true;
            b.canAttack = false;
            
            checkPlayerInRange(b, a);
        }
        
                
        // a little easier to just adjust the vel by gamepad here rather than in player1
        a.velocity.x = 0;
        a.velocity.y = 0;
        
        b.velocity.x = 0;
        b.velocity.y = 0;
        
        a.velocity.x+=(pad1->getAxisValue(0))*a.maxSpeed;
        a.velocity.y+=(pad1->getAxisValue(1))*a.maxSpeed;
        
        b.velocity.x+=(pad2->getAxisValue(0))*b.maxSpeed;
        b.velocity.y+=(pad2->getAxisValue(1))*b.maxSpeed;
        
        a.angle = atan2(pad1->getAxisValue(3), pad1->getAxisValue(2));
        b.angle = atan2(pad2->getAxisValue(3), pad2->getAxisValue(2));
        
        a.update();
        b.update();
        
//        for (int i = 0; i < enemies.size(); i++) {
//            enemies[i].update();
//            
//            if (ofDist(enemies[i].pos.x, enemies[i].pos.y, player1.pos.x, player1.pos.y) > ofDist(enemies[i].pos.x, enemies[i].pos.y, player2.pos.x, player2.pos.y)){
//                enemies[i].angle = atan2(player1.pos.y - enemies[i].pos.y, player1.pos.x - enemies[i].pos.x);
//            } else {
//                enemies[i].angle = atan2(player2.pos.y - enemies[i].pos.y, player2.pos.x - enemies[i].pos.x);
//            }
//        }
//       
    for (int i = 0; i < weapons.size(); i++) {
        if (ofDist(a.pos.x, a.pos.y, weapons[i].pos.x, weapons[i].pos.y) < weapons[i].image.width && weapons[i].isHeld == false && a.isHolding == false) {
            weapons[i].isHeld = true;
            weapons[i].heldByPlayer = 1;
            a.isHolding = true;
        }
        
        if (ofDist(b.pos.x, b.pos.y, weapons[i].pos.x, weapons[i].pos.y) < weapons[i].image.width && weapons[i].isHeld == false && b.isHolding == false) {
            weapons[i].isHeld = true;
            weapons[i].heldByPlayer = 2;
            b.isHolding = true;
        }
    }
    

    for (int i = 0; i < weapons.size(); i++) {
        if (weapons[i].isHeld == true) {
            if (weapons[i].heldByPlayer == 1 && a.isAttacking == false) {
                //cout << "a is not attacking" << endl;
                weapons[i].update(a.lastAngle, a.pos);
            } else if (weapons[i].heldByPlayer == 1 && a.isAttacking == true) {
                //cout << "a is attacking" << endl;
                weapons[i].update(a.currentWeaponAngle, a.pos);
            }
            
            if (weapons[i].heldByPlayer == 2 && b.isAttacking == false) {
                //cout << "b is not attacking" << endl;
                weapons[i].update(b.lastAngle, b.pos);
            } else if (weapons[i].heldByPlayer == 2 && b.isAttacking == true) {
                //cout << "b is attacking" << endl;
                weapons[i].update(b.currentWeaponAngle, b.pos);
            }
        }
    }

        
//        
//        if (ofGetElapsedTimef() > startTimeWave + intervalWave) {
//            newEnemyWave();
//            startTimeWave = ofGetElapsedTimef();
//        }
//        
//        
//        if (numViewers > lastNumViewers) {
//            player1.isCursed = true;
//            startTimeCurse = ofGetElapsedTimef();
//            lastNumViewers = numViewers;
//        }
//        
//        if (player1.isCursed == true) {
//            cursePlayer();
//        }
//        
//        if (player1.health <= 0) {
//          // gameState = 2;
//        }
//        
//        
//        for (int i = 0; i < healthList.size(); i++) {
//            healthList[i].update();
//        }
//        for (int i = 0; i < bulletList.size(); i++) {
//            bulletList[i].update();
//        }
//        collisionLogic();
//        
//    }
    
    
    
//    while(serverReceiver.hasWaitingMessages()){
//		// get the next message
//		ofxOscMessage m;
//		serverReceiver.getNextMessage(&m);
//		//Log received message for easier debugging of participants' messages:
//		ofLogVerbose("Server recvd msg " + getOscMsgAsString(m) + " from " + m.getRemoteIp());
//        
//		// check the address of the incoming message
//		if(m.getAddress() == "/typing"){
//			//Identify host of incoming msg
//			string incomingHost = m.getRemoteIp();
//			//See if incoming host is a new one:
//			if(std::find(knownClients.begin(), knownClients.end(), incomingHost)
//			   == knownClients.end()){
//				knownClients.push_back(incomingHost); //add new host to list
//			}
//			// get the first argument (we're only sending one) as a string
//			if(m.getNumArgs() > 0){
//				if(m.getArgType(0) == OFXOSC_TYPE_STRING){
//					//reimplemented message display:
//					//If vector has reached max size, delete the first/oldest element
//					if(serverMessages.size() == maxServerMessages){
//						serverMessages.erase(serverMessages.begin());
//					}
//					//Add message text at the end of the vector
//					serverMessages.push_back(m.getArgAsString(0));
//                    
//					//Broadcast message to other chat participants
//					broadcastReceivedMessage(m.getArgAsString(0));
//                    
//                    evaluateChat(m.getArgAsString(0), 0); // ramiro
//				}
//			}
//		}
//		// handle getting random OSC messages here
//		else{
//			ofLogWarning("Server got weird message: " + m.getAddress());
//		}
//	}
//    
//	// Client side:
//    
//	// OSC receiver queues up new messages, so you need to iterate
//	// through waiting messages to get each incoming message
//    
//	// check for waiting messages
//	while(clientReceiver.hasWaitingMessages()){
//		// get the next message
//		ofxOscMessage m;
//		clientReceiver.getNextMessage(&m);
//		ofLogNotice("Client just received a message");
//		// check the address of the incoming message
//		if(m.getAddress() == "/chatlog"){
//			// get the first argument (we're only sending one) as a string
//			if(m.getNumArgs() > 0){
//				if(m.getArgType(0) == OFXOSC_TYPE_STRING){
//					string oldMessages = clientMessages;
//					clientMessages = m.getArgAsString(0) + "\n" + oldMessages;
//				}
//			}
//		}
//	}
//    
//	//this is purely workaround for a mysterious OSCpack bug on 64bit linux
//	// after startup, reinit the receivers
//	// must be a timing problem, though - in debug, stepping through, it works.
//	if(ofGetFrameNum() == 60){
//		clientReceiver.setup(clientRecvPort);
//		serverReceiver.setup(serverRecvPort);
//    }

    
}

//--------------------------------------------------------------
void testApp::draw(){
    
//    if (gameState == 1) {
        
//        ofxGamepadHandler::get()->draw(10,10);
   
    a.draw();
    b.draw();

    for (int i = 0; i < weapons.size(); i++) {
        weapons[i].draw();
    }
    
//    weapon.draw();
        
//        ofNoFill();
        
//        for (int i = 0; i < enemies.size(); i++) {
//            enemies[i].draw();
//            ofRectMode(OF_RECTMODE_CORNER);
//            if (ofDist(player1.pos.x, player1.pos.y, enemies[i].pos.x, enemies[i].pos.y) < 10 && (player1.isHit == false)) {
//                ofEnableAlphaBlending();
//                ofFill();
//                ofSetColor(255, 255, 255, 100);
//                ofRect(0, 0, 1024, 768);
//                ofDisableAlphaBlending();
//                
//                player1.startTimeHit = ofGetElapsedTimef();
//                cout << "start time hit" << player1.startTimeHit << endl;
//                player1.health-=5;
//                player1.isHit = true;
//                
//            }
//        }
        
//        for (int i = 0; i < healthList.size(); i++) {
//            healthList[i].draw();
//        }
//        for (int i = 0; i < bulletList.size(); i++) {
//            bulletList[i].draw();
//        }
        
//    }
    
//    string debug = "Chat client\nSending messages to " + string(clientDestination) + ":"
//    + ofToString(clientSendPort);
//	string instructions = "type to create a new message.\nhit RETURN to send!";
//    
//	airshipLittle.drawString(debug, 10, 37);
//	airshipLittle.drawString(instructions, 10, 93);
//    
//	// what have we typed so far?
//	airshipLittle.drawString(clientTyping, 10, 160);
//    
//	//received messages:
//	airshipLittle.drawString(clientMessages, 10, 180);
//
//    
//    //Display some information about the server
//	string title = "Chat server";
//	airshipLittle.drawString(title, 542, 37);
//	title = "Listening for messages on port " + ofToString(serverRecvPort) + ".\nKnown chatters: "
//    + ofToString(knownClients.size());
//	airshipLittle.drawString(title, 542, 65);
//    
//	//Display received messages:
//	serverTyping = "";
//	// Concatenate a nice multiline string to display
//	for(unsigned int i = 0; i < serverMessages.size(); i++){
//		string oldTyping = serverTyping;
//		serverTyping = oldTyping + "\n" + serverMessages[i];
//	}

}

//--------------------------------------------------------------
void testApp::keyPressed  (int key){ 
//    if (key=='a')   a.turn(1);
//    if (key=='s')   a.turn(-1);
//    
//    if (key==358)   b.turn(1);
//    if (key==356)   b.turn(-1);
	
}

//--------------------------------------------------------------
void testApp::keyReleased  (int key){ 
    
//    if(key != OF_KEY_RETURN){
//		// some trickery: ignore the backspace key
//		if(key != OF_KEY_BACKSPACE){
//			clientTyping += key;
//		}
//		else{
//			if(clientTyping.size() > 0){
//				clientTyping.erase(clientTyping.end() - 1);
//			}
//		}
//	}
//	// hit Return, time to send the osc message
//	else{
//		// to send a string, create an ofxOscMessage object, give it an address
//		// and add a string argument to the object
//		ofxOscMessage m;
//		m.setAddress("/typing");
//		m.addStringArg(clientTyping);
//		clientSender.sendMessage(m);
//        
//		// clear out "typing"
//		clientTyping = "";
//	}
        
//    if (key == '=') {
//        numViewers++;
//    }
//    if (key == '-') {
//        numViewers--;
//    }
//    
//    
//    if (key == 'j') {
//        bool success;
//        success=justinTV.open("http://api.justin.tv/api/stream/list.json?channel=janelastname");
//        
//        if (success) {
//            cout << justinTV.getRawString() << endl; // will return [] if offline
//        } else {
//            cout << "oh shit y'all failed" << endl;
//        }
//        channelCount = scrapeValue("channel_count", justinTV.getRawString());
//        
//        numViewers = channelCount;
//    }
//    
//    if (key == ' ') {
//        if (gameState == 0) {
//            gameState = 1;
//        }
//        
////        if (gameState == 2) {
////            gameState = 1;
////        }
//    }
    
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
//    cout << e.button << endl;
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
void testApp::cursePlayer() {
    /* 
     potential curses:
     - add particles to chain (limited)
     - speed up enemies (limited)
     - add in another wave
     - decrease time between all waves
     - add in more harder enemies/add in primarily combos of fast and slow
     */
    
    
    intervalCurse = 5;
    
//    if (ofGetElapsedTimef() > startTimeCurse + intervalCurse) {
//        player1.isCursed = false;
//        cout << "done cursing" << endl;
//    }
    
    ofSetColor(255, 0, 0);
    
}
//--------------------------------------------------------------
void testApp::checkPlayerInRange(Player &x, Player &y) {
    // called when a player swings; prereq to calling below function
    cout << "seeing if in range" << endl;
    // if in range
    if (ofDist(x.pos.x, x.pos.y, y.pos.x, y.pos.y) < x.size*2) {
        checkPlayerHit(x, y);
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
            x.col = ofColor::cyan;
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
                y.col = ofColor::green;
             //   cout << "safe" << endl;
            } else {
                //b is facing away and can be hit
                y.col = ofColor::red;
                cout << "hit" << endl;
                y.health-=10;
            }
            
        }
    }
    
    if (!wasFacing){
        //a is not even facing b
        x.col = ofColor::gray;
        y.col = ofColor::gray;
       // cout << "not even facing" << endl;
    }
    
    
}

//--------------------------------------------------------------
void testApp::newEnemyWave() {
    for (int i = 0; i < 3; i++) {
//        Enemy e;
//        e.setup();
//        enemies.push_back(e);
//        cout << "wave" << endl;
    }
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
    // OSC receiver queues up new messages, so you need to iterate
	// through waiting messages to get each incoming message
    
	// check for waiting messages
//	while(serverReceiver.hasWaitingMessages()){
//		// get the next message
//		ofxOscMessage m;
//		serverReceiver.getNextMessage(&m);
//		//Log received message for easier debugging of participants' messages:
//		ofLogVerbose("Server recvd msg " + getOscMsgAsString(m) + " from " + m.getRemoteIp());
//        
//		// check the address of the incoming message
//		if(m.getAddress() == "/typing"){
//			//Identify host of incoming msg
//			string incomingHost = m.getRemoteIp();
//			//See if incoming host is a new one:
//			if(std::find(knownClients.begin(), knownClients.end(), incomingHost)
//			   == knownClients.end()){
//				knownClients.push_back(incomingHost); //add new host to list
//			}
//			// get the first argument (we're only sending one) as a string
//			if(m.getNumArgs() > 0){
//				if(m.getArgType(0) == OFXOSC_TYPE_STRING){
//					//reimplemented message display:
//					//If vector has reached max size, delete the first/oldest element
//					if(serverMessages.size() == maxServerMessages){
//						serverMessages.erase(serverMessages.begin());
//					}
//					//Add message text at the end of the vector
//					serverMessages.push_back(m.getArgAsString(0));
//                    
//					//Broadcast message to other chat participants
//					broadcastReceivedMessage(m.getArgAsString(0));
//				}
//			}
//		}
//		// handle getting random OSC messages here
//		else{
//			ofLogWarning("Server got weird message: " + m.getAddress());
//		}
//	}
//    
//	// Client side:
//    
//	// OSC receiver queues up new messages, so you need to iterate
//	// through waiting messages to get each incoming message
//    
//	// check for waiting messages
//	while(clientReceiver.hasWaitingMessages()){
//		// get the next message
//		ofxOscMessage m;
//		clientReceiver.getNextMessage(&m);
//		ofLogNotice("Client just received a message");
//		// check the address of the incoming message
//		if(m.getAddress() == "/chatlog"){
//			// get the first argument (we're only sending one) as a string
//			if(m.getNumArgs() > 0){
//				if(m.getArgType(0) == OFXOSC_TYPE_STRING){
//					string oldMessages = clientMessages;
//					clientMessages = m.getArgAsString(0) + "\n" + oldMessages;
//				}
//			}
//		}
//	}
//    
//	//this is purely workaround for a mysterious OSCpack bug on 64bit linux
//	// after startup, reinit the receivers
//	// must be a timing problem, though - in debug, stepping through, it works.
//	if(ofGetFrameNum() == 60){
//		clientReceiver.setup(clientRecvPort);
//		serverReceiver.setup(serverRecvPort);
//	}
}

//--------------------------------------------------------------
string testApp::getOscMsgAsString(ofxOscMessage m){
	string msg_string;
	msg_string = m.getAddress();
	msg_string += ":";
	for(int i = 0; i < m.getNumArgs(); i++){
		// get the argument type
		msg_string += " " + m.getArgTypeName(i);
		msg_string += ":";
		// display the argument - make sure we get the right type
		if(m.getArgType(i) == OFXOSC_TYPE_INT32){
			msg_string += ofToString(m.getArgAsInt32(i));
		}
		else if(m.getArgType(i) == OFXOSC_TYPE_FLOAT){
			msg_string += ofToString(m.getArgAsFloat(i));
		}
		else if(m.getArgType(i) == OFXOSC_TYPE_STRING){
			msg_string += m.getArgAsString(i);
		}
		else{
			msg_string += "unknown";
		}
	}
	return msg_string;
}
//--------------------------------------------------------------
void testApp::broadcastReceivedMessage(string chatmessage){
    
	//create a new OSC message
	ofxOscMessage m;
	m.setAddress("/chatlog");
	m.addStringArg(chatmessage);
    
	//Send message to all known hosts
	// use another port to avoid a localhost loop
	for(unsigned int i = 0; i < knownClients.size(); i++){
		serverSender.setup(knownClients[i], serverRecvPort + 1);
		m.setRemoteEndpoint(knownClients[i], serverRecvPort + 1);
		serverSender.sendMessage(m);
		ofLogVerbose("Server broadcast message " + m.getArgAsString(0) + " to " + m.getRemoteIp()
					 + ":" + ofToString(m.getRemotePort()));
	}
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
	if(action == "health") { 
		Health myHealth(player1Name, pos, vel);
		healthList.push_back(myHealth);
	}
	else if (action == "bullet") { 
		Bullet myBullet(player1Name, pos, vel);
        bulletList.push_back(myBullet);
	}
}
//--------------------------------------------------------------
void testApp::reset() {
    gameState = 1;   
    //    // JustinTV API (p much same as twitch) http://www.justin.tv/p/api
    //    bool success;
    //    success=justinTV.open("http://api.justin.tv/api/stream/list.json?channel=janelastname");
    //    
    //    if (success) {
    //        cout << justinTV.getRawString() << endl; // will return [] if offline
    //        string jtv;
    //        jtv = justinTV.getRawString();
    //        if (jtv.length() > 4)   isOnline = true;
    //    } else {
    //        cout << "oh shit y'all failed" << endl;
    //    }
    //    
    //    if (isOnline) {
    //        channelCount = scrapeValue("channel_count", justinTV.getRawString());
    //        channelViewCount = scrapeValue("channel_view_count", justinTV.getRawString());
    //        
    //        cout << "channel_count : " << channelCount << endl;
    //        cout << "channel_view_count : " << channelViewCount << endl;
    //    }
    
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
        
    a.setup(50, 50);
    b.setup(500, 500);
    //weapon.setup();
    
    for (int i = 0; i < 2; i++) {
        Weapon w;
        w.setup();
        weapons.push_back(w);
    }
    
    angleRange = ofDegToRad(45);
    
    
    //    // OSC STUFF --------
    //    //Server side
    //	//listen for incoming messages on a port; setup OSC receiver with usage:
    //	serverRecvPort = 9000;
    //	serverReceiver.setup(serverRecvPort);
    //	maxServerMessages = 38;
    //    
    //	//Client side
    //	//clientDestination = "localhost";
    //    clientDestination	= "192.168.0.100"; // if you send to another instance enter IP here
    //	clientSendPort = 9000;
    //	clientSender.setup(clientDestination, clientSendPort);
    //    
    //    clientRecvPort = clientSendPort + 1;
    //	//clientRecvPort = clientSendPort - 1;
    //	clientReceiver.setup(clientRecvPort);
    //    
    //    keywordList.push_back("health");
    //	keywordList.push_back("bullet");
    
}
//--------------------------------------------------------------
void testApp::collisionLogic(){
//	for(int i = 0; i < healthList.size(); i++){
//		if(ofDist(player1.particles[0].pos.x, player1.particles[0].pos.y, healthList[i].pos.x, healthList[i].pos.y) < (player1.size + healthList[i].size)){
//			player1.health += 20;
//			healthList.erase(healthList.begin() + i);
//		}
//	}
//	for(int i = 0; i < bulletList.size(); i++){
//		if(ofDist(player1.particles[0].pos.x, player1.particles[0].pos.y, bulletList[i].pos.x, bulletList[i].pos.y) < (player1.size + bulletList[i].size)){
//			player1.health -= 5;
//			bulletList.erase(bulletList.begin() + i);
//		}
//	}
}