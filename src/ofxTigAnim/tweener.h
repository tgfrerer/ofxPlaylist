#ifndef GUARD_TWEENER
#define GUARD_TWEENER

/*
 *  tweener.h
 *
 *  Created by Timothy Gfrerer on 18/10/2010.
 *  Copyright 2010. All rights reserved.
 *
 */

// TODO: Think about: you could make this into a threaded function - which would be the benefits?

#include "ofMain.h"
#include "tweener_functions.h"
#include "key_frame.h"

#define TWEEN_WAIT     0
#define TWEEN_SIN      1
#define TWEEN_QUAD_IN  3
#define TWEEN_QUAD_OUT 4
#define TWEEN_LIN      5

class Tweener : public Tweener_base, public KeyFrame{
public:
	
	Tweener(float * _pTweenTarget, const int& _tweener_function, float * _start, const float& _end, const int& _steps);
	
	~Tweener();
	
	// bool value to give notice that the tween has finished.
	// bool is_idle;  
	
	
	
	void start();
	void execute();        // returns tweened value as a float
	
	// this variable decides which function is called every time the tween updates.
	// contains one of the above TWEEN_ constants.
	
private:
	
	void initTweener();
	void setup(float * _pTweenTarget, const int& _tweener_function, float * _start, const float& _end, const int& _steps);
	
	// variables you need to save for every tween
	float * pTweenTarget;
	bool hasStarted;
	unsigned long startTimeMillis;
	float start_pos;
	float * start_pos_p;
	float end_pos;  
	int steps; 
	int step;
	
};






#endif