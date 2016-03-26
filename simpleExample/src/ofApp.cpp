#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){
	ofSetLogLevel(OF_LOG_VERBOSE);
	ofSetFrameRate(60);
	ofSetVerticalSync(TRUE);

	// init
	rectRotation = 0.f;
	rectPos.set(ofRandomWidth(), ofRandomHeight()); 
}

//--------------------------------------------------------------
void ofApp::update(){

	// this will update all values controlled by mainPlaylist. 
	// to see which values are controlled by mainPlaylist, 
	// jump to ofApp::mouseReleased(), which is where the
	// playlist is set up.
	
	mainPlaylist.update();
	
}

//--------------------------------------------------------------
void ofApp::draw(){
	
	ofColor(128);
	
	ofPushMatrix();
	ofTranslate(rectPos);
	ofRotateZ(rectRotation);
	ofDrawRectangle(0,0, 200, 100);
	ofPopMatrix();

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

	using namespace Playlist;
	
	// this will move a rectangle to the mouse position.
	// and then wobble sigthly.
	
	ofVec3f targetPosition = ofVec3f(x, y);
	
	// (1) take 200ms to move to the mouse position on x axis,
	// (2) take 200ms to move to the mouse position on y axis in sync with x.
	
	mainPlaylist.addKeyFrame(	Action::tween(200.f, &rectPos.x, targetPosition.x));		// -- (1)
	mainPlaylist.addToKeyFrame(	Action::tween(200.f, &rectPos.y, targetPosition.y));		// -- (2)
	mainPlaylist.addKeyFrame(Action::event([this](){ ofLogNotice() << "event 1: " << rectPos; }));
	
	// pause for 200 ms - you will only notice this if you click repeatedly.
	// mainPlaylist.addKeyFrame(Action::pause(200.f));

	// wobble slightly once target position reached.
	mainPlaylist.addKeyFrame(Action::tween(1000.f, &rectRotation, ofRandomf()*90, TWEEN_BOUNCE, TWEEN_EASE_OUT));
	mainPlaylist.addKeyFrame(Action::event([this](){ ofLogNotice() << "event 2: " << rectPos; }));
	// --> try other TWEEN_ variations with the above- it's fun!
	// --> try other TWEEN_EASE_ variations with the above - it's geeky!
	
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}