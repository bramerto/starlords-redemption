#ifndef _BULLET_H_
#define _BULLET_H_

#include <stdio.h>
#include <stdlib.h>
#include <cgl/cgl.h>
#include <cgl/core.h>
#include <core/corefile.h>
#include <coresound/coresound.h>
#include <math.h>

#define COLOR_WALL 0xffff0000

#define WEAPON_PISTOL  0
#define WEAPON_ASSAULT 1
#define WEAPON_DAGGER  2

#define PLAYER 0
#define ENEMY 1

extern s_sprite spr_pistolbullet,spr_pistolbulletm,spr_assaultbullet;
extern s_bitmap bmp_junglelevelmask;
extern s_bitmap bmp_citylevelmask;
extern int screenx,screeny,level;

class c_bullet
{
	public:
	
	int x,y,dx,dy,ds,speed,pdamage,edamage,facing,weapon,addangle,collision[2];
	float angle;
	bool active;
	
	void Init(int posx,int posy,int destx,int desty,int weapon);
	void Draw();
	void Handle();
};

#endif
