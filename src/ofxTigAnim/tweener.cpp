/*
 *  tweener.cpp
 *
 *  Created by Timothy Gfrerer on 18/10/2010.
 *  Copyright 2010. All rights reserved.
 *
 */

#include "tweener.h"




void Tweener::initTweener(){
	ofLog(OF_LOG_VERBOSE, "tweener created!");
	is_idle = FALSE;      // initialise zero Pointer
	pTweenTarget = NULL;
	hasStarted = FALSE;
	step = 0;
}

Tweener::Tweener(float * _pTweenTarget, const int& _tweener_function, float* _start, const float& _end, const int& _steps){
	initTweener();
	setup(_pTweenTarget, _tweener_function, _start, _end, _steps);
}



Tweener::~Tweener(){
	ofLog(OF_LOG_VERBOSE, "tweener destroyed.");
}

void Tweener::start(){
	ofLog(OF_LOG_VERBOSE, "tweener start");
	is_idle = FALSE;
	startTimeMillis = ofGetSystemTime();
	step = 0;
	hasStarted = TRUE;
	// get current Tween initialisation value by dereferencing the given start value pointer.
	start_pos = *start_pos_p;
}

void Tweener::setup(float * _pTweenTarget, const int& _tweener_function,  float* _start, const float& _end, const int& _steps){
	start_pos_p = _start;
	end_pos = _end;
	steps = _steps;
	startTimeMillis = 0;
	step = 0;
	pTweenTarget = _pTweenTarget;
	key_frame_type = _tweener_function;
}

void Tweener::execute(){
	// tim: DONE: have this function execute a static method (via pointer) with the appropriate easing function
	
	// check if tween_idle pointer has been properly initialized 
	if ((pTweenTarget != NULL) && (is_idle == FALSE)) {
		
		if (hasStarted == FALSE) start();
		
		// cout << "tw-execute: is_idle " << is_idle << endl;
		
		step = labs(ofGetSystemTime() - startTimeMillis);
		
		// cout << "tweening: "<< step << "/" << steps << endl;
		
		// bool * tween_idle is a pointer put out there by the caller function
		// in order to find out if the operation has completed.
		float _r = *pTweenTarget;
		
		switch (key_frame_type) {
			case TWEEN_LIN:
				_r = tween_lin(start_pos, end_pos, step, steps, &is_idle);
			case TWEEN_SIN:
				_r = tween_sin(start_pos, end_pos, step, steps, &is_idle);
				break;
			case TWEEN_QUAD_IN:
				_r = tween_quad_in(start_pos, end_pos, step, steps, &is_idle);
				break;
			case TWEEN_QUAD_OUT:
				_r = tween_quad_out(start_pos, end_pos, step, steps, &is_idle);
				break;
			case TWEEN_WAIT:
				tween_wait(start_pos, end_pos, step, steps, &is_idle);
				break;
			default:
				cout << "no tweener function specified!" << endl;
				break;
		}
		
		// *pTweenTarget = _r;
	}
};

