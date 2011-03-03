/*
 *  keyframe_swapper.cpp
 *  getty
 *
 *  Created by Timothy Gfrerer on 20/10/2010.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "keyframe_swapper.h"

KeyFrame_Swapper::KeyFrame_Swapper(){
  cout << "tweener created!" << endl;
  is_idle = FALSE;      // initialise zero Pointer
  pTarget1 = NULL;
  pTarget2 = NULL;
  hasStarted = FALSE;
  step = 0;
}

KeyFrame_Swapper::~KeyFrame_Swapper(){
  cout << "keyframe_swapper destroyed!" << endl;
}

void KeyFrame_Swapper::start(){
  cout << "keyframe_swapper start!" << endl;
  is_idle = FALSE;
  startTimeMillis = ofGetSystemTime();
  step = 0;
}

void KeyFrame_Swapper::init( void * _pTarget1, void * _pTarget2, const int& _steps){
  steps = _steps;
  startTimeMillis = 0;
  step = 0;
  pTarget1 = _pTarget1;
  pTarget2 = _pTarget2;
}

void KeyFrame_Swapper::execute(){
  
  // check if tween_idle pointer has been properly initialized 
  if ((pTarget1 != NULL) && (pTarget2 != NULL) && (is_idle == FALSE)) {
    
    if (startTimeMillis == 0) start();
    
    // cout << "tw-execute: is_idle " << is_idle << endl;
    
    step = labs(ofGetSystemTime() - startTimeMillis);
    
    if (step > steps) {
      // swap the two pointers
      void * tmpP;
      tmpP = pTarget2;
      pTarget2 = pTarget1;
      pTarget1 = tmpP;
      cout << "swapping! " << endl;
      // say you're tired and don't want to do this again.
      is_idle = TRUE;
    }
  }
};
