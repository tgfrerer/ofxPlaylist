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


namespace Playlist {
	class BezierTween {
		// this describes a cubic bezier curve, 
		// we assume a normalised x coordinate (p2.x - p1.x == 1.f, p1.x == 0)

		ofVec2f p1;
		ofVec2f pc1;
		ofVec2f pc2;
		ofVec2f p2;
		
		float inSpeed;
		float outSpeed;
		
		
	public:

		// default constructor
		BezierTween()
		:p1(0,0)
		,pc1(0,0)
		,pc2(0,0)
		,p2(1,0)
		,inSpeed(0.f)
		,outSpeed(0.f){}
		
		float getAt(float t){
			return ofBezierPoint(p1, pc1, pc2, p2, t).y;
		};
		
		
		void setIn(const float& _value){p1.set(0,_value);}
		void setOut(const float& _value){p2.set(1,_value);}
		
		ofVec2f getIn(){return p1;}
		ofVec2f getOut(){return p2;}
		
		// getter and setter methods.
		// speed is given in pixels / sec. which means, we need to normalise this if the total lenght is not one sec.
		
		void setInSpeed(const float& speed){
			inSpeed = speed;
		}

		void setOutSpeed(const float& speed){
			outSpeed = speed;
		}
		
		float getInSpeed(){return pc1.y;}
		float getOutSpeed(){return pc2.y;}
		
		void setInInfluence(const float& influence){pc1.x=influence;}
		void setOutInfluence(const float& influence){pc2.x=1.f-influence;}
		
		float getInInfluence(){return pc1.x;}
		float getOutInfluence(){return 1.f-pc2.x;}
		
		
		
		void setup(const float& duration){
			// calculates correct values for in and outspeed.
			// duration is given in millisecs.
			// in after effects, the speed is given as units per second
			// so we:
			
			// 1. find out where y value would be after one second
			// 3. see where the value would on (influence percent) down the x-axis
			
			float scaledInSpeed = (inSpeed * duration * getInInfluence()) / 1000.f;
			float scaledOutSpeed = (outSpeed * duration * getOutInfluence()) /1000.f;
			
			// speed values are relative, which is why we add the current in/out y-values to the
			// relative speed value to calculate the bezier curve tangent handles.



			(p1.y > 0 ) ? pc1.y = p1.y + scaledInSpeed : pc1.y = p1.y - scaledInSpeed;
			(p2.y > 0 ) ? pc2.y = p2.y-scaledOutSpeed : pc2.y = p2.y + scaledOutSpeed;
		}

	};
}


class ofxKeyframe : public ofxBaseKeyframe {
	
public:
	
	ofxKeyframe(ofxEasing* _easingP, float * _pTweenTarget, const TweenTransition& _tween_transition, const float& _end, const int& _frames, const int& _frames_delay=0);
	ofxKeyframe(ofxEasing* _easingP, float * _pTweenTarget, const TweenTransition& _tween_transition, const float& _end, const float& _millisecs, const float& _millisecs_delay=0);

	ofxKeyframe(ofxEasing* _easingP, float * _pTweenTarget, const TweenTransition& _tween_transition, float * _start, const float& _end, const int& _frames, const int& _frames_delay=0);
	ofxKeyframe(ofxEasing* _easingP, float * _pTweenTarget, const TweenTransition& _tween_transition, float * _start, const float& _end, const float& _millisecs, const float& _millisecs_delay=0);

	// bezier curve
	
	ofxKeyframe(ofPtr<Playlist::BezierTween> _easingC, float * _pTweenTarget, const float& _end, const int& _frames, const int& _frames_delay=0);
	ofxKeyframe(ofPtr<Playlist::BezierTween> _easingC, float * _pTweenTarget, const float& _end, const float& _millisecs, const float& _millisecs_delay=0);

	ofxKeyframe(ofPtr<Playlist::BezierTween> _easingC, float * _pTweenTarget, float * _start, const float& _end, const int& _frames, const int& _frames_delay=0);
	ofxKeyframe(ofPtr<Playlist::BezierTween> _easingC, float * _pTweenTarget, float * _start, const float& _end, const float& _millisecs, const float& _millisecs_delay=0);
	
	
	// Pause
	explicit ofxKeyframe(const int& _frames);
	explicit ofxKeyframe(const float& _millisecs);

	~ofxKeyframe(){
#ifdef PLAYLIST_DEBUG_MODE
		ofLog(OF_LOG_VERBOSE) << ofToString(ofGetFrameNum()) << ": ~ofxKeyframe();";
#endif
	};
	
	// bool value to give notice that the tween has finished.
	// bool is_idle;  
	void start();
	void execute();        // returns tweened value as a float
	
	// this variable decides which function is called every time the tween updates.
	// contains one of the above TWEEN_ constants.

	int getDuration(){return steps;};

private:
	
	ofxKeyframe(){};	// just to make sure no-one calls this implicitly.
	
	bool isFrameBased;
	bool isBezierCurveBased;
	bool isDelayed;
	
	ofxEasing* easingP;
	ofPtr<Playlist::BezierTween> pEasingC;
	
	void initofxKeyframe();
	void setup(float * _pTweenTarget, const TweenTransition& _tween_transition, float * _start, const float& _end, const int& _steps, const int& _delay_steps);
	
	void fetchTargets();
	bool delayHasEnded();
	
	// variables you need to save for every tween
	float * pTweenTarget;
	unsigned long startValue;
	float start_pos;
	float * start_pos_p;
	float end_pos;  
	int step;
	int steps;
	int delay_steps;
	
};





#endif