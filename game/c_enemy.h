#ifndef _ENEMY_H_
#define _ENEMY_H_

#include <stdio.h>
#include <stdlib.h>
#include <cgl/cgl.h>
#include <cgl/core.h>
#include <core/corefile.h>
#include <coresound/coresound.h>
#include <math.h>

#include "c_player.h"

#define COLOR_WALL 0xffff0000
#define COLOR_POISON 0xff00ff12
#define COLOR_LADDER 0xfffffc00
#define COLOR_PATH 0xff0000ff
#define COLOR_ENDPATH 0xffff9000

#define COLLISION_TOP			0
#define COLLISION_TOP_LEFT		1
#define COLLISION_MIDDLE_LEFT	2
#define COLLISION_BOTTOM_LEFT	3
#define COLLISION_BOTTOM		4
#define COLLISION_BOTTOM_RIGHT	5
#define COLLISION_MIDDLE_RIGHT	6
#define COLLISION_TOP_RIGHT		7

#define MAXEANIMS  5
#define MAXEFRAMES 8

#define ANIM_IDLE 0
#define ANIM_WALK 1

#define JUNGLE 0
#define CITY 1

typedef struct 
{
    int startframe,endframe,delay,loop;
} s_animenemy;

extern s_bitmap bmp_junglelevelmask, bmp_citylevelmask;

extern int screenx,screeny,gameactive,level;
extern s_sprite spr_enemyjungle[MAXEFRAMES], spr_enemycity[MAXEFRAMES];
extern s_sprite spr_weapon_pistol,spr_weapon_pistolm,spr_healthbar,spr_healthbarborder;
extern s_font gamefont;
extern s_sound snd_footsteps[3];
extern s_sound snd_hurt[3];

class c_enemy
{
	public:
	
	int x,y,dx,dy,health,temphealth,speed,collision[8],facing,type,width,height,gravity;
	int step,stepcount,canshoot,shoot,shootcount,angle;
	bool active;
	
	int currentanim,animframe,animcount;
    s_animenemy anim[MAXEANIMS];
	
	void Init(int posx, int posy, int enemytype);
	void InitAnim(int animnr);
	void Draw(int plrx,int plry);
	void HandleInteraction();
	void Handle(int plrx);
};

#endif
