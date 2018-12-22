#include "c_pickup.h"

void c_pickup::InitAnim(int animnr)
{
	if (animnr!=currentanim)
	{
		currentanim=animnr;
		animframe=anim[currentanim].startframe;
		animcount=0;
    }
}

void c_pickup::Init(int posx, int posy, int pickuptype)
{
	x=posx;
	y=posy;
	active=true;
	type=pickuptype;
	
	// INITIALIZE ANIMATIONS
	anim[0].startframe=0; anim[0].endframe=11; anim[0].delay=6; anim[0].loop=1;
	anim[1].startframe=0; anim[1].endframe=20; anim[1].delay=2; anim[1].loop=1;
}

void c_pickup::Draw()
{
	if (active)
	{
		if(type==KEY) CGL_DrawSprite(x-screenx, y-screeny,spr_key[animframe]);
		if(type==COIN) CGL_DrawSprite(x-screenx, y-screeny,spr_coin[animframe]);
		if(type==ASSAULT) CGL_DrawSprite(x-screenx, y-screeny,spr_weapon_assault);
	}
	
	// HANDLE ANIMATION  
	animcount++;
	if (animcount>anim[currentanim].delay)
	{
		animframe++;
		if (animframe>anim[currentanim].endframe) animframe=anim[currentanim].startframe;
		animcount=0;
    }
}

void c_pickup::Handle()
{
	if(active)
	{
		if (type==KEY) 
		{
			InitAnim(ANIM_KEY); 
			if(CGL_CheckBoxCollision(player.x, player.y, 50, 64,x, y, 48,48 )) 
			{
				player.key=true; 
				Soundsystem_PlaySound(&snd_pickup_key,0);
				active=false;
			}
		}
		if (type==COIN)
		{ 
			InitAnim(ANIM_COIN); 
			if(CGL_CheckBoxCollision(player.x, player.y, 50, 64,x, y, 32,32 )) 
			{
				player.point++;
				Soundsystem_PlaySound(&snd_pickup_coin,0);
				active=false; 
			}
		}
		if (type==ASSAULT)
		{ 
			if(CGL_CheckBoxCollision(player.x, player.y, 50, 64, x+75, y, 75, 24)) 
			{
				player.weapon=WEAPON_ASSAULT;
				Soundsystem_PlaySound(&snd_pickup_key,0);
				active=false; 
			}
		}
	}
}

