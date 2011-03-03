#include "testApp.h"





//--------------------------------------------------------------
void testApp::setup(){
	ofSetLogLevel(OF_LOG_VERBOSE);
	
for (int i=0; i<10; i++) {
	animatedRectangles.push_back(new AnimatedRectangle());
	animatedRectangles.push_back(new AnimatedRectangle());
}	
}

//--------------------------------------------------------------
void testApp::update(){
	vector<AnimatedRectangle *>::iterator it = animatedRectangles.begin();
	
	while (it != animatedRectangles.end()) {
		// draw that Rectangle.
		(*it)->update();
		it++;
	}
	
}

//--------------------------------------------------------------
void testApp::draw(){
	vector<AnimatedRectangle *>::iterator it = animatedRectangles.begin();
	
	while (it != animatedRectangles.end()) {
		// draw that Rectangle.
		(*it)->draw();
		it++;
	}
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

	int index = int(ofRandom(animatedRectangles.size()));
	
	// first an elegant compound movement,
	animatedRectangles[index]->addNewKeyFrame(new Tweener(&animatedRectangles[index]->pos.x, TWEEN_SIN, &animatedRectangles[index]->pos.x, ofRandomuf()*ofGetWidth(), 3000));
	animatedRectangles[index]->addToKeyFrame(new Tweener(&animatedRectangles[index]->angle, TWEEN_SIN, &animatedRectangles[index]->angle, ofRandomuf()*360., 1500));
	// then a delicate change colour change.
	animatedRectangles[index]->addNewKeyFrame(new Tweener(&animatedRectangles[index]->color.r, TWEEN_SIN, &animatedRectangles[index]->color.r, ofRandomuf()*255.f, 500));
	animatedRectangles[index]->addToKeyFrame(new Tweener(&animatedRectangles[index]->color.g, TWEEN_SIN, &animatedRectangles[index]->color.g, ofRandomuf()*255.f, 3000));
	animatedRectangles[index]->addToKeyFrame(new Tweener(&animatedRectangles[index]->color.b, TWEEN_SIN, &animatedRectangles[index]->color.b, ofRandomuf()*255.f, 750));

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