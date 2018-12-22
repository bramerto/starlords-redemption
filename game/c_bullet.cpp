#include "c_bullet.h"

void c_bullet::Init(int posx,int posy,int destx,int desty,int weapon)
{
	x=posx;
	y=posy;
	dx=destx;
	dy=desty;
	speed=25;
	active=true;
	pdamage=rand() %25+15;
	edamage=rand() %7+3;
	
	weapon=WEAPON_ASSAULT;
	
	if (x<dx) facing=1;
	if (x>dx) facing=0;
		
	angle=atan2(-(dx-x),dy-y);
}

void c_bullet:: Draw()
{
	if (active) 
	{
		if (weapon==WEAPON_PISTOL)
		{
			if (facing) CGL_DrawRotatedSprite(x-screenx,y-screeny,spr_pistolbullet,angle*180/pi+90);
			else CGL_DrawRotatedSprite(x-screenx,y-screeny,spr_pistolbullet,angle*180/pi+90);
		}
		else if (weapon==WEAPON_ASSAULT)
		{
			if (facing) CGL_DrawRotatedSprite(x-screenx,y-screeny,spr_assaultbullet,angle*180/pi+90);
			else CGL_DrawRotatedSprite(x-screenx,y-screeny,spr_assaultbullet,angle*180/pi+90);
		}
	}
}

void c_bullet::Handle()
{
	if (active)
	{
		x-=sin(angle)*speed;
		y+=cos(angle)*speed;
		
		
		if (level==0) 
		{
			collision[0]=CGL_GetPixel(x,y+3,bmp_junglelevelmask);
			collision[1]=CGL_GetPixel(x+32,y+3,bmp_junglelevelmask);
		}
		if (level==1)
		{
			collision[0]=CGL_GetPixel(x,y+3,bmp_citylevelmask);
			collision[1]=CGL_GetPixel(x+32,y+3,bmp_citylevelmask);
		}
		
		if (collision[0]==COLOR_WALL || collision[1]==COLOR_WALL) active=false;
		
		
		if (x<0) active=false;
		if (x>6336) active=false;
		if (y<0) active=false;
		if (y>1536) active=false;
	}
}
