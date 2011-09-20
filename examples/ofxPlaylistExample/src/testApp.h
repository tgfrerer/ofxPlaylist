#pragma once

/*
 *                   .. .. ......                            
 *                   .. ..     ..                            
 *     .....  .....  .. ..    ..           ....  ..... ..  ..
 *    ..  .. ..  .. ..  ..   ...          ..  . ..  .. ......
 *    ..  .. ..  .. ......     ..         ..    ..  .. .. . .
 *   ...  .....  ..     .. ..  ..   ..   ...   ...  .. .. . .
 *   . .... . ....      ..  ....    ..  .. ..... .... ...   .
 *                                                         
 */

// tig, 17.03:
// now able to incorporate any ofxEasing-function
// now compatible w/ frame-by-frame animations and able to link up with MPE


#include "ofMain.h"
#include "animated_rectangle.h"
#include "ofxPlaylist.h"

class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed  (int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		void onKeyframe(ofxPlaylistEventArgs& args);
		
	AnimatedRectangle eins;
	
	vector<AnimatedRectangle *> animatedRectangles;
};
