#ifndef _PICKUP_H_
#define _PICKUP_H_

#include <stdio.h>
#include <stdlib.h>
#include <cgl/cgl.h>
#include <cgl/core.h>
#include <core/corefile.h>
#include <coresound/coresound.h>

#include "c_player.h"

#define COLOR_WALL   0xffff0000
#define COLOR_POISON 0xff00ff12
#define COLOR_LADDER 0xfffffc00

#define MAXPICKANIMS  2
#define MAXPICKFRAMES 21

#define ANIM_KEY  0
#define ANIM_COIN 1

#define KEY 	0
#define COIN 	1
#define ASSAULT 2

typedef struct 
{
    int startframe,endframe,delay,loop;
} s_animpickup;

extern int screenx,screeny,gameactive;
extern s_sprite spr_weapon_assault, spr_key[MAXPICKFRAMES], spr_coin[MAXPICKFRAMES];
extern s_sound snd_pickup_coin,snd_pickup_key;
extern c_player player;

class c_pickup
{
	public:
	
	int x, y, type;
	bool active;
	
	int currentanim,animframe,animcount;
    s_animpickup anim[MAXPICKANIMS];
	
	void InitAnim(int animnr);
	void Init(int posx, int posy, int pickuptype);
	void Draw();
	void Handle();
};

#endif
