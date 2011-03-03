#ifndef GUARD_PLAY_LIST_OBJECT
#define GUARD_PLAY_LIST_OBJECT





#define PLAYLIST_LOOP_INFINITE       42
#define PLAYLIST_LOOP_ONE_OFF         1


#define GRID_WAIT                     0
#define GRID_WAIT_1000                1
#define GRID_WAVE                     2
#define GRID_SINGLE                   3
#define GRID_HERO                     4
#define GRID_HERO_RECLAIM             5
#define GRID_TRICKLE_DOWN             6
#define GRID_LOAD_NEXT                7
#define GRID_SET_HERO_DIMENSIONS      8
#define GRID_LEAVE                    9

#define SLIDESHOW_WAIT               99
#define SLIDESHOW_FADE_TOBLACK        0
#define SLIDESHOW_FADE_OUT            1
#define SLIDESHOW_FADE_IN             2
#define SLIDESHOW_WAIT_1000           3
#define SLIDESHOW_GET_NEXTIMG         4
#define SLIDESHOW_LOAD_NEXTIMG        5
#define SLIDESHOW_CROSSFADE           6
#define SLIDESHOW_SHOW_ONE            7
#define SLIDESHOW_SHOW_TWO            8
#define SLIDESHOW_FLIP_IMAGES         9
#define SLIDESHOW_FLIP_CURRENT       10
#define SLIDESHOW_SET_OPAQUE         11
#define SLIDESHOW_3D_FLIP_BACK       12
#define SLIDESHOW_3D_FLIP_FORTH      13
#define SLIDESHOW_FADE_OUT_SLOWLY    14 
#define SLIDESHOW_FADE_IN_SLOWLY     15

#define SLIDESHOW_MODE_CROSSFADE      1
#define SLIDESHOW_MODE_SINGLE_FADE    2
#define SLIDESHOW_MODE_SLOW_FADE    2
#define SLIDESHOW_MODE_3DFLIP         3

#define SORT_ORDER_RANDOM             0
#define SORT_ORDER_FILENAME_ASC       1
#define SORT_ORDER_TIME_ASC           2
#define SORT_ORDER_TIME_DESC           3


//static int TILE_W = 120;
//static int TILE_H = 80;

/*
 *  play_list_object.h
 *  getty
 *
 *  Created by Timothy Gfrerer on 29/10/2010.
 *  Copyright 2010. All rights reserved.
 *
 */
#include "ofMain.h"
#include <queue.h>
#include "ofxXmlSettings.h"

class PlayListObject {
public:

  PlayListObject(){
    display_duration = 0;   // pre-set is zero, this value has to be set by the playlist_builder...
    bModePaused = false;
  };
  virtual ~PlayListObject(){};  
  
  virtual void set_path(string _path){};
  virtual void set_sort_order(int _sort_order){};
  virtual void preload(){};
  virtual void reset(){};
  
  virtual void show(){};
  virtual void update(){};
  virtual void draw(){};
  virtual void key_pressed(int key){};
  virtual bool ready_to_leave(){};
  virtual void prepare_to_leave(){};
  
  int loop_mode;
  
  // files are waiting to be processed.
  bool bFilesAreWaiting;
  bool is_ready;
  bool on_display;
  bool anim_idle;
  bool preparing_to_leave;
  bool bPreloadCalledAlready;
  string isA;
  
  queue<int> Playlist;
  queue<int> origPlaylist;

  long display_duration;
  unsigned long appeared_at_millis;
  bool bModePaused;

  void set_dimensions(int _screen_w, int _screen_h, int _tile_w, int _tile_h){
    TILE_H = _tile_h;
    TILE_W = _tile_w;
    SCREEN_H = _screen_h;
    SCREEN_W = _screen_w;
  };

protected:
  int TILE_W;
  int TILE_H;
  int SCREEN_W;
  int SCREEN_H;

  
};


#endif
