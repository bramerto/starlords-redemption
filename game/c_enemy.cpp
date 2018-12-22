#include "c_enemy.h"

void c_enemy::InitAnim(int animnr)
{
	if (animnr!=currentanim)
	{
		currentanim=animnr;
		animframe=anim[currentanim].startframe;
		animcount=0;
    }
}

void c_enemy::Init(int posx, int posy, int enemytype)
{
	x=posx;
	y=posy;
	type=enemytype; 
	active = true;
	health = 100;
	temphealth = 100;
	
	if (type==JUNGLE)
	{
		width=52;
	}
	else
	{
		width=44;
	}
	height=64;
	
	// INITIALIZE ANIMATIONS
	anim[0].startframe=0; anim[0].endframe=1; anim[0].delay=50; anim[0].loop=1;
	anim[1].startframe=1; anim[1].endframe=4; anim[1].delay=5; anim[1].loop=1;
}
void c_enemy::Draw(int plrx,int plry)
{
	if(active)
	{
		if(type==JUNGLE)
		{
			if (facing) CGL_DrawSprite(x-screenx,y-screeny,spr_enemyjungle[animframe]);
			else CGL_DrawMirroredSprite(x-screenx,y-screeny,spr_enemyjungle[animframe]);
		}
		if(type==CITY)
		{
			if (facing) CGL_DrawSprite(x-screenx,y-screeny,spr_enemycity[animframe]);
			else CGL_DrawMirroredSprite(x-screenx,y-screeny,spr_enemycity[animframe]);
		}
		
		
		for (int t=0;t<health/2;t++) CGL_DrawSprite(x-screenx+t,y-screeny-30,spr_healthbar);
		CGL_DrawSprite(x-screenx-2,y-screeny-32,spr_healthbarborder);
		CGL_DrawText(x-screenx+7,y-screeny-60,gamefont,"%d",health);
		
	
		angle=atan2(-(plrx+25-x),plry+32-y);
		
		
		if (type==CITY)
		{
			if (facing) CGL_DrawRotatedSprite(x-5-screenx,y+32-screeny,spr_weapon_pistol,angle*180/pi+90);
			else CGL_DrawRotatedSprite(x-5-screenx,y+32-screeny,spr_weapon_pistolm,angle*180/pi+270);
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
}
void c_enemy::HandleInteraction()
{
	if (active)
	{
		for (int t=0;t<8;t++) collision[t]=0;
		
		if(level==0)
		{
			if (CGL_GetPixel(x+25,y,bmp_junglelevelmask)==COLOR_WALL) 			collision[COLLISION_TOP]=			1;
			if (CGL_GetPixel(x,y+32,bmp_junglelevelmask)==COLOR_WALL) 			collision[COLLISION_MIDDLE_LEFT]=	1;
			if (CGL_GetPixel(x,y+64,bmp_junglelevelmask)==COLOR_WALL) 			collision[COLLISION_BOTTOM_LEFT]=	1;
			if (CGL_GetPixel(x+25,y+64,bmp_junglelevelmask)==COLOR_WALL) 		collision[COLLISION_BOTTOM]=		1;
			if (CGL_GetPixel(x+50,y+64,bmp_junglelevelmask)==COLOR_WALL)		collision[COLLISION_BOTTOM_RIGHT]=	1;
			if (CGL_GetPixel(x+50,y+32,bmp_junglelevelmask)==COLOR_WALL) 		collision[COLLISION_MIDDLE_RIGHT]=	1;
			
			if (CGL_GetPixel(x,y+64,bmp_junglelevelmask)==COLOR_POISON) 		collision[COLLISION_BOTTOM_LEFT]=	2;
			if (CGL_GetPixel(x+25,y+64,bmp_junglelevelmask)==COLOR_POISON) 		collision[COLLISION_BOTTOM]=		2;
			if (CGL_GetPixel(x+50,y+64,bmp_junglelevelmask)==COLOR_POISON)		collision[COLLISION_BOTTOM_RIGHT]=	2;
			
			if (CGL_GetPixel(x,y+32,bmp_junglelevelmask)==COLOR_PATH) 			collision[COLLISION_MIDDLE_LEFT]=	3;
			if (CGL_GetPixel(x,y+64,bmp_junglelevelmask)==COLOR_PATH) 			collision[COLLISION_BOTTOM_LEFT]=	3;
			if (CGL_GetPixel(x+50,y+64,bmp_junglelevelmask)==COLOR_PATH)		collision[COLLISION_BOTTOM_RIGHT]=	3;
			if (CGL_GetPixel(x+50,y+32,bmp_junglelevelmask)==COLOR_PATH) 		collision[COLLISION_MIDDLE_RIGHT]=	3;
			
			if (CGL_GetPixel(x,y+32,bmp_junglelevelmask)==COLOR_ENDPATH) 		collision[COLLISION_MIDDLE_LEFT]=	4;
			if (CGL_GetPixel(x,y+64,bmp_junglelevelmask)==COLOR_ENDPATH) 		collision[COLLISION_BOTTOM_LEFT]=	4;
			if (CGL_GetPixel(x+50,y+64,bmp_junglelevelmask)==COLOR_ENDPATH)		collision[COLLISION_BOTTOM_RIGHT]=	4;
			if (CGL_GetPixel(x+50,y+32,bmp_junglelevelmask)==COLOR_ENDPATH)		collision[COLLISION_MIDDLE_RIGHT]=	4;
		}
		if(level==1)
		{
			if (CGL_GetPixel(x+25,y,bmp_citylevelmask)==COLOR_WALL) 		collision[COLLISION_TOP]=			1;
			if (CGL_GetPixel(x,y+32,bmp_citylevelmask)==COLOR_WALL) 		collision[COLLISION_MIDDLE_LEFT]=	1;
			if (CGL_GetPixel(x,y+64,bmp_citylevelmask)==COLOR_WALL) 		collision[COLLISION_BOTTOM_LEFT]=	1;
			if (CGL_GetPixel(x+25,y+64,bmp_citylevelmask)==COLOR_WALL) 		collision[COLLISION_BOTTOM]=		1;
			if (CGL_GetPixel(x+50,y+64,bmp_citylevelmask)==COLOR_WALL)		collision[COLLISION_BOTTOM_RIGHT]=	1;
			if (CGL_GetPixel(x+50,y+32,bmp_citylevelmask)==COLOR_WALL) 		collision[COLLISION_MIDDLE_RIGHT]=	1;
			
			if (CGL_GetPixel(x,y+64,bmp_citylevelmask)==COLOR_POISON) 		collision[COLLISION_BOTTOM_LEFT]=	2;
			if (CGL_GetPixel(x+25,y+64,bmp_citylevelmask)==COLOR_POISON) 	collision[COLLISION_BOTTOM]=		2;
			if (CGL_GetPixel(x+50,y+64,bmp_citylevelmask)==COLOR_POISON)	collision[COLLISION_BOTTOM_RIGHT]=	2;
			
			if (CGL_GetPixel(x,y+32,bmp_citylevelmask)==COLOR_PATH) 		collision[COLLISION_MIDDLE_LEFT]=	3;
			if (CGL_GetPixel(x,y+64,bmp_citylevelmask)==COLOR_PATH) 		collision[COLLISION_BOTTOM_LEFT]=	3;
			if (CGL_GetPixel(x+50,y+64,bmp_citylevelmask)==COLOR_PATH)		collision[COLLISION_BOTTOM_RIGHT]=	3;
			if (CGL_GetPixel(x+50,y+32,bmp_citylevelmask)==COLOR_PATH) 		collision[COLLISION_MIDDLE_RIGHT]=	3;
			
			if (CGL_GetPixel(x,y+32,bmp_citylevelmask)==COLOR_ENDPATH) 		collision[COLLISION_MIDDLE_LEFT]=	4;
			if (CGL_GetPixel(x,y+64,bmp_citylevelmask)==COLOR_ENDPATH) 		collision[COLLISION_BOTTOM_LEFT]=	4;
			if (CGL_GetPixel(x+50,y+64,bmp_citylevelmask)==COLOR_ENDPATH)	collision[COLLISION_BOTTOM_RIGHT]=	4;
			if (CGL_GetPixel(x+50,y+32,bmp_citylevelmask)==COLOR_ENDPATH) 	collision[COLLISION_MIDDLE_RIGHT]=	4;
		}
		
		gravity+=9;
		if (gravity>=200) gravity=200;
		if (collision[COLLISION_BOTTOM_LEFT]!=1 || collision[COLLISION_BOTTOM]!=1 || collision[COLLISION_BOTTOM_RIGHT]!=1) y+=gravity/10;
	
		for (int i=0;i<20;i++)
		{
			if (CGL_GetPixel(x-5,y-5,bmp_junglelevelmask)!=COLOR_WALL && CGL_GetPixel(x+55,y-5,bmp_junglelevelmask)!=COLOR_WALL)
			{
				if (CGL_GetPixel(x+width/2,y+63-i,bmp_junglelevelmask)==COLOR_WALL) y--;
			}
		}
	}
}
	
	
void c_enemy::Handle(int plrx)
{
	if (active)
	{
		x+=dx;
		
		
		if (dx>0) facing=1;
		else facing=0;
		if (dx!=0)
		{
			InitAnim(ANIM_WALK);
			if (plrx+400>x && plrx-400<x) if (step) 
			{
				Soundsystem_PlaySound(&snd_footsteps[rand() %3],0);
				step=0;
			}
		}
	
		if (step==0)
		{
			if (stepcount==16)
			{
				stepcount=0;									// FOOTSTEP COUNTER
				step=1;
			} else step=0;
			stepcount++;
		}
		
		
		if (type==CITY)
		{
			if (canshoot==0)
			{
				if (shootcount==32)
				{
					shootcount=0;								// PISTOL SHOT FREQUENCY COUNTER
					canshoot=1;
				} else canshoot=0;
				shootcount++;
			}
	
			if (canshoot) if (plrx+300>x && plrx-300<x) 
			{
				shoot=1;
			}
		}
		
		
		if (dx==0) dx=3;
		
		if (collision[COLLISION_BOTTOM_LEFT]==1 || collision[COLLISION_BOTTOM]==1 || collision[COLLISION_BOTTOM_RIGHT]==1) gravity=0;
		if (collision[COLLISION_BOTTOM_LEFT]==2 || collision[COLLISION_BOTTOM]==2 || collision[COLLISION_BOTTOM_RIGHT]==2) health=0;
		
		if ((collision[COLLISION_MIDDLE_RIGHT]==1)||(collision[COLLISION_MIDDLE_RIGHT]==4))
		{
			InitAnim(ANIM_WALK);
			dx=-3;
		}
		if ((collision[COLLISION_MIDDLE_LEFT]==1)||(collision[COLLISION_MIDDLE_LEFT]==4))
		{
			InitAnim(ANIM_WALK);
			dx=3;
		}
		
		if (collision[COLLISION_MIDDLE_RIGHT]==3 || collision[COLLISION_TOP_RIGHT]==3)
		{
			int numb=rand()%3;
			if(numb==1)dx=-3;
		}
		if (collision[COLLISION_MIDDLE_LEFT]==3 || collision[COLLISION_TOP_LEFT]==3)
		{
			int numb=rand()%3;
			if(numb==1)dx=3;
		}
	
		if (plrx+700>x && plrx-700<x) if (temphealth!=health)
		{
			Soundsystem_PlaySound(&snd_hurt[rand() %3],0);
			temphealth=health;
		}
			
		if (health<=0) active=false;
	}
}
