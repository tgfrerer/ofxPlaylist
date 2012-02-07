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
#include "ofxKeyframe.h"
#include "ofxEventKeyframe.h"
#include <deque>

// ----------------------------------------------------------------------

#include "ofxEasingBack.h"
#include "ofxEasingBounce.h"
#include "ofxEasingCirc.h"
#include "ofxEasingCubic.h"
#include "ofxEasingElastic.h"
#include "ofxEasingExpo.h"
#include "ofxEasingLinear.h"
#include "ofxEasingQuad.h"
#include "ofxEasingQuart.h"
#include "ofxEasingQuint.h"
#include "ofxEasingSine.h"

namespace Playlist{

	enum TweenType{
		TWEEN_BACK,
		TWEEN_BOUNCE,
		TWEEN_CIRC,
		TWEEN_CUBIC,
		TWEEN_ELASTIC,
		TWEEN_EXPO,
		TWEEN_LIN,
		TWEEN_QUAD,
		TWEEN_QUART,
		TWEEN_QUINT,
		TWEEN_SIN,
		TWEEN_BEZIER
	};

	extern ofxEasingBack	tweenBack;
	extern ofxEasingBounce  tweenBounce;
	extern ofxEasingCirc	tweenCirc;
	extern ofxEasingCubic	tweenCubic;
	extern ofxEasingElastic tweenElastic;
	extern ofxEasingExpo	tweenExpo;
	extern ofxEasingLinear  tweenLinear;
	extern ofxEasingQuad	tweenQuad;
	extern ofxEasingQuart	tweenQuart;
	extern ofxEasingQuint	tweenQuint;
	extern ofxEasingSine	tweenSine;

	namespace Action {
		
		 // MARK: - Static Factory functions

		template<class T>
		static ofPtr<ofxEventKeyframe> event(T * _listener, string _message)
		{
			return ofPtr<ofxEventKeyframe>(new ofxEventKeyframe(_listener, _message));
		};

		
		template <typename T>
		static ofPtr<ofxKeyframe> tween(const T& _duration, float* _pTweenTarget, const float& _targetValue, 
									const TweenType& tweenType = TWEEN_LIN, const TweenTransition& _tween_transition = TWEEN_EASE_IN_OUT, 
									float* _start = NULL)
		{
			ofxEasing* easingP;
			if (_start == NULL )				// if no special _start pointer is given, the initialisation value of _pTweenTarget is 
				_start = _pTweenTarget;			// taken to be _pTweenTarget at the moment the Tween gets executed the first time.
												// otherwise the value pointed to by _start is used as initialisation value for _pTweenTarget
												// the moment the Tween gets executed for the first time.
			
			switch (tweenType) {
				case TWEEN_BACK:
					easingP = &tweenBack;
					break;
				case TWEEN_BOUNCE:
					easingP = &tweenBounce;
					break;
				case TWEEN_CIRC: 
					easingP = &tweenCirc;
					break;
				case TWEEN_CUBIC:
					easingP = &tweenCubic;
					break;
				case TWEEN_ELASTIC:
					easingP = &tweenElastic;
					break;
				case TWEEN_EXPO:
					easingP = &tweenExpo;
					break;
				case TWEEN_LIN:
					easingP = &tweenLinear;
					break;
				case TWEEN_QUAD:
					easingP = &tweenQuad;
					break;
				case TWEEN_QUART:
					easingP = &tweenQuart;
					break;
				case TWEEN_QUINT:
					easingP = &tweenQuint;
					break;
				case TWEEN_SIN:
					easingP = &tweenSine;
					break;
				default:
					break;
			}
			
			return ofPtr<ofxKeyframe>(new ofxKeyframe(easingP, _pTweenTarget, _tween_transition, _start, _targetValue, _duration));
		};

		// ------- 
		// bezier curve based:
		
		template <typename T>
		static ofPtr<ofxKeyframe> tween(const T& _duration, float* _pTweenTarget, const float& _targetValue, 
										const ofPtr<BezierTween> _BezierTween, 
										float* _start = NULL)
		{
			ofxEasing* easingP = NULL;
			if (_start == NULL )				// if no special _start pointer is given, the initialisation value of _pTweenTarget is 
				_start = _pTweenTarget;			// taken to be _pTweenTarget at the moment the Tween gets executed the first time.
												// otherwise the value pointed to by _start is used as initialisation value for _pTweenTarget
												// the moment the Tween gets executed for the first time.
			
			return ofPtr<ofxKeyframe>(new ofxKeyframe(_BezierTween, _pTweenTarget, _start, _targetValue, _duration));
		};

		
		// ----------		
		// allows int or float, but does no checks for other, more exotic types, so be careful.
		template <typename T>
		static ofPtr<ofxKeyframe> pause(T pause)
		{
			return ofPtr<ofxKeyframe>(new ofxKeyframe(pause));
		};
		
	}
}

// ------------------------------------------------------------------------------------------------------------------------------------------
// MARK: - ofxPlaylist Object 

class ofxPlaylist {
public:
	typedef vector<ofPtr<ofxBaseKeyframe > > Keyframe;
	bool anim_idle;              // whether the current ofxPlaylist is animating
    int duration;
	
	ofxPlaylist()
	:anim_idle(TRUE)
	,duration(0)
	,lastDuration(0)
	,isAttached(FALSE)
	,bShouldClear(FALSE)
	{ 
#ifdef PLAYLIST_DEBUG_MODE
		ofLog(OF_LOG_VERBOSE) << "Instantiated new ofxPlaylist.";
#endif
	};
	
	~ofxPlaylist();
	
	void clear();
	void attach();
	void detach();

	void update(ofEventArgs& args){	update(); }

	// ********** UPDATER **********

	void update();  
	
	
	ofxPlaylist& addKeyFrame(ofPtr<ofxBaseKeyframe> _action);
	ofxPlaylist& addToKeyFrame(ofPtr<ofxBaseKeyframe> _action);
	
	void savePlaylistCurrentlyInBufferToInternalMap(string playlistName);
	void saveAndInitialiseTargetsAndClear(string playlistName);
	void replacePlaylistCurrentlyInBufferWithPlaylistFromInternalMap(string playlistName);

	
	// -----------------------------------------------------------------------------
	// MARK: Private methods
private:
	
	ofMutex playlistMutex;
	deque<ofPtr<Keyframe> > playlist;
	deque<ofPtr<Keyframe> > playlistBuffer;
	
	map<string, deque<ofPtr<Keyframe> > > savedPlaylists;
	
	int lastDuration;
	bool isAttached;
	bool bShouldClear;
		
	bool doNext();    
	void flush();
	
};


#endif