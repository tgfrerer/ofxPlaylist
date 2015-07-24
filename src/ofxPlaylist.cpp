/*    _____    ___     
 *   /    /   /  /     ofxPlaylist
 *  /  __/ * /  /__    (c) ponies & light, 2009-2012. 
 * /__/     /_____/    poniesandlight.co.uk
 * 
 * ofxPlaylist.cpp
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


#include "ofxPlaylist.h"

 ofxEasingBack		Playlist::tweenBack;				// 	declare global tween objects for ofxKeyframes
 ofxEasingBounce	Playlist::tweenBounce;
 ofxEasingCirc		Playlist::tweenCirc;
 ofxEasingCubic		Playlist::tweenCubic;
 ofxEasingElastic	Playlist::tweenElastic;
 ofxEasingExpo		Playlist::tweenExpo;
 ofxEasingLinear	Playlist::tweenLinear;
 ofxEasingQuad		Playlist::tweenQuad;
 ofxEasingQuart		Playlist::tweenQuart;
 ofxEasingQuint		Playlist::tweenQuint;
 ofxEasingSine		Playlist::tweenSine;


// ----------------------------------------------------------------------


ofxPlaylist& ofxPlaylist::addKeyFrame(shared_ptr<ofxBaseKeyframe> _action){
	// tim-debug: this function was leaking memory like a whole geriatric ward!
	// no more. shared_ptr to the rescue.

	lastDuration = _action->getDuration();
	duration += lastDuration;

	playlistBuffer.push_back(shared_ptr<Keyframe> (new Keyframe()));

	// add keyframe to the playlistBuffer
	playlistBuffer.back()->push_back(_action);

	anim_idle = FALSE;
	return *this;
}

// ----------------------------------------------------------------------

ofxPlaylist& ofxPlaylist::addToKeyFrame(shared_ptr<ofxBaseKeyframe> _action){
	// get the last element of the queue

	if (playlistBuffer.empty()){
		// if there is no previous keyframe to attach to, add a new keyframe.
		return addKeyFrame(_action);
	}
	
	if (_action->getDuration() > lastDuration) {
		duration -= lastDuration;	// take away the smaller value from the total
		lastDuration = _action->getDuration();
		duration += lastDuration;  // and exchange it for the larger value
	}

	//  add ofxKeyFrame to the list.
	playlistBuffer.back()->push_back(_action);
	anim_idle = FALSE;
	return *this;
}

// ----------------------------------------------------------------------

void ofxPlaylist::update(){

	if (playlistMutex.try_lock()){
		playlistMutex.unlock();
	} else {
		ofLog(OF_LOG_FATAL_ERROR) << "Did you just try to update a playlist from within an event?. Recursive updates, or what? That's forbidden.";
		ofExit();
	}

	if (bShouldClear == true) {
		bShouldClear = false;
#ifdef PLAYLIST_DEBUG_MODE
		ofLog(OF_LOG_VERBOSE) << "Did catch soft-clear at the start.";
#endif
		clear();
		return;
	}

	playlistMutex.lock();

	flush();

	if (!playlist.empty()){
		if (anim_idle == TRUE){
			anim_idle = doNext();
		} else {
			// do some animation here!

			Keyframe currentKeyframe = *(playlist.front());
			int _boolCount = 0;

			for (int i=0; i<currentKeyframe.size(); i++){
				currentKeyframe[i]->execute();
				if (currentKeyframe[i]->is_idle) _boolCount++;
			}

			if (_boolCount == currentKeyframe.size()) {
				// all the tweens report true, so all the work is done for this frame
				anim_idle = TRUE;
				// check if there are more frames to do work on...
				do {
					anim_idle = doNext();
				} while (anim_idle==TRUE);
			} else {
				// there's still some more stuff to do.
				anim_idle = FALSE;
			}

			if (duration > 0)
				duration--;

		}
	}

	playlistMutex.unlock();

	if (bShouldClear == true) {
		bShouldClear = false;
#ifdef PLAYLIST_DEBUG_MODE
		ofLog(OF_LOG_VERBOSE) << "Did catch soft-clear at the end.";
#endif
		clear();
		return;
	}


};

// ----------------------------------------------------------------------

void ofxPlaylist::clear(){
	if(playlistMutex.try_lock()){
#ifdef PLAYLIST_DEBUG_MODE
		ofLog(OF_LOG_VERBOSE) << "Clearing ofxPlaylist.playlist";
#endif
		playlist.clear(); 					// aah...... the beauty of shared_ptr<>
		bShouldClear = false;
		playlistMutex.unlock();
	} else {
#ifdef PLAYLIST_DEBUG_MODE
		ofLog(OF_LOG_VERBOSE) << "playlist cannot be cleared currently. Activating soft-clear.";
#endif
		bShouldClear = true;
	}
};

// ----------------------------------------------------------------------
// MARK: - event based update helpers

void ofxPlaylist::attach(){
	if (!isAttached) {
		ofAddListener(ofEvents().update, this, &ofxPlaylist::update);
		isAttached = TRUE;
	}
}

// ----------------------------------------------------------------------

void ofxPlaylist::detach(){
	if (isAttached) {
		ofRemoveListener(ofEvents().update, this, &ofxPlaylist::update);
		isAttached = FALSE;
	}

}

// ----------------------------------------------------------------------
// MARK: - private methods

bool ofxPlaylist::doNext(){
	bool _r = TRUE;

	// don't do anything if you are requested to clear.
	if (bShouldClear == true) return FALSE;
	
	// on a very fast application this can be empty
	if (playlist.size() < 1) return FALSE;

	for (int i=0; i<playlist.front()->size(); i++) {
		// reset keyframe is_idle value, just in case it has been stored for re-use.
		(*playlist.front())[i]->is_idle = false;
		(*playlist.front())[i]->hasStarted = false;
	}
	
#ifdef PLAYLIST_DEBUG_MODE
	ofLog(OF_LOG_VERBOSE) << "deleting front of queue";
#endif
	
	playlist.pop_front();
	
#ifdef PLAYLIST_DEBUG_MODE
	ofLog(OF_LOG_VERBOSE) << "Playlist size now:" << playlist.size();
#endif
	
	if (!playlist.empty()) {
		Keyframe currentKeyframe = *(playlist.front());
//		int idleCount = 0;
		for (int i=0; i<currentKeyframe.size(); i++){
			currentKeyframe[i]->start();
			currentKeyframe[i]->execute();
			if (bShouldClear == true) {
				playlistMutex.unlock();
				return TRUE;
			}

			_r &= currentKeyframe[i]->is_idle;			// &= means, if just one of the result values differs from the initial _r value, _r will be false
		}
		// make sure the caller of this function sets anim_idle to the return value _r!

	} else {
		_r = false;
	}

	return _r;
}

// ----------------------------------------------------------------------

void ofxPlaylist::flush(){
		// push stuff from the playlistBuffer into the playlist, if there's stuff left in there.
		while (!playlistBuffer.empty()) {
			playlist.push_back(playlistBuffer.front());
			playlistBuffer.pop_front();
#ifdef PLAYLIST_DEBUG_MODE
			ofLog(OF_LOG_VERBOSE) << "flushing one object";
#endif
		}
	
}

// ----------------------------------------------------------------------

void ofxPlaylist::savePlaylistCurrentlyInBufferToInternalMap(string playlistName){
	
	// n.b.: this needs to happen before flush() is called for the first time, typically, this would happen during update()
	
	savedPlaylists[playlistName] = playlistBuffer;
};

// ----------------------------------------------------------------------

void ofxPlaylist::saveAndInitialiseTargetsAndClear(string playlistName){

	// this will set all ofxPlaylist target values to their initial state
	// but then we instantly clear the playlists, so that the animation will only be running if we call replacePlaylistCurrentlyInBufferWithPlaylistFromInternalMap().

	savePlaylistCurrentlyInBufferToInternalMap(playlistName);
	update();
	clear();
}


// ----------------------------------------------------------------------

void ofxPlaylist::replacePlaylistCurrentlyInBufferWithPlaylistFromInternalMap(string playlistName){
	
	map<string, deque<shared_ptr<Keyframe> > >::iterator it = savedPlaylists.find(playlistName);
	
	if (it != savedPlaylists.end()){
		// we have found a saved playlist with this name!
		
		playlist.clear();					// attempt to clear playlist
		playlistBuffer = it->second;		// replace buffer with stored playlist
		
	} else {
		ofLog(OF_LOG_WARNING) << "ofxPlaylist: could not find saved playlist: " << playlistName;
	}
	
};


// ----------------------------------------------------------------------

ofxPlaylist::~ofxPlaylist(){
#ifdef PLAYLIST_DEBUG_MODE
		ofLog(OF_LOG_VERBOSE) << "~ofxPlaylist";
#endif
		detach();
		bShouldClear = true;
		if (playlistMutex.try_lock()){			// just in case
												// the object gets destroyed while the mutex is locked.
			clear();
		}
		playlistMutex.unlock();					// unlock the mutex regardless of what happens.
}

