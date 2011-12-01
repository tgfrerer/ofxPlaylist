<pre>
     _____    ___     
    /    /   /  /     ofxPlaylist
   /  __/ * /  /__    (c) ponies & light, 2009-2011. 
  /__/     /_____/    oo43.com

  ofxPlaylist
  Created by Tim Gfrerer 2009-2011.
  
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
</pre>


# ofxPlaylist

A playlist-based animation library. Developed over a couple of years and used in a growing number of permanent installations, deployed on OS X, Windows and Linux.

Playlists hold a sequence of Keyframes, which either:

+ point to values to be tweened over time.
+ pause for a given duration
+ trigger an Event
 
Keyframes are cleared from their Playlist upon completion. Additional Keyframes can be pushed onto the end of any Playlist at any time. Playlists can also be cleared at any time, even from within a Keyframe Event triggered by a playlist itself.

## Key Features:

* Tweens using any of Robert Penner' functions via ofxTween
* Pause
* Event Keyframes (special thanks to James George for suggesting these!)
* Internal memory management using ofPtr()
* Keyframes can be set to execute in sequence or in parallel
* Calculate total remaining duration of Playlist
* NEW: Tweens follwing Bézier curves, mirroring the functionality of Adobe After Effects temporal timeline curves.

## Use:

Keyframes tween from value a variable holds at the moment the Keyframe is reached to an absolute target value. Assuming you'd want to tween a float xPos from a randomly assigned value to 0.f, here's a mockup:

<pre>

// .h

class testApp(){
	// …
	ofxPlaylist playlist1;
	float xPos;
	// …
}

// .cpp

void testApp::setup(){

	xPos = ofRandomuf(1000.f);

	using namespace Playlist;

	// call factory function to insert a new Keyframe 
	// (controlling xPos) to playlist1
	
	// the tween shall take 1000ms (a float time value indicates
	// absolute time in Milliseconds, an integer time value 
	// indicates you want to go frame-based)

	playlist1.addKeyFrame(Action::tween(1000.f, &xPos, 0., TWEEN_SIN, TWEEN_EASE_OUT));

}

void testApp::update(){

	playlist1.update();

	ofLog(OF_LOG_VERBOSE) << "xPos: " << xPos;
}

void testApp::draw(){
	// use xPos
	// ...
}

void testApp::keyPressed(){

	if (key == ' '){
		// starts/pauses execution of the playlist
		playlist1.isPlaying ^= true;
	} 

}

</pre>

## See also: 

A more hands-on example of how to use ofxPlaylist and a run-down of its key features is shown in the included example Project, 
<pre>
example/ofxPlaylistExample
</pre>

## Dependencies:

<pre>
ofxEasing (part of ofxTween)
</pre>