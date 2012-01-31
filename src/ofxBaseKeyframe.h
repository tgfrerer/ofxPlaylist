#ifndef GUARD_ofxBaseKeyframe
#define GUARD_ofxBaseKeyframe

/*
 *  ofxBaseKeyframe.h
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
 *  Created by Timothy Gfrerer on 19/10/2010.
 *  Copyright 2010 ponies & light. All rights reserved.
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
	TweenTransition tween_transition;        // the type of keyframe transition (TWEEN_SIN, etc.)
	
	virtual void execute()=0;  // this function needs to be set in all inheriting classes!
	virtual void start(){};
	virtual int getDuration()=0;

	bool hasStarted;

};




#endif
