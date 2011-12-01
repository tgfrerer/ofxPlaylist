<pre>
     _____    ___     
    /    /   /  /     ofxPlaylist
   /  __/   /  /__    (c) ponies & light, 2009-2011. 
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

A playlist-based animation library. 

A playlist holds a sequence of Keyframes which point to values to be tweened over time.

Keyframes are cleared from their playlist upon completion. 

## Features:

* Any of Robert Penner' tweening functions via ofxTween
* Calculate total remaining duration of Playlist
* Pause Tween
* Event Keyframes
* Combined Keyframes which execute in parallel
* NEW: Bézier curve tweens

## Usage

Assuming you'd want to tween pos.x from it's current position when the Playlist starts executing to 0.f:

<pre>
using namespace Playlist;
playlist.addKeyFrame(Action::tween(1000.f, &pos.x, 0., TWEEN_SIN, TWEEN_EASE_OUT, &pos.x));
playlist.addKeyFrame(Action::pause(500.f));
playlist.addKeyFrame(Action::event(this, "EVENT MESSAGE"));
</pre>