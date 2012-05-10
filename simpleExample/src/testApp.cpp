#include "testApp.h"


//--------------------------------------------------------------
void testApp::setup(){
	ofSetLogLevel(OF_LOG_VERBOSE);
	ofSetFrameRate(60);
	ofSetVerticalSync(TRUE);

	// init
	rectRotation = 0.f;
	rectPos.set(ofRandomWidth(), ofRandomHeight()); 
}

//--------------------------------------------------------------
void testApp::update(){

	// this will update all values controlled by mainPlaylist. 
	// to see which values are controlled by mainPlaylist, 
	// jump to testApp::mouseReleased(), which is where the
	// playlist is set up.
	
	mainPlaylist.update();
}

//--------------------------------------------------------------
void testApp::draw(){
	
	ofColor(128);
	
	ofPushMatrix();
	ofTranslate(rectPos);
	ofRotateZ(rectRotation);
	ofRect(0,0, 200, 100);
	ofPopMatrix();

}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

	using namespace Playlist;
	
	// this will move a rectangle to the mouse position.
	// and then wobble sigthly.
	
	ofVec3f targetPosition = ofVec3f(x, y);
	
	// (1) take 1000ms to move to random target point on x axis,
	// (2) wait 500ms, then take 500ms to move to random target point on y axis
	
	mainPlaylist.addKeyFrame(	Action::tween(200.f, &rectPos.x, targetPosition.x));		// -- (1)
	mainPlaylist.addToKeyFrame(	Action::tween(200.f, &rectPos.y, targetPosition.y));		// -- (2)
	
	// pause for 200 ms - you will only notice this if you click repeatedly.
	// mainPlaylist.addKeyFrame(Action::pause(200.f));

	// wobble slightly once target position reached.
	mainPlaylist.addKeyFrame(Action::tween(1000.f, &rectRotation, ofRandomf()*90, TWEEN_BOUNCE, TWEEN_EASE_OUT));

	// --> try other TWEEN_ variations with the above- it's fun!
	// --> try other TWEEN_EASE_ variations with the above - it's geeky!
	
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}