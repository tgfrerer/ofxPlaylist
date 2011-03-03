#ifndef GUARD_KEYFRAME_SWAPPER
#define GUARD_KEYFRAME_SWAPPER
/*
 *  keyframe_swapper.h
 *  getty
 *
 *  Created by Timothy Gfrerer on 20/10/2010.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "ofMain.h"
#include "key_frame.h"

class KeyFrame_Swapper : public KeyFrame{
public:
  
  KeyFrame_Swapper();
  ~KeyFrame_Swapper();
  
  
  void init( void * _pTarget1, void * _pTarget2, const int& _steps);
  
  void start();
  void execute();        // returns tweened value as a float
  
private:
  
  // variables you need to save for every tween
  void * pTarget1;
  void * pTarget2;
  bool hasStarted;
  unsigned long startTimeMillis;
  int steps; 
  int step;
  
};




#endif

