#ifndef GUARD_TWEENER_FUNCTIONS
#define GUARD_TWEENER_FUNCTIONS

/*
 *  tweener_functions.h
 *  getty
 *
 *  Created by Timothy Gfrerer on 19/10/2010.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

class Tweener_base {
public:
  Tweener_base(){};
  ~Tweener_base(){};
  
  static float tween_sin(const float& _min, const float& _max, const int& _step, const int& _steps, bool * _tween_idle){
    // cout << "tweening: "<< step << "/" << steps << endl;
    
    // bool * tween_idle is a pointer put out there by the caller function
    // in order to find out if the operation has completed.
    if (!*_tween_idle){
      double _r = 0.0;
      
      if (_step > _steps){
        *_tween_idle = TRUE;
        return _max;
      }
      // cout << _step << " /";
      _r = _min + sin(PI * (float(_step)/_steps) / 2.f) * (_max - _min);
      return _r;
    }
  };

  static float tween_lin(const float& _min, const float& _max, const int& _step, const int& _steps, bool * _tween_idle){
    // cout << "tweening: "<< step << "/" << steps << endl;
    
    // bool * tween_idle is a pointer put out there by the caller function
    // in order to find out if the operation has completed.
    if (!*_tween_idle){
      double _r = 0.0;
      
      if (_step > _steps){
        *_tween_idle = TRUE;
        return _max;
      }
      // cout << _step << " /";
      _r = _min + (float(_step)/float(_steps)) * float(_max - _min);
      return _r;
    }
  };
  

  // **********************************************************************
  // quadratic easing in - accelerating from zero velocity 
  // tig, with thanks to:
  //// Robert Penner - robertpenner.com //// 
  // t: current time, b: beginning value, c: change in value, d: duration 
  // t and d can be frames or seconds/milliseconds 
  static float tween_quad_in(const float& _min, const float& _max, const int& _step, const int& _steps, bool * _tween_idle){
    // cout << "tweening: "<< step << "/" << steps << endl;
    
    // bool * tween_idle is a pointer put out there by the caller function
    // in order to find out if the operation has completed.
    if (!*_tween_idle){
      float _r = 0.0;
      
      if (_step > _steps){
        *_tween_idle = TRUE;
        return _max;
      }
      //      t /= d;
      //      _r = c*t*t + b;
      
      float _pct = float(_step) / float(_steps);
      
      _r = (_max-_min) * _pct * _pct + _min;
      return _r;
    }
  };

  
  // **********************************************************************
  // quadratic easing out - decelerating from _max velocity 
  // tig, with thanks to:
  // Robert Penner - robertpenner.com, http://www.gizma.com/easing/  

  // t: current time, b: beginning value, c: change in value, d: duration 
  // t and d can be frames or seconds/milliseconds 
  static float tween_quad_out(const float& _min, const float& _max, const int& _step, const int& _steps, bool * _tween_idle){

    // bool * tween_idle is a pointer put out there by the caller function
    // in order to find out if the operation has completed.
    if (!*_tween_idle){
      float _r = 0.0;
      
      if (_step > _steps){
        *_tween_idle = TRUE;
        return _max;
      }
      //      t /= d;
      //      _r =  -c * t*(t-2) + b;      
      
      float _pct = float(_step) / float(_steps);
      
      _r = -(_max-_min) * _pct * (_pct -2) + _min;

      return _r;
    }
  };
  

  static float tween_wait(const float& _min, const float& _max, const int& _step, const int& _steps, bool * _tween_idle){
    
    // bool * tween_idle is a pointer put out there by the caller function
    // in order to find out if the operation has completed.
    if (!*_tween_idle){
      float _r = 0.0;
      
      if (_step > _steps){
        *_tween_idle = TRUE;
        _r = _max;
        return _r;
      }
      _r = _min;
      
      return _r;
    }
  };
  
  
  

};





#endif