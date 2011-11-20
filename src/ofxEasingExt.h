#pragma once

#include "ofxEasing.h"

/*
 *  ofxEasingExt.h
 *  ofxKeyframeAnim
 *
 *	Wrapper to get static access to Robert Penner's tweening functions. 
 *
 *
 *  Created by Timothy Gfrerer on 17/03/2011.
 *  Copyright 2011 . All rights reserved.
 *
 */

class ofxEasingExt: public ofxEasing {
public:
	
	static float easeInS(ofxEasing* me, float t,float b , float c, float d){
		return me->easeIn(t,b,c,d);
	};
	
	static float easeOutS(ofxEasing* me, float t,float b , float c, float d){
		return me->easeOut(t,b,c,d);
	};
	
	static float easeInOutS(ofxEasing* me, float t,float b , float c, float d){
		return me->easeInOut(t,b,c,d);
	};
	
};