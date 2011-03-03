#ifndef GUARD_KEY_FRAME
#define GUARD_KEY_FRAME

/*
 *  key_frame.h
 *  getty
 *
 *  Created by Timothy Gfrerer on 19/10/2010.
 *  Copyright 2010 . All rights reserved.
 *
 */

#include "ofMain.h"
#include <stream.h>

class KeyFrame {
public:
  KeyFrame(){};
  virtual ~KeyFrame(){ 
	  ofLog(OF_LOG_VERBOSE, "keyframe destroyed.");
  };     // by calling this function virtual I make sure to call the destructor for 
         // the derived class - and not for the parent class!
  
  bool is_idle;
  int key_frame_type;        // the type of keyframe (TWEEN_SIN, etc.)
  
  virtual void execute(){};  // this function needs to be set in all inheriting classes!
  virtual void start(){};
  
};




#endif
