#ifndef _C_PLAYER_H_
#define _C_PLAYER_H_

#include <stdio.h>
#include <stdlib.h>
#include <cgl/cgl.h>
#include <cgl/core.h>
#include <core/corefile.h>
#include <coresound/coresound.h>
#include <math.h>

#include "c_enemy.h"
#include "c_gamescreens.h"

#define COLOR_WALL   0xffff0000
#define COLOR_POISON 0xff00ff12
#define COLOR_LADDER 0xfffffc00
#define COLOR_DOOR   0xff00f0ff

#define COLLISION_TOP			0
#define COLLISION_TOP_LEFT		1
#define COLLISION_MIDDLE_LEFT	2
#define COLLISION_BOTTOM_LEFT	3
#define COLLISION_BOTTOM		4
#define COLLISION_BOTTOM_RIGHT	5
#define COLLISION_MIDDLE_RIGHT	6
#define COLLISION_TOP_RIGHT		7

#define MAXBULLETS 50

#define WEAPON_PISTOL	0
#define WEAPON_ASSAULT	1
#define WEAPON_DAGGER	2

#define MAXPANIMS  10
#define MAXPFRAMES 21

#define ANIM_IDLE 0
#define ANIM_WALK 1

typedef struct 
{
    int startframe,endframe,delay,loop;
} s_animplayer;

extern int level;

extern s_bitmap bmp_junglelevelmask;
extern s_sprite spr_player[MAXPFRAMES], spr_crosshair;
extern s_sprite spr_weapon_pistol,spr_weapon_pistolm;
extern s_sprite spr_weapon_assault,spr_weapon_assaultm;
extern s_sprite spr_weapon_dagger,spr_weapon_daggerm;
extern s_font gamefont;
extern s_sound snd_footsteps[3];
extern s_sound snd_hurt[3];

extern int screenx,screeny,gameactive,mx,my,mb;

class c_player
{
	public:
	
	int x,y,facing,health,temphealth,lives,gravity,jump,slash,canshoot,shoot,speed,step,point,key;
	int bulletcount,ammo,shootcount,stepcount,weapon;
	float angle;
	int collision[8];
	
	bool respawn, assaultactive;
	
	s_animplayer anim[MAXPANIMS];
    int currentanim,animframe,animcount;
	
	void Init();
	void InitAnim(int anim);
	void Draw();
	void HandleInteraction(c_gamescreens *gamescreens);
	void Handle(c_gamescreens *gamescreens,int mousebtn);
};

#endif
