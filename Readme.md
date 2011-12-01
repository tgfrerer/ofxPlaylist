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

A playlist-based animation library. Developed over a couple of years and used in a growing number of permanent installations. 

Playlists hold a sequence of Keyframes, which either:

+ point to values to be tweened over time.
+ pause for a given duration
+ trigger an Event
 
Keyframes are cleared from their Playlist upon completion. Additional Keyframes can be pushed onto the end of any Playlist at any time. Playlists can also be cleared at any time.

## Key Features:

* Tweens using any of Robert Penner' functions via ofxTween
* Pause
* Event Keyframes (special thanks to James George for suggesting these!)
* Internal memory management using ofPtr()
* Keyframes can be set to execute in sequence or in parallel
* Calculate total remaining duration of Playlist
* NEW: Tweens follwing Bézier curves, mirroring the functionality of Adobe After Effects temporal timeline curves.

## Use:

Assuming you'd want to tween pos.x from it's current position when the Playlist starts executing to 0.f:

<pre>

// .h
ofxPlaylist playlist1;

// .cpp

using namespace Playlist;

// call factory function to insert a new keyframe to playlist
// the tween shall last 1000ms (a float value indicates absolute time, an integer time value says you want to use frames as your time base)

playlist1.addKeyFrame(Action::tween(1000.f, &pos.x, 0., TWEEN_SIN, TWEEN_EASE_OUT, &pos.x));

// add a 500ms pause after the tweening ends.
playlist1.addKeyFrame(Action::pause(500.f));

// trigger an event after the 500ms pause ends.
playlist1.addKeyFrame(Action::event(this, "EVENT MESSAGE"));
</pre>

## See also: 

A more hands-on example of how to use ofxPlaylist and a run-down of its key features is shown in the included example Project, example/ofxPlaylistExample