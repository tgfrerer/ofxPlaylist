#ifndef GUARD_ofxKeyframe
#define GUARD_ofxKeyframe

/*
 *  ofxKeyframe.h
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
 *  Created by Timothy Gfrerer on 18/10/2010.
 *  Copyright 2010 ponies & light. All rights reserved.
 */

// TODO: Think about: you could make this into a threaded function - which would be the benefits?

#include "ofMain.h"

#include "ofxBaseKeyframe.h"
#include "ofxEasingExt.h"

class ofxKeyframe : public ofxBaseKeyframe {
public:
	
	ofxKeyframe(ofxEasing* _easingP, float * _pTweenTarget, const TweenTransition& _tween_transition, const float& _end, const int& _frames);
	ofxKeyframe(ofxEasing* _easingP, float * _pTweenTarget, const TweenTransition& _tween_transition, const float& _end, const float& _millisecs);

	ofxKeyframe(ofxEasing* _easingP, float * _pTweenTarget, const TweenTransition& _tween_transition, float * _start, const float& _end, const int& _frames);
	ofxKeyframe(ofxEasing* _easingP, float * _pTweenTarget, const TweenTransition& _tween_transition, float * _start, const float& _end, const float& _millisecs);

	// Pause
	explicit ofxKeyframe(const int& _frames);
	explicit ofxKeyframe(const float& _millisecs);

	~ofxKeyframe(){
		ofLog(OF_LOG_VERBOSE) << ofToString(ofGetFrameNum()) << ": ~ofxKeyframe();";
	};
	
	// bool value to give notice that the tween has finished.
	// bool is_idle;  
	void start();
	void execute();        // returns tweened value as a float
	
	// this variable decides which function is called every time the tween updates.
	// contains one of the above TWEEN_ constants.

	int getDuration(){return steps;};

private:
	bool isFrameBased;
	
	ofxEasing* easingP;
	
	void initofxKeyframe();
	void setup(float * _pTweenTarget, const TweenTransition& _tween_transition, float * _start, const float& _end, const int& _steps);
	
	// variables you need to save for every tween
	float * pTweenTarget;
	bool hasStarted;
	unsigned long startValue;
	float start_pos;
	float * start_pos_p;
	float end_pos;  
	int step;
	int steps; 
	
};







#endif