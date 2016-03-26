/*    _____    ___     
 *   /    /   /  /     ofxPlaylist
 *  /  __/ * /  /__    (c) ponies & light, 2009-2012. 
 * /__/     /_____/    poniesandlight.co.uk
 * 
 * ofxKeyframe.cpp
 * Created by Timothy Gfrerer on 18/10/2010.
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

#include "ofxKeyframe.h"
#include "ofxEasingExt.h"

// ----------------------------------------------------------------------
void ofxKeyframe::initofxKeyframe(){
#ifdef PLAYLIST_DEBUG_MODE
	ofLog(OF_LOG_VERBOSE) << ofToString(ofGetFrameNum()) << ": new ofxKeyframe();";
#endif
	is_idle = FALSE;     
	pTweenTarget = NULL;
	hasStarted = FALSE;
	isBezierCurveBased = FALSE;
	step = 0;
	isDelayed = FALSE;
}

// ----------------------------------------------------------------------
// bezier curve based
// by-frame:
ofxKeyframe::ofxKeyframe(shared_ptr<Playlist::BezierTween> _easingC, float * _pTweenTarget, const float& _end, const int& _frames, const int& _frames_delay){
	easingP = NULL;
	pEasingC = _easingC;
	initofxKeyframe();
	setup(_pTweenTarget, TWEEN_EASE_IN_OUT, _pTweenTarget, _end, _frames, _frames_delay);
	isFrameBased = TRUE;
	isBezierCurveBased = TRUE;
}

// ----------------------------------------------------------------------
// by-time:
ofxKeyframe::ofxKeyframe(shared_ptr<Playlist::BezierTween> _easingC, float * _pTweenTarget, const float& _end, const float& _millisecs, const float& _millisecs_delay){
	easingP = NULL;
	pEasingC = _easingC;
	initofxKeyframe();
	setup(_pTweenTarget, TWEEN_EASE_IN_OUT, _pTweenTarget, _end, _millisecs, _millisecs_delay);
	isFrameBased = FALSE;
	isBezierCurveBased = TRUE;
}

// ----------------------------------------------------------------------
// by-frame:
ofxKeyframe::ofxKeyframe(shared_ptr<Playlist::BezierTween> _easingC, float * _pTweenTarget, float* _start, const float& _end, const int& _frames, const int& _frames_delay){
	easingP = NULL;
	pEasingC = _easingC;
	initofxKeyframe();
	setup(_pTweenTarget, TWEEN_EASE_IN_OUT, _start, _end, _frames, _frames_delay);
	isFrameBased = TRUE;
	isBezierCurveBased = TRUE;
}

// ----------------------------------------------------------------------
// by-time:
ofxKeyframe::ofxKeyframe(shared_ptr<Playlist::BezierTween> _easingC, float * _pTweenTarget, float* _start, const float& _end, const float& _millisecs, const float& _millisecs_delay){
	easingP = NULL;
	pEasingC = _easingC;
	initofxKeyframe();
	setup(_pTweenTarget, TWEEN_EASE_IN_OUT, _start, _end, _millisecs, _millisecs_delay);
	isFrameBased = FALSE;
	isBezierCurveBased = TRUE;
}

// ----------------------------------------------------------------------
// easing function based
// frame-based
ofxKeyframe::ofxKeyframe(ofxEasing* _easingP, float * _pTweenTarget, const TweenTransition& _tween_transition, float* _start, const float& _end, const int& _frames, const int& _frames_delay){
	easingP = _easingP;
	initofxKeyframe();
	setup(_pTweenTarget, _tween_transition, _start, _end, _frames, _frames_delay);
	isFrameBased = true;
}

// ----------------------------------------------------------------------
//time-based (ms)
ofxKeyframe::ofxKeyframe(ofxEasing* _easingP, float * _pTweenTarget, const TweenTransition& _tween_transition, float* _start, const float& _end, const float& _millisecs, const float& _millisecs_delay){
	easingP = _easingP;
	initofxKeyframe();
	setup(_pTweenTarget, _tween_transition, _start, _end, _millisecs, _millisecs_delay);
	isFrameBased = false;
}

// ----------------------------------------------------------------------
// frame-based
ofxKeyframe::ofxKeyframe(ofxEasing* _easingP, float * _pTweenTarget, const TweenTransition& _tween_transition, const float& _end, const int& _frames, const int& _frames_delay){
	easingP = _easingP;
	initofxKeyframe();
	setup(_pTweenTarget, _tween_transition, _pTweenTarget, _end, _frames, _frames_delay);
	isFrameBased = true;
}

// ----------------------------------------------------------------------
//time-based (ms)
ofxKeyframe::ofxKeyframe(ofxEasing* _easingP, float * _pTweenTarget, const TweenTransition& _tween_transition, const float& _end, const float& _millisecs, const float& _millisecs_delay){
	easingP = _easingP;
	initofxKeyframe();
	setup(_pTweenTarget, _tween_transition, _pTweenTarget, _end, _millisecs, _millisecs_delay);
	isFrameBased = false;
}


// ----------------------------------------------------------------------
// this only for TWEEN_PAUSE
// frame-based
ofxKeyframe::ofxKeyframe(const int& _frames){
	easingP = NULL;
	initofxKeyframe();
	setup(NULL, TWEEN_PAUSE, NULL, 0, _frames, 0);
	isFrameBased = true;
}

// ----------------------------------------------------------------------
//time-based (ms)
ofxKeyframe::ofxKeyframe(const float& _millisecs){
	easingP = NULL;
	initofxKeyframe();
	setup(NULL, TWEEN_PAUSE, NULL, 0, _millisecs, 0);
	isFrameBased = false;
}

// ----------------------------------------------------------------------

void ofxKeyframe::start(){
#ifdef PLAYLIST_DEBUG_MODE
	ofLog(OF_LOG_VERBOSE) << ofToString(ofGetFrameNum()) << ": ofxKeyframe start";
#endif
	is_idle = FALSE;
	(isFrameBased) ? startValue = 0 : startValue = ofGetSystemTime();
	step = 0;
	hasStarted = TRUE;
	isDelayed = TRUE;
}

// ----------------------------------------------------------------------

void ofxKeyframe::fetchTargets(){
	// cout << "   fetching targets: "<< step << "/" << steps << "+" << delay_steps << endl;

	// get current animatedObject's start value by dereferencing the given start value pointer.
	if (start_pos_p != NULL)	// is NULL in case TWEEN_PAUSE
		start_pos = *start_pos_p;
	
	if (isBezierCurveBased){
		// initalise the bezier curve...
		pEasingC->setIn(*start_pos_p);
		pEasingC->setOut(end_pos);
		
		if (!isFrameBased)
			pEasingC->setup(steps);
		else pEasingC->setup((steps / (float)ofGetFrameRate())*1000); 
	}
}

// ----------------------------------------------------------------------

void ofxKeyframe::setup(float * _pTweenTarget, const TweenTransition& _tween_transition,  float* _start, const float& _end, const int& _steps, const int& _delay_steps)
{
	start_pos_p = _start;
	end_pos = _end;
	delay_steps = _delay_steps;
	steps = _steps;
	startValue = 0;
	step = 0;
	pTweenTarget = _pTweenTarget;
	tween_transition = _tween_transition;
	isDelayed = true;
	
};

// ----------------------------------------------------------------------

bool ofxKeyframe::delayHasEnded(){
	if (isDelayed && (step >= delay_steps)) {
		isDelayed = false;
		return true;
	}
	return false;
}

// ----------------------------------------------------------------------

void ofxKeyframe::execute(){
	if (((pTweenTarget != NULL) && (is_idle == FALSE)) || (tween_transition==TWEEN_PAUSE)) {
		
		if (hasStarted == FALSE) start();
		
		// cout << "tw-execute: is_idle " << is_idle << endl;
		
		step = isFrameBased ? startValue : (ofGetSystemTime() - startValue);
		if (isFrameBased) startValue++;		// increase frame count if the animation is by-frame
		
		// cout << "tweening: "<< step << "/" << steps << "+" << delay_steps << endl;

		if (delayHasEnded()) fetchTargets();	// will only return TRUE the first time.
		
		if (isDelayed) return;
		// ----------| invariant: delay has ended, we are ready to execute:
		
		float _r;
		
		if (tween_transition != TWEEN_PAUSE )
			_r = *pTweenTarget;
		
		if (!is_idle && (step < (steps + delay_steps))){
			_r = 0.0;

			if (isBezierCurveBased)
				_r = pEasingC->getAt((step - delay_steps)/(float)(steps));
			else
			switch (tween_transition) {
				case TWEEN_EASE_IN:
					_r = ofxEasingExt::easeInS( easingP, (step - delay_steps), start_pos , end_pos-start_pos, steps );
					break;
				case TWEEN_EASE_OUT: 
					 _r = ofxEasingExt::easeOutS( easingP, (step - delay_steps), start_pos , end_pos-start_pos, steps);
					break;
				case TWEEN_EASE_IN_OUT:
					_r = ofxEasingExt::easeInOutS( easingP, (step - delay_steps), start_pos , end_pos-start_pos, steps);
					break;
				case TWEEN_PAUSE:
					break;
				default:
					ofLog(OF_LOG_WARNING) << "no easing function specified!";
					break;
			}
			if (step == (delay_steps + steps) ){
				is_idle = TRUE;
				if (tween_transition != TWEEN_PAUSE)
					_r= end_pos;
			}
			
		} else {
			if (step >= (delay_steps + steps) ){
				is_idle = TRUE;
				if (tween_transition != TWEEN_PAUSE)
					_r= end_pos;
			}
		}
		if (tween_transition != TWEEN_PAUSE )
			*pTweenTarget = _r;
	}
};