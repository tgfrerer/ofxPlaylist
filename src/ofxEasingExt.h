#pragma once

#include "ofxEasing.h"

/*    _____    ___     
 *   /    /   /  /     ofxPlaylist
 *  /  __/ * /  /__    (c) ponies & light, 2009-2012. 
 * /__/     /_____/    poniesandlight.co.uk
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
	//  easing*, step, start_pos , end_pos-start_pos, steps
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