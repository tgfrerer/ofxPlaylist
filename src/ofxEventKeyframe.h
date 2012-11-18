#ifndef GUARD_keyframeEvent
#define	GUARD_keyframeEvent

/*    _____    ___     
 *   /    /   /  /     ofxPlaylist
 *  /  __/ * /  /__    (c) ponies & light, 2009-2012. 
 * /__/     /_____/    poniesandlight.co.uk
 * 
 * ofxEventKeyframe.h
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

#include "ofMain.h"
#include "ofxBaseKeyframe.h"



/*	
 
 // Example onKeyFrame method:
 
 void testApp::onKeyframe(ofxPlaylistEventArgs& args){
 
 // this check is only necessary if you want to be absolutely sure that 
 // the onKeyFrame Event was sent by the same object as the receiver.
 if (args.pSender != static_cast<void*>(this)) return;
 
 ofLog(OF_LOG_VERBOSE) << "Keyframe Event received for (" << args.pSender << "): " << args.message << ": " << ofGetFrameNum();
 
 }
 
 */



class ofxPlaylistEventArgs : public ofEventArgs
{
public:
    string message;
	void* pSender;

	ofxPlaylistEventArgs()
	:message("")
	,pSender(NULL)
	{};
	
};

class ofxPlaylistEvents
{
public:
  	ofEvent<ofxPlaylistEventArgs> onKeyframe;
};

extern ofxPlaylistEvents ofxKeyframeEvents;

namespace Playlist {
	// friendlier API
	// 
	// register your class as a listener for the onKeyframe Event by calling:
	//
	// Playlist::addListenerForOnKeyframeEvent()
	//
	// Don't forget to then remove the listener in the destructor of your class.
	

		template<class ListenerClass>
		void addListenerForOnKeyframeEvent(ListenerClass * listener){
			ofAddListener(ofxKeyframeEvents.onKeyframe, listener, &ListenerClass::onKeyframe);
		}
		
		template<class ListenerClass>
		void removeListenerForOnKeyframeEvent(ListenerClass * listener){
			ofRemoveListener(ofxKeyframeEvents.onKeyframe, listener, &ListenerClass::onKeyframe);
		}
}

template<class ListenerClass>
void ofxKeyframeAnimRegisterEvents(ListenerClass * listener){
	ofAddListener(ofxKeyframeEvents.onKeyframe, listener, &ListenerClass::onKeyframe);
}

template<class ListenerClass>
void ofxKeyframeAnimUnRegisterEvents(ListenerClass * listener){
	ofRemoveListener(ofxKeyframeEvents.onKeyframe, listener, &ListenerClass::onKeyframe);
}


// ------------------------------------

class ofxEventKeyframe : public ofxBaseKeyframe {
	string message;
	void* pSender;
	
	bool isDelayed;
	const int delay_steps;
	
	long startValue;
	const bool isFrameBased;
	int step;


public:
	
	template<class ListenerClass>
	ofxEventKeyframe(ListenerClass * listener, string _message)
	: isDelayed (FALSE)
	, delay_steps(0)
	, startValue(0)
	, isFrameBased(TRUE)
	, step(0)
	{							// initialise with message .
		is_idle = FALSE;
		hasStarted = FALSE;

		message = _message;
		pSender = listener;
	};

	template<class ListenerClass>
	ofxEventKeyframe(float delayMillisecs, ListenerClass * listener, string _message)
	: isDelayed (TRUE)
	, delay_steps(delayMillisecs)
	, startValue(0)
	, isFrameBased(FALSE)
	, step(0)
	{							// initialise with  message.
		is_idle = FALSE;
		hasStarted = FALSE;
		message = _message;
		pSender = listener;
	};

	template<class ListenerClass>
	ofxEventKeyframe(int delayFrames, ListenerClass * listener, string _message)
	: isDelayed (TRUE)
	, delay_steps(0)
	, startValue(0)
	, isFrameBased(TRUE)
	, step(0)
	{							// initialise with message .
		is_idle = FALSE;
		hasStarted = FALSE;
		message = _message;
		pSender = listener;
	};

	void start();
	void execute();
	bool delayHasEnded();
	int getDuration()	{return delay_steps;};


};




#endif