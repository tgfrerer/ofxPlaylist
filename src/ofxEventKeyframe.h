#ifndef GUARD_keyframeEvent
#define	GUARD_keyframeEvent

/*
 *  ofxEventKeyframe.h
 *
 *
 *                                                   ____         ___                __      __      
 *                          __                     /|  _ \       /\_ \    __        /\ \    /\ \__   
 *   _____     ___     ___ /\_\     __    ____     |/\   |       \//\ \  /\_\     __\ \ \___\ \ ,_\  
 *  /\ '__`\  / __`\ /' _ `\/\ \  /'__`\ /',__\     \// __`\/\     \ \ \ \/\ \  /'_ `\ \  _ `\ \ \/  
 *  \ \ \L\ \/\ \L\ \/\ \/\ \ \ \/\  __//\__, `\    /|  \L>  <_     \_\ \_\ \ \/\ \L\ \ \ \ \ \ \ \_ 
 *   \ \ ,__/\ \____/\ \_\ \_\ \_\ \____\/\____/    | \_____/\/     /\____\\ \_\ \____ \ \_\ \_\ \__\
 *    \ \ \/  \/___/  \/_/\/_/\/_/\/____/\/___/      \/____/\/      \/____/ \/_/\/___L\ \/_/\/_/\/__/
 *     \ \_\                                                                      /\____/            
 *      \/_/                                                                      \_/__/             
 *         
 *
 *  Created by Timothy Gfrerer on 13/04/2011.
 *  Copyright 2011 ponies & light. All rights reserved.
 */

#include "ofMain.h"
#include "ofxPlaylistAction.h"


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

class ofxCoreKeyframeEvents
{
public:
  	ofEvent<ofxPlaylistEventArgs> onKeyframe;
};

extern ofxCoreKeyframeEvents ofxKeyframeEvents;

template<class ListenerClass>
void ofxKeyframeAnimRegisterEvents(ListenerClass * listener){
    ofAddListener(ofxKeyframeEvents.onKeyframe, listener, &ListenerClass::onKeyframe);
}

template<class ListenerClass>
void ofxKeyframeAnimUnRegisterEvents(ListenerClass * listener){
    ofRemoveListener(ofxKeyframeEvents.onKeyframe, listener, &ListenerClass::onKeyframe);
}


// ------------------------------------

class ofxEventKeyframe : public ofxPlaylistAction {
public:
	
	template<class ListenerClass>
	ofxEventKeyframe(ListenerClass * listener, string _message){							// initialise with <#message#> .
		is_idle = FALSE;     // bool value to give notice that the keyframe is done with.
		message = _message;
		pSender = static_cast<void *>(listener);
	};

	void start(){
		// do essentially nothing.
	};	
	void execute(){
		// call the Event as soon as possible.
		// call event here
		if (is_idle == FALSE) {
			ofxPlaylistEventArgs keyframeEventArgs;
			keyframeEventArgs.message = message;
			keyframeEventArgs.pSender = pSender;
			// ofxCoreKeyframeEvents Ev;
			ofLog(OF_LOG_VERBOSE) << ofToString(ofGetFrameNum()) << ": EventKeyframe calling event, passing message: " << message ;
			ofNotifyEvent(ofxKeyframeEvents.onKeyframe, keyframeEventArgs);
		}
		is_idle = TRUE;	// get rid of it.
	};
	
	int getDuration(){return 0;};
	
private:
	string message;
	void* pSender;
};




#endif