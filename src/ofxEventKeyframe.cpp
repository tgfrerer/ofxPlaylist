/*    _____    ___     
 *   /    /   /  /     ofxPlaylist
 *  /  __/ * /  /__    (c) ponies & light, 2009-2012. 
 * /__/     /_____/    poniesandlight.co.uk
 * 
 * ofxEventKeyframe.cpp
 * Created by Timothy Gfrerer on 13/04/2011.
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


#include "ofxEventKeyframe.h"

ofxPlaylistEvents ofxKeyframeEvents;		// declare the extern as static

// ----------------------------------------------------------------------

void ofxEventKeyframe::start(){
	is_idle = FALSE;     // bool value to give notice that the keyframe is done with.
	(isFrameBased) ? startValue = 0 : startValue = ofGetSystemTime();
	step = 0;
	hasStarted = TRUE;
};

// ----------------------------------------------------------------------

void ofxEventKeyframe::execute(){
	// call the Event as soon as possible.
	// call event here
	if (is_idle == FALSE) {
		
		if (hasStarted == FALSE) start();
		
		step = isFrameBased ? startValue : (ofGetSystemTime() - startValue);
		if (isFrameBased) startValue++;		// increase frame count if the animation is by-frame
		
		delayHasEnded();	// check whether delay has ended.
		
		if (isDelayed) return;
		// ----------| invariant: delay has ended, we are ready to execute:
		
		ofxPlaylistEventArgs keyframeEventArgs;
		keyframeEventArgs.message = message;
		keyframeEventArgs.pSender = pSender;
		// ofxCoreKeyframeEvents Ev;
#ifdef PLAYLIST_DEBUG_MODE
		ofLog(OF_LOG_VERBOSE) << ofToString(ofGetFrameNum()) << ": EventKeyframe calling event, passing message: " << message ;
#endif
		ofNotifyEvent(ofxKeyframeEvents.onKeyframe, keyframeEventArgs);
		is_idle = TRUE;	// get rid of it.
	}
}

// ----------------------------------------------------------------------

bool ofxEventKeyframe::delayHasEnded() {
	if (isDelayed && (step >= delay_steps)) {
		isDelayed = false;
		return true;
	}
	return false;
};

// ----------------------------------------------------------------------
