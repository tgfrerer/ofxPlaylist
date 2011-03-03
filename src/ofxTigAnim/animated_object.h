#ifndef GUARD_ANIMATED_OBJECT
#define GUARD_ANIMATED_OBJECT

/*
 *  animated_object.h
 *
 *  Created by Timothy Gfrerer on 19/10/2010.
 *  Copyright 2010. All rights reserved.
 *
 */

#include "tweener.h"
#include "keyframe_swapper.h"

#include <queue>

class AnimatedObject {
public:
  
  bool anim_idle;              // whether the current animatedObject is animating
  queue<list<KeyFrame *> *> animationQueue;
  
  
  AnimatedObject(){ 
    anim_idle = TRUE;
	ofLog(OF_LOG_VERBOSE, "Instantiated new AnimatedObject.");
  };

  // ********** UPDATER **********
  
  virtual void update(){
    if (animationQueue.size() > 0){
      if (anim_idle == TRUE){
        anim_idle = delete_front_of_queue_and_initialize_next_element_if_present();
      } else {
        // do some animation here!
        int _boolCount = 0;
        int _j = 0;
        
        list <KeyFrame *>::iterator kFSLIterator = animationQueue.front()->begin();
        while (kFSLIterator != animationQueue.front()->end()) {
          // here is the place to do parallel transformations!
          (*kFSLIterator)->execute();
          // cout << "anim_o exec: isIdle: " << (*kFSLIterator)->is_idle << " _boolSum = ";
          if ((*kFSLIterator)->is_idle == TRUE) _boolCount++;
          _j++;
          kFSLIterator++;
        }
        if (_boolCount == _j) {
          // all the tweens report true, so all the work is done for this frame
          anim_idle = TRUE;
          // check if there are more frames to do work on...
          anim_idle = delete_front_of_queue_and_initialize_next_element_if_present();
        } else {
          // there's still some more stuff to do.
          anim_idle = FALSE;
        }
        
        // cout << _boolCount << endl;
        
      }
    } 
  };  

  
  void addNewKeyFrame(KeyFrame * _kfP){
    // tim-debug: this function was leaking memory like a whole geriatric ward!
    
    // create a permanent object which holds an empty List of (Keyframe) pairs
    // and add it to the animationQueue

    //    list<KeyFrame *> * tmp_list;
    //    tmp_list = new list<KeyFrame *>;
    
    animationQueue.push(new list<KeyFrame *>);
    animationQueue.back()->push_back(_kfP);

    // add keyFrame to this list
    // scaffoldFrameListPointer
    anim_idle = FALSE;
  }

  void addToKeyFrame(KeyFrame * _kfP){
    // get the last element of the queue
    list<KeyFrame *> * scaffoldFrameListPointer = animationQueue.back();
    
    //  add keyFrame to the list.
    scaffoldFrameListPointer->push_back(_kfP);
    anim_idle = FALSE;
  }

  
  
  // ********** DESTRUCTOR ********** 
  
  ~AnimatedObject(){
    // make sure to delete all Keyframes!!!
    cleanup();
  };
  
  
  void cleanup(){
    while (!animationQueue.empty()) {
      // erase Keyframe objects from memory by calling their destructors...
      //      for (int _i; _i < animationQueue.front().size(); _i++ ){
      //        delete(animationQueue.front()[_i].kF);
      //      }
      
      // kFSLIterator == keyFrameStructList Iterator
      
      list <KeyFrame *>::iterator kFSLIterator = animationQueue.front()->begin();
      while (kFSLIterator != animationQueue.front()->end()) {
        delete(*kFSLIterator);
        *kFSLIterator = NULL;
        kFSLIterator++;
      }
      
      // delete the list of KeyFrameStruct at the current queue position
      delete(animationQueue.front());
      
      // set the pointer to NULL
      animationQueue.front() = NULL;
      
      // then delete the pointer to it...
      animationQueue.pop();
    }
  };
  
  
  // ********************************************************************************
  
private:

  bool delete_front_of_queue_and_initialize_next_element_if_present(){
    bool _r = TRUE;
    
    // erase Keyframe objects from memory by calling their destructors...
    list <KeyFrame *>::iterator kFSLIterator = animationQueue.front()->begin();
    while (kFSLIterator != animationQueue.front()->end()) {
      delete(*kFSLIterator);
      kFSLIterator++;
    }
    
    // delete the list of KeyFrameStruct at the current queue position
    delete(animationQueue.front());

    // set the pointer to NULL
    animationQueue.front() = NULL;
    
    // then finish the beast off by deleting the pointer to it.
    animationQueue.pop();
    // initialise the next KeyFrame if there are any left...
    if (animationQueue.size() > 0) {
      list <KeyFrame *>::iterator kFSLIterator = animationQueue.front()->begin();
      while (kFSLIterator != animationQueue.front()->end()) {
        (*kFSLIterator)->start();
        kFSLIterator++;
      }
      // make sure the caller of this function sets anim_idle to the return value _r!
      _r= FALSE;
    }
    return _r;
  };    

  // ********************************************************************************


};


#endif