#ifndef GUARD_OFXPLAYLIST
#define GUARD_OFXPLAYLIST

/*    _____    ___     
 *   /    /   /  /     ofxPlaylist
 *  /  __/ * /  /__    (c) ponies & light, 2009-2012. 
 * /__/     /_____/    poniesandlight.co.uk
 * 
 * ofxPlaylist.h
 * Created by Timothy Gfrerer on 19/10/2010.
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

// ----------------------------------------------------------------------
// basic usage: 
/* 
 using namespace Playlist;
 float tweenTarget;
 
 playlist.addKeyFrame(Action::tween(1000.f, &tweenTarget, 100.));
 playlist.addKeyFrame(Action::pause(500.f));
 playlist.addKeyFrame(Action::event(this, "EVENT MESSAGE"));
 
 */
// ----------------------------------------------------------------------


#include "ofMain.h"
#include "ofxKeyframe.h"
#include "ofxEventKeyframe.h"
#include <deque>

// ----------------------------------------------------------------------

#include "Easings/ofxEasingBack.h"
#include "Easings/ofxEasingBounce.h"
#include "Easings/ofxEasingCirc.h"
#include "Easings/ofxEasingCubic.h"
#include "Easings/ofxEasingElastic.h"
#include "Easings/ofxEasingExpo.h"
#include "Easings/ofxEasingLinear.h"
#include "Easings/ofxEasingQuad.h"
#include "Easings/ofxEasingQuart.h"
#include "Easings/ofxEasingQuint.h"
#include "Easings/ofxEasingSine.h"

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
		static shared_ptr<ofxEventKeyframe> event(T * _listener, string _message)
		{
			return shared_ptr<ofxEventKeyframe>(new ofxEventKeyframe(_listener, _message));
		};

		template<class T>
		static shared_ptr<ofxEventKeyframe> event(int frameDelay_, T * _listener, string _message)
		{
			return shared_ptr<ofxEventKeyframe>(new ofxEventKeyframe(frameDelay_, _listener, _message));
		};
	
		template<class T>
		static shared_ptr<ofxEventKeyframe> event(float millisecDelay_, T * _listener, string _message)
		{
			return shared_ptr<ofxEventKeyframe>(new ofxEventKeyframe(millisecDelay_, _listener, _message));
		};

		
		template <typename T>
		static shared_ptr<ofxKeyframe> tween(const T& _duration, float* _pTweenTarget, const float& _targetValue, 
									const TweenType& tweenType = TWEEN_LIN, const TweenTransition& _tween_transition = TWEEN_EASE_IN_OUT, 
									float* _start = NULL, const T& _delay_duration=0)
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
			
			return shared_ptr<ofxKeyframe>(new ofxKeyframe(easingP, _pTweenTarget, _tween_transition, _start, _targetValue, _duration, _delay_duration));
		};

		// this allows you to specify a delay before the tween duration in a more friendly notation
		template <typename T>
		static shared_ptr<ofxKeyframe> tween(const T& _delay_duration, const T& _duration, float* _pTweenTarget, const float& _targetValue, 
										const TweenType& tweenType = TWEEN_LIN, const TweenTransition& _tween_transition = TWEEN_EASE_IN_OUT, 
										float* _start = NULL)
		{
			return tween(_duration, _pTweenTarget, _targetValue, tweenType, _tween_transition, _start, _delay_duration);
		}
		
		// ------- 
		// bezier curve based:
		
		template <typename T>
		static shared_ptr<ofxKeyframe> tween(const T& _duration, float* _pTweenTarget, const float& _targetValue, 
										const shared_ptr<BezierTween> _BezierTween, 
										float* _start = NULL, const T& _delay_duration=0)
		{
			ofxEasing* easingP = NULL;
			if (_start == NULL )				// if no special _start pointer is given, the initialisation value of _pTweenTarget is 
				_start = _pTweenTarget;			// taken to be _pTweenTarget at the moment the Tween gets executed the first time.
												// otherwise the value pointed to by _start is used as initialisation value for _pTweenTarget
												// the moment the Tween gets executed for the first time.
			
			return shared_ptr<ofxKeyframe>(new ofxKeyframe(_BezierTween, _pTweenTarget, _start, _targetValue, _duration, _delay_duration));
		};

		// this allows you to specify a delay before the tween duration in a more friendly notation
		template <typename T>
		static shared_ptr<ofxKeyframe> tween(const T& _delay_duration, const T& _duration, float* _pTweenTarget, const float& _targetValue, 
										const shared_ptr<BezierTween> _BezierTween, 
										float* _start = NULL)
		{
			return tween(_duration, _pTweenTarget, _targetValue, _BezierTween, _start, _delay_duration);
		};

		
		// ----------		
		// allows int or float, but does no checks for other, more exotic types, so be careful.
		template <typename T>
		static shared_ptr<ofxKeyframe> pause(T pause)
		{
			return shared_ptr<ofxKeyframe>(new ofxKeyframe(pause));
		};
		
	}
}

// ------------------------------------------------------------------------------------------------------------------------------------------
// MARK: - ofxPlaylist Object 

class ofxPlaylist {
public:
	typedef vector<shared_ptr<ofxBaseKeyframe > > Keyframe;
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
	
	
	ofxPlaylist& addKeyFrame(shared_ptr<ofxBaseKeyframe> _action);
	ofxPlaylist& addToKeyFrame(shared_ptr<ofxBaseKeyframe> _action);
	
	void savePlaylistCurrentlyInBufferToInternalMap(string playlistName);
	void saveAndInitialiseTargetsAndClear(string playlistName);
	void replacePlaylistCurrentlyInBufferWithPlaylistFromInternalMap(string playlistName);

	
	// -----------------------------------------------------------------------------
	// MARK: Private methods
private:
	
	ofMutex playlistMutex;
	deque<shared_ptr<Keyframe> > playlist;
	deque<shared_ptr<Keyframe> > playlistBuffer;
	
	map<string, deque<shared_ptr<Keyframe> > > savedPlaylists;
	
	int lastDuration;
	bool isAttached;
	bool bShouldClear;
		
	bool doNext();    
	void flush();
	
};


#endif
