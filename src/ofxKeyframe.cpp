/*
 *  ofxKeyframe.cpp
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

#include "ofxKeyframe.h"
#include "ofxEasingExt.h"

void ofxKeyframe::initofxKeyframe(){
	ofLog(OF_LOG_VERBOSE) << ofToString(ofGetFrameNum()) << ": new ofxKeyframe();";
	is_idle = FALSE;     
	pTweenTarget = NULL;
	hasStarted = FALSE;
	step = 0;
}

// frame-based
ofxKeyframe::ofxKeyframe(ofxEasing* _easingP, float * _pTweenTarget, const TweenTransition& _tween_transition, float* _start, const float& _end, const int& _frames){
	easingP = _easingP;
	initofxKeyframe();
	setup(_pTweenTarget, _tween_transition, _start, _end, _frames);
	isFrameBased = true;
}

//time-based (ms)
ofxKeyframe::ofxKeyframe(ofxEasing* _easingP, float * _pTweenTarget, const TweenTransition& _tween_transition, float* _start, const float& _end, const float& _millisecs){
	easingP = _easingP;
	initofxKeyframe();
	setup(_pTweenTarget, _tween_transition, _start, _end, _millisecs);
	isFrameBased = false;
}

// frame-based
ofxKeyframe::ofxKeyframe(ofxEasing* _easingP, float * _pTweenTarget, const TweenTransition& _tween_transition, const float& _end, const int& _frames){
	easingP = _easingP;
	initofxKeyframe();
	setup(_pTweenTarget, _tween_transition, _pTweenTarget, _end, _frames);
	isFrameBased = true;
}

//time-based (ms)
ofxKeyframe::ofxKeyframe(ofxEasing* _easingP, float * _pTweenTarget, const TweenTransition& _tween_transition, const float& _end, const float& _millisecs){
	easingP = _easingP;
	initofxKeyframe();
	setup(_pTweenTarget, _tween_transition, _pTweenTarget, _end, _millisecs);
	isFrameBased = false;
}


// this only for TWEEN_PAUSE
// frame-based
ofxKeyframe::ofxKeyframe(const int& _frames){
	easingP = NULL;
	initofxKeyframe();
	setup(NULL, TWEEN_PAUSE, NULL, 0, _frames);
	isFrameBased = true;
}
//time-based (ms)
ofxKeyframe::ofxKeyframe(const float& _millisecs){
	easingP = NULL;
	initofxKeyframe();
	setup(NULL, TWEEN_PAUSE, NULL, 0, _millisecs);
	isFrameBased = false;
}



void ofxKeyframe::start(){
	ofLog(OF_LOG_VERBOSE) << ofToString(ofGetFrameNum()) << ": ofxKeyframe start";
	is_idle = FALSE;
	(isFrameBased) ? startValue = 0 : startValue = ofGetSystemTime();
	step = 0;
	hasStarted = TRUE;
	// get current animatedObject's start value by dereferencing the given start value pointer.
	if (start_pos_p != NULL)	// is NULL in case TWEEN_PAUSE
		start_pos = *start_pos_p;
}

void ofxKeyframe::setup(float * _pTweenTarget, const TweenTransition& _tween_transition,  float* _start, const float& _end, const int& _steps)
{
	start_pos_p = _start;
	end_pos = _end;
	steps = _steps;
	startValue = 0;
	step = 0;
	pTweenTarget = _pTweenTarget;
	tween_transition = _tween_transition;
};

void ofxKeyframe::execute(){
	if (((pTweenTarget != NULL) && (is_idle == FALSE)) || (tween_transition==TWEEN_PAUSE)) {
		
		if (hasStarted == FALSE) start();
		
		// cout << "tw-execute: is_idle " << is_idle << endl;
		
		step = isFrameBased ? labs(startValue) : labs(ofGetSystemTime() - startValue);
		if (isFrameBased) startValue++;		// increase frame count if the animation is by-frame
		
		// cout << "tweening: "<< step << "/" << steps << endl;
		
		float _r;
		
		if (tween_transition != TWEEN_PAUSE)
			_r = *pTweenTarget;
		
		if (!is_idle && step<=steps){
			_r = 0.0;
			
			switch (tween_transition) {
				case TWEEN_EASE_IN:
					_r = ofxEasingExt::easeInS( easingP, step, start_pos , end_pos-start_pos, steps);
				case TWEEN_EASE_OUT:
					_r = ofxEasingExt::easeOutS( easingP, step, start_pos , end_pos-start_pos, steps);
					break;
				case TWEEN_EASE_IN_OUT:
					_r = ofxEasingExt::easeInOutS( easingP, step, start_pos , end_pos-start_pos, steps);
					break;
				case TWEEN_PAUSE:
					break;
				default:
					ofLog(OF_LOG_WARNING) << "no easing function specified!";
					break;
			}
			if (step == steps){
				is_idle = TRUE;
				if (tween_transition != TWEEN_PAUSE)
					_r= end_pos;
			}
			
		} else {
			if (step > steps){
				is_idle = TRUE;
				if (tween_transition != TWEEN_PAUSE)
					_r= end_pos;
			}
		}
		if (tween_transition != TWEEN_PAUSE)
			*pTweenTarget = _r;
	}
};