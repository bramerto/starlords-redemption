#include "c_player.h"

void c_player::InitAnim(int animnr)
{
	if (animnr!=currentanim)
	{
		currentanim=animnr;
		animframe=anim[currentanim].startframe;
		animcount=0;
    }
}

void c_player::Init()
{
	if(level==0){x=100; y=400;}
	else if(level==1){x=200; y=200;}
	speed=6;
	health=100;
	temphealth=100;
	respawn=false;
	weapon=WEAPON_PISTOL;
	
	// INITIALIZE ANIMATIONS
	anim[0].startframe=0; anim[0].endframe=1; anim[0].delay=50; anim[0].loop=1;
	anim[1].startframe=1; anim[1].endframe=4; anim[1].delay=5; anim[1].loop=1;
}

void c_player::Draw()
{
	// DRAW PLAYER SPRITES
	if (facing) CGL_DrawSprite(x-screenx,y-screeny,spr_player[animframe]);
	else CGL_DrawMirroredSprite(x-screenx,y-screeny,spr_player[animframe]);
	
	angle=atan2(-(mx-x),my-y);
	
	if (weapon==WEAPON_PISTOL)
	{
		if (facing) CGL_DrawRotatedSprite(x-5-screenx,y+32-screeny,spr_weapon_pistol,angle*180/pi+90);
		else CGL_DrawRotatedSprite(x-5-screenx,y+32-screeny,spr_weapon_pistolm,angle*180/pi+270);
	}
	else
	{
		if (facing) CGL_DrawRotatedSprite(x-50-screenx,y+32-screeny,spr_weapon_assault,angle*180/pi+90);
		else CGL_DrawRotatedSprite(x-50-screenx,y+32-screeny,spr_weapon_assaultm,angle*180/pi+270);
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

void c_player::HandleInteraction(c_gamescreens *gamescreens)
{
	for (int t=0;t<8;t++) collision[t]=0;
	
    
	if (level==0)
	{
		if (CGL_GetPixel(x+25,y,bmp_junglelevelmask)==COLOR_WALL) 		collision[COLLISION_TOP]=			1;
		if (CGL_GetPixel(x+8,y,bmp_junglelevelmask)==COLOR_WALL) 		collision[COLLISION_TOP_LEFT]=		1;
		if (CGL_GetPixel(x,y+32,bmp_junglelevelmask)==COLOR_WALL) 		collision[COLLISION_MIDDLE_LEFT]=	1;
		if (CGL_GetPixel(x+8,y+64,bmp_junglelevelmask)==COLOR_WALL) 	collision[COLLISION_BOTTOM_LEFT]=	1;
		if (CGL_GetPixel(x+25,y+64,bmp_junglelevelmask)==COLOR_WALL) 	collision[COLLISION_BOTTOM]=		1;
		if (CGL_GetPixel(x+36,y+64,bmp_junglelevelmask)==COLOR_WALL)	collision[COLLISION_BOTTOM_RIGHT]=	1;
		if (CGL_GetPixel(x+50,y+32,bmp_junglelevelmask)==COLOR_WALL) 	collision[COLLISION_MIDDLE_RIGHT]=	1;
		if (CGL_GetPixel(x+36,y,bmp_junglelevelmask)==COLOR_WALL) 		collision[COLLISION_TOP_RIGHT]=		1;
		
		
		if (CGL_GetPixel(x,y+64,bmp_junglelevelmask)==COLOR_POISON) 	collision[COLLISION_BOTTOM_LEFT]=	2;
		if (CGL_GetPixel(x+25,y+64,bmp_junglelevelmask)==COLOR_POISON) 	collision[COLLISION_BOTTOM]=		2;
		if (CGL_GetPixel(x+36,y+64,bmp_junglelevelmask)==COLOR_POISON)	collision[COLLISION_BOTTOM_RIGHT]=	2;
		
		
		if (CGL_GetPixel(x+25,y,bmp_junglelevelmask)==COLOR_LADDER) 	collision[COLLISION_TOP]=			3;
		if (CGL_GetPixel(x+25,y+50,bmp_junglelevelmask)==COLOR_LADDER) 	collision[COLLISION_BOTTOM]=		3;
		
		
		for (int i=0;i<20;i++)
		{
			if (CGL_GetPixel(x-5,y-5,bmp_junglelevelmask)!=COLOR_WALL && CGL_GetPixel(x+55,y-5,bmp_junglelevelmask)!=COLOR_WALL)
			{
				if (CGL_GetPixel(x+8,y+63-i,bmp_junglelevelmask)==COLOR_WALL) 	y--;
				if (CGL_GetPixel(x+36,y+63-i,bmp_junglelevelmask)==COLOR_WALL)	y--;
			}
		}
	}
	
	if (level==1)
	{
		if (CGL_GetPixel(x+25,y,bmp_citylevelmask)==COLOR_WALL) 		collision[COLLISION_TOP]=			1;
		if (CGL_GetPixel(x+8,y,bmp_citylevelmask)==COLOR_WALL) 			collision[COLLISION_TOP_LEFT]=		1;
		if (CGL_GetPixel(x,y+32,bmp_citylevelmask)==COLOR_WALL) 		collision[COLLISION_MIDDLE_LEFT]=	1;
		if (CGL_GetPixel(x+8,y+64,bmp_citylevelmask)==COLOR_WALL) 		collision[COLLISION_BOTTOM_LEFT]=	1;
		if (CGL_GetPixel(x+25,y+64,bmp_citylevelmask)==COLOR_WALL) 		collision[COLLISION_BOTTOM]=		1;
		if (CGL_GetPixel(x+36,y+64,bmp_citylevelmask)==COLOR_WALL)		collision[COLLISION_BOTTOM_RIGHT]=	1;
		if (CGL_GetPixel(x+50,y+32,bmp_citylevelmask)==COLOR_WALL) 		collision[COLLISION_MIDDLE_RIGHT]=	1;
		if (CGL_GetPixel(x+36,y,bmp_citylevelmask)==COLOR_WALL) 		collision[COLLISION_TOP_RIGHT]=		1;
		
		
		if (CGL_GetPixel(x,y+64,bmp_citylevelmask)==COLOR_POISON) 		collision[COLLISION_BOTTOM_LEFT]=	2;
		if (CGL_GetPixel(x+25,y+64,bmp_citylevelmask)==COLOR_POISON) 	collision[COLLISION_BOTTOM]=		2;
		if (CGL_GetPixel(x+36,y+64,bmp_citylevelmask)==COLOR_POISON)	collision[COLLISION_BOTTOM_RIGHT]=	2;
		
		
		if (CGL_GetPixel(x+25,y,bmp_citylevelmask)==COLOR_LADDER) 		collision[COLLISION_TOP]=			3;
		if (CGL_GetPixel(x+25,y+50,bmp_citylevelmask)==COLOR_LADDER) 	collision[COLLISION_BOTTOM]=		3;
		
		
		if (CGL_GetPixel(x+25,y,bmp_citylevelmask)==COLOR_DOOR) 		collision[COLLISION_TOP]=			4;
		if (CGL_GetPixel(x+25,y+50,bmp_citylevelmask)==COLOR_DOOR) 		collision[COLLISION_BOTTOM]=		4;
		
		
		for (int i=0;i<20;i++)
		{
			if (CGL_GetPixel(x-5,y-5,bmp_citylevelmask)!=COLOR_WALL && CGL_GetPixel(x+55,y-5,bmp_citylevelmask)!=COLOR_WALL)
			{
				if (CGL_GetPixel(x+8,y+63-i,bmp_citylevelmask)==COLOR_WALL) 	y--;
				if (CGL_GetPixel(x+36,y+63-i,bmp_citylevelmask)==COLOR_WALL)	y--;
			}
		}
	}

	
	gravity+=9;
	if (gravity>=200) gravity=200;
	if (collision[COLLISION_TOP]!=3 || collision[COLLISION_BOTTOM]!=3) y+=gravity/10;

	//											COLLISION EVENTS
	
	if (key) if (collision[COLLISION_TOP]==4 || collision[COLLISION_BOTTOM]==4) gamescreens->gamescreen=3;
	
	if (collision[COLLISION_BOTTOM_LEFT] ||collision[COLLISION_BOTTOM] || collision[COLLISION_BOTTOM_RIGHT]) 
	{
		if (gravity>0) gravity=0;
		jump=1;
	}
	else jump=0;
	
	if (collision[COLLISION_TOP_LEFT] || collision[COLLISION_TOP] || collision[COLLISION_TOP_RIGHT]) 
	{
		if (gravity<0) gravity=0;
	}
	
	if (collision[COLLISION_BOTTOM_LEFT]==2 ||collision[COLLISION_BOTTOM]==2 || collision[COLLISION_BOTTOM_RIGHT]==2)
	{
		if (gamescreens->godmode==0) 
		{
			health=0;
		}
	}
}

void c_player::Handle(c_gamescreens *gamescreens,int mousebtn)
{
	int key,keytrig;
	CGL_GetKeys(&key,&keytrig);
	
	if (CGL_controller[5].connected)
	{
		if (CGL_controller[5].y==0 && CGL_controller[5].x==0)	// IDLE
		{
			if (key==0 && keytrig==0)
			{
				InitAnim(ANIM_IDLE);
			}
		}
		if (CGL_controller[5].y<0)							// UP 		(W)
		{
			if (collision[COLLISION_TOP]==3 || collision[COLLISION_BOTTOM]==3)
			{
				y-=speed;
				gravity=0;
			}
			if (jump==1) gravity=-220;
		}
		if (CGL_controller[5].x<0)							// LEFT 	(A)
		{
			if (collision[COLLISION_MIDDLE_LEFT]!=1)
			{
		    	x-=speed;
				InitAnim(ANIM_WALK);
				if (jump==1)
				{
					if (step) 
					{
						int t=rand() %3;
						Soundsystem_PlaySound(&snd_footsteps[t],0);
						step=0;
					}
				}
			}
		}
		if (CGL_controller[5].y>0)	 						// DOWN 	(S)
		{
			if (collision[COLLISION_TOP]==3 || collision[COLLISION_BOTTOM]==3)
			{
				y+=speed;
			}
		}
		if (CGL_controller[5].x>0)							// RIGHT 	(D)
		{
			if (collision[COLLISION_MIDDLE_RIGHT]!=1)
			{
		    	x+=speed;
				InitAnim(ANIM_WALK);
				if (jump==1)
				{
					if (step) 
					{
						Soundsystem_PlaySound(&snd_footsteps[rand() %3],0);
						step=0;
					}
				}
			}
		}
	}
	if (key && CGL_INPUT_KEYCODE_SPACE)
	{
		if (jump==1) gravity=-220;
	}
	if (key & CGL_INPUT_KEY_EXIT)							// ESCAPE KEY
	{
		gamescreens->gamescreen=0;
	}	
    if (mousebtn & CGL_INPUT_MOUSEBUTTON_LEFT)				// LEFT MOUSE BUTTON
	{
		if (canshoot)
		{
			shoot=1;
		} else shoot=0;
	}
	
	if (canshoot==0)
	{
		if (weapon==WEAPON_PISTOL)							// SET PISTOL SHOT FREQUENCY
		{
			if (shootcount>=32)
			{
				shootcount=0;								// PISTOL SHOT FREQUENCY COUNTER
				canshoot=1;
			} else canshoot=0;
		}
		else if (weapon==WEAPON_ASSAULT)					// SET ASSAULT SHOT FREQUENCY COUNTER
		{
			if (shootcount>=8)
			{
				shootcount=0;								// ASSAULT SHOT FREQUENCY COUNTER
				canshoot=1;
			} else canshoot=0;
		}
		shootcount++;
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
	
	if (temphealth!=health)
	{
		Soundsystem_PlaySound(&snd_hurt[rand() %3],0);
		temphealth=health;
	}
	
	if (health<=0) 
	{
		lives--;
		if(lives>0)
		{
			health=100;
			respawn=true;
		}
	}
	if (lives==0)
	{
		if (health<=0) 
		{
			gamescreens->gamescreen=2;
		}
	}
	
	if (x<0) x=0;
	if (y<0) y=0;
	if (x>6350) x=6350;
	
	if (level==0 && x==6350) level=1;
	if (level==1 && x==0) level=0;
	
	if (x+25<mx+16) facing=1;
	if (x+25>mx+16) facing=0;
}
