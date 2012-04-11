#ifndef GUARD_ofxBaseKeyframe
#define GUARD_ofxBaseKeyframe

/*    _____    ___     
 *   /    /   /  /     ofxPlaylist
 *  /  __/ * /  /__    (c) ponies & light, 2009-2012. 
 * /__/     /_____/    poniesandlight.co.uk
 * 
 * ofxBaseKeyframe.h
 * Created by Timothy Gfrerer on 19/10/2010.
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include "ofMain.h"

enum TweenTransition{
	TWEEN_PAUSE   	   = 0,
	TWEEN_EASE_IN      = 1,
	TWEEN_EASE_IN_OUT  = 3,
	TWEEN_EASE_OUT	   = 4
};


class ofxBaseKeyframe {
public:
	ofxBaseKeyframe(){};

	virtual ~ofxBaseKeyframe(){ 
#ifdef PLAYLIST_DEBUG_MODE
		ofLog(OF_LOG_VERBOSE) << ofToString(ofGetFrameNum()) << ": ~ofxKeyFrame();";
#endif

	};     // by calling this function virtual I make sure to call the destructor for 
		   // the derived class - and not for the parent class!
	
	bool is_idle;
	TweenTransition tween_transition;        
	
	virtual void start(){};
	virtual void execute()=0;  

	virtual int getDuration()=0;

	bool hasStarted;

};




#endif
