/*
 *  ofxPlaylist.cpp
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


ofxPlaylist& ofxPlaylist::addKeyFrame(ofPtr<ofxBaseKeyframe> _action){
	// tim-debug: this function was leaking memory like a whole geriatric ward!
	// no more. ofPtr to the rescue.

	lastDuration = _action->getDuration();
	duration += lastDuration;

	playlistBuffer.push_back(ofPtr<Keyframe> (new Keyframe()));

	// add keyframe to the playlistBuffer
	playlistBuffer.back()->push_back(_action);

	anim_idle = FALSE;
	return *this;
}

// ----------------------------------------------------------------------

ofxPlaylist& ofxPlaylist::addToKeyFrame(ofPtr<ofxBaseKeyframe> _action){
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

	if (playlistMutex.tryLock()){
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
	if(playlistMutex.tryLock()){
#ifdef PLAYLIST_DEBUG_MODE
		ofLog(OF_LOG_VERBOSE) << "Clearing ofxPlaylist.playlist";
#endif
		playlist.clear(); 					// aah...... the beauty of ofPtr<>
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

			_r &= currentKeyframe[i]->is_idle;			// &= means, if even one of the result values differs from the initial _r value, _r will be false
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
	// but then we instantly clear the playlists, so that the animation will only be running if we call queueAnimations().

	savePlaylistCurrentlyInBufferToInternalMap(playlistName);
	update();
	clear();
}


// ----------------------------------------------------------------------

void ofxPlaylist::replacePlaylistCurrentlyInBufferWithPlaylistFromInternalMap(string playlistName){
	
	map<string, deque<ofPtr<Keyframe> > >::iterator it = savedPlaylists.find(playlistName);
	
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
		if (playlistMutex.tryLock(50)){			// allow for a grace period of 50ms
												// before clearing, just in case
												// the object gets destroyed while the mutex is under lock.
			clear();
		}
		playlistMutex.unlock();					// unlock the mutex regardless of what happens.
}

