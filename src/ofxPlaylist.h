#ifndef GUARD_OFXPLAYLIST
#define GUARD_OFXPLAYLIST
/*
 *  ofxPlaylist.h
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


// ----------------------------------------------------------------------
// usage: 
/* 
 using namespace Playlist;
 playlist.addKeyFrame(Action::tween(1000.f, &pos.x, 0., TWEEN_SIN, TWEEN_EASE_OUT, &pos.x));
 playlist.addKeyFrame(Action::pause(500.f));
 playlist.addKeyFrame(Action::event(this, "EVENT MESSAGE"));
 
 */
// ----------------------------------------------------------------------


#include "ofMain.h"
#include "tweener.h"
#include "ofxEventKeyframe.h"
#include <deque>

// ----------------------------------------------------------------------

#include "ofxEasingLinear.h"
#include "ofxEasingSine.h"
#include "ofxEasingQuad.h"

enum TweenType{
	TWEEN_LIN,
	TWEEN_QUAD,
	TWEEN_SIN
};

 

namespace Playlist{

	extern ofxEasingLinear tweenLinear;
	extern ofxEasingSine tweenSine;
	extern ofxEasingQuad tweenQuad;

	namespace Action {
		
		/* 
		 // MARK: - Static Factory functions
		 Factory functions. these allow you 
		 
		 */
		template<class T>
		static ofPtr<ofxEventKeyframe> event(T * _listener, string _message)
		{
			return ofPtr<ofxEventKeyframe>(new ofxEventKeyframe(_listener, _message));
		};

		
		template <typename T>
		static ofPtr<Tweener> tween(const T& _duration, float* _pTweenTarget, const float& _targetValue, 
									const TweenType& tweenType = TWEEN_LIN, const TweenTransition& _tween_transition = TWEEN_EASE_IN_OUT, 
									float* _start = NULL)
		{
			ofxEasing* easingP;
			if (_start == NULL )				// if no special _start pointer is given, the initialisation value of _pTweenTarget is 
				_start = _pTweenTarget;			// taken to be _pTweenTarget at the moment the Tween gets executed the first time.
												// otherwise the value pointed to by _start is used as initialisation value for _pTweenTarget
												// the moment the Tween gets executed the first time.
			
			switch (tweenType) {
				case TWEEN_LIN:
					easingP = &tweenLinear;
					break;
				case TWEEN_SIN:
					easingP = &tweenSine;
					break;
				case TWEEN_QUAD:
					easingP = &tweenQuad;
					break;
				default:
					break;
			}
			
			return ofPtr<Tweener>(new Tweener(easingP, _pTweenTarget, _tween_transition, _start, _targetValue, _duration));
		};
		
		// ----------		
		// allows int or float
		template <typename T>
		static ofPtr<Tweener> pause(T pause)
		{
			return ofPtr<Tweener>(new Tweener(pause));
		};
		
	}
}

// ------------------------------------------------------------------------------------------------------------------------------------------
// MARK: - ofxPlaylist Object 

class ofxPlaylist {
public:
	typedef vector<ofPtr<ofxPlaylistAction > > Keyframe;
	bool anim_idle;              // whether the current ofxPlaylist is animating
    int duration;
	
	ofxPlaylist()
	:anim_idle(TRUE)
	,duration(0)
	,lastDuration(0)
	,isAttached(FALSE)
	,bShouldClear(FALSE)
	{ 
		ofLog(OF_LOG_VERBOSE) << "Instantiated new ofxPlaylist.";
	};
	
	~ofxPlaylist(){
		ofLog(OF_LOG_VERBOSE) << "~ofxPlaylist";
		detach();
		bShouldClear = true;
		if (playlistMutex.tryLock(50)){			// allow for a grace period of 50ms
												// before clearing, just in case
												// the object gets destroyed while the mutex is under lock.
			clear();
		}
		playlistMutex.unlock();					// unlock the mutex regardless of what happens.
	};
	
	void clear();
	void attach();
	void detach();

	void update(ofEventArgs& args){	update(); }

	// ********** UPDATER **********

	void update();  
	
	
	ofxPlaylist* addKeyFrame(ofPtr<ofxPlaylistAction> _action);
	ofxPlaylist* addToKeyFrame(ofPtr<ofxPlaylistAction> _action);
	


	
	// -----------------------------------------------------------------------------
	// MARK: Private methods
private:
	ofMutex playlistMutex;
	deque<ofPtr<Keyframe> > playlist;
	deque<ofPtr<Keyframe> > playlistBuffer;
	
	int lastDuration;
	bool isAttached;
	bool bShouldClear;
		
	bool doNext();    
	void flush();
	
};


#endif