<pre>
     _____    ___     
    /    /   /  /     ofxPlaylist
   /  __/ * /  /__    (c) ponies & light, 2009-2012. 
  /__/     /_____/    poniesandlight.co.uk

  ofxPlaylist
  Created by Tim Gfrerer 2009-2012.
  
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

Each Keyframe holds a pointer to the variable it has been assigned to modify, so the variable is updated directly, everytime their Playlist is updated. 

Assuming you'd want to tween a float xPos to a randomly assigned target value, here's a mockup:

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

	xPos = ofRandomuf(ofGetWidth());

}

void testApp::update(){

	playlist1.update();

	ofLog(OF_LOG_VERBOSE) &lt;&lt; &quot;xPos: &quot; &lt;&lt; ofToString(xPos);
}

void testApp::draw(){
	// use xPos
	// ...
}

void testApp::keyPressed(){
using namespace Playlist;

	if (key == ' '){
		// adds a new keyframe to playlist1

	float targetPos = ofRandomuf(ofGetWidth());

	playlist1.addKeyFrame(Action::tween(1000.f, &xPos, targetPos , TWEEN_SIN, TWEEN_EASE_OUT));

	// the playlist will now start tweening xPos towards targetPos at the next update() cycle.
	} 

}

</pre>

## See also: 

A more hands-on example of how to use ofxPlaylist and a run-down of its key features is shown in the included example Project:
 
<pre>
example/ofxPlaylistExample
</pre>

## Dependencies:

<pre>
	none. (ofxPlaylistAEHelper makes heavy use of ofxXMLSettings, which is part of the openFrameworks Core Addons)
</pre>