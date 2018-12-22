// =========================================================================== INCLUDES ===========================================================================

#include <stdio.h>
#include <stdlib.h>
#include <cgl/cgl.h>
#include <cgl/core.h>
#include <core/corefile.h>
#include <coresound/coresound.h>
#include <iostream>
#include <conio.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

#include "c_player.h"
#include "c_enemy.h"
#include "c_gamescreens.h"
#include "c_pickup.h"
#include "c_bullet.h"

#define MAXENEMIES 30
#define MAXPICKUPS 31

c_enemy enemy[MAXENEMIES];
c_player player;
c_pickup pickup[MAXPICKUPS];
c_gamescreens gamescreens;
c_bullet pbullet[MAXBULLETS];
c_bullet ebullet[MAXBULLETS];

int gameactive,currentframe,count[3];
int screenx,screeny,mx,my,mb;
int tmpaspectratio;
int level, templevel;
int enemybulletcount;
bool debugactive;

s_sprite spr_crosshair;
s_sprite spr_player[MAXPFRAMES];

s_sprite spr_enemycity[MAXEFRAMES];
s_sprite spr_enemyjungle[MAXEFRAMES];

s_sprite spr_pistolbullet;
s_sprite spr_assaultbullet;

s_sprite spr_weapon_pistol;
s_sprite spr_weapon_pistolm;
s_sprite spr_weapon_assault;
s_sprite spr_weapon_assaultm;
s_sprite spr_weapon_dagger;
s_sprite spr_weapon_daggerm;

s_sprite spr_healthbar;
s_sprite spr_healthbarborder;
s_sprite spr_playerhealthbar;
s_sprite spr_playerhealthbarborder;
s_sprite spr_life;
s_sprite spr_hud;

s_sprite spr_key[MAXPICKFRAMES];
s_sprite spr_coin[MAXPICKFRAMES];

s_bitmap bmp_titlebackground;
s_bitmap bmp_gamebackground;
s_bitmap bmp_junglelevelmask;
s_bitmap bmp_junglelevel;
s_bitmap bmp_citylevelmask;
s_bitmap bmp_citylevel;

s_sound snd_titlesong;
s_sound snd_weapon_pistol;
s_sound snd_weapon_assault;
s_sound snd_footsteps[3];
s_sound snd_hurt[3];
s_sound snd_pickup_coin;
s_sound snd_pickup_key;

s_font menufont;
s_font gamefont;
s_font gametitlefont;

// ====================================================================== PRE-GAME FUNCTIONS ======================================================================

void LoadData()
{
    s_bitmap playerspritebmp, enemyjunglespritebmp, enemycityspritebmp, pickupcoinbmp, pickupkeybmp;
    int numtiles, x, y;
    
    CGL_LoadBitmap("Graphics/Misc/titlebackground.tga",&bmp_titlebackground);
    CGL_LoadBitmap("Graphics/Levels/junglelevelmask.tga",&bmp_junglelevelmask);
    CGL_LoadBitmap("Graphics/Levels/citylevelmask.tga",&bmp_citylevelmask);					// LOAD BACKGROUND IMAGES
    CGL_LoadBitmap("Graphics/Levels/junglelevel.tga",&bmp_junglelevel);
    CGL_LoadBitmap("Graphics/Levels/citylevel.tga",&bmp_citylevel);
    
    CGL_LoadBitmap("Graphics/Player/player.tga",&playerspritebmp);
    CGL_LoadBitmap("Graphics/Enemy/enemy_jungle.tga",&enemyjunglespritebmp);
    CGL_LoadBitmap("Graphics/Enemy/enemy_city.tga",&enemycityspritebmp);					// LOAD ENTITY IMAGES
    CGL_LoadBitmap("Graphics/Pickup/pickup_key.tga",&pickupkeybmp);
    CGL_LoadBitmap("Graphics/Pickup/pickup_coin.tga",&pickupcoinbmp);
    
    CGL_LoadSprite("Graphics/Player/weapon_pistol.tga",&spr_weapon_pistol);	
    CGL_LoadSprite("Graphics/Player/weapon_pistolm.tga",&spr_weapon_pistolm);
    CGL_LoadSprite("Graphics/Player/weapon_assault.tga",&spr_weapon_assault);				//LOAD WEAPONS
    CGL_LoadSprite("Graphics/Player/weapon_assaultm.tga",&spr_weapon_assaultm);
    CGL_LoadSprite("Graphics/Player/weapon_dagger.tga",&spr_weapon_dagger);
    CGL_LoadSprite("Graphics/Player/weapon_daggerm.tga",&spr_weapon_daggerm);
	
	CGL_LoadSprite("Graphics/Misc/pistolbullet.tga",&spr_pistolbullet);
	CGL_LoadSprite("Graphics/Misc/assaultbullet.tga",&spr_assaultbullet);
	CGL_LoadSprite("Graphics/Misc/crosshair.tga",&spr_crosshair);
	CGL_LoadSprite("Graphics/Misc/healthbar.tga",&spr_healthbar);							// LOAD MISCELLANEOUS SPRITES
	CGL_LoadSprite("Graphics/Misc/healthbarborder.tga",&spr_healthbarborder);
	CGL_LoadSprite("Graphics/Misc/playerhealthbar.tga",&spr_playerhealthbar);
	CGL_LoadSprite("Graphics/Misc/playerhealthbarborder.tga",&spr_playerhealthbarborder);
	CGL_LoadSprite("Graphics/Misc/life.tga",&spr_life);
	CGL_LoadSprite("Graphics/Misc/hud.tga",&spr_hud);
    
    CGL_InitFont("Fonts/menufont.tga",&menufont);	
    CGL_InitFont("Fonts/gamefont.tga",&gamefont);											// LOAD FONTS
    CGL_InitFont("Fonts/gametitlefont.tga",&gametitlefont);
    
	Soundsystem_LoadSound("Sounds/Misc/titlesong.wav",&snd_titlesong);
	Soundsystem_LoadSound("Sounds/Misc/weapon_pistol.wav",&snd_weapon_pistol);
	Soundsystem_LoadSound("Sounds/Misc/weapon_assault.wav",&snd_weapon_assault);
	Soundsystem_LoadSound("Sounds/Player/footsteps1.wav",&snd_footsteps[0]);
	Soundsystem_LoadSound("Sounds/Player/footsteps2.wav",&snd_footsteps[1]);
	Soundsystem_LoadSound("Sounds/Player/footsteps3.wav",&snd_footsteps[2]);				// LOAD SOUNDS
	Soundsystem_LoadSound("Sounds/Player/hurt1.wav",&snd_hurt[0]);
	Soundsystem_LoadSound("Sounds/Player/hurt2.wav",&snd_hurt[1]);
	Soundsystem_LoadSound("Sounds/Player/hurt3.wav",&snd_hurt[2]);
	Soundsystem_LoadSound("Sounds/Misc/pickup_coin.wav",&snd_pickup_coin);
	Soundsystem_LoadSound("Sounds/Misc/pickup_key.wav",&snd_pickup_key);
	
    for (int i=0;i<MAXPFRAMES;i++)
	{
        CGL_GetSprite(i*50,0,50,64,playerspritebmp,&spr_player[i]);
    }
    for (int i=0;i<MAXEFRAMES;i++)
    {
        CGL_GetSprite(i*52,0,52,64,enemyjunglespritebmp,&spr_enemyjungle[i]);				// GET SPRITES FROM PAGE
        CGL_GetSprite(i*44,0,44,64,enemycityspritebmp,&spr_enemycity[i]);
    }
    
    printf("Done!");
    for (int i=0;i<MAXPICKFRAMES;i++)
    {
        CGL_GetSprite(i*32,0,32,32,pickupcoinbmp,&spr_coin[i]);
        CGL_GetSprite(i*48,0,48,48,pickupkeybmp,&spr_key[i]);
    }
}

void InitGame()
{
	corefile_mountimage("data",MOUNT_DIR);
	
//	if (gamescreens.aspectratio==0) CGL_InitVideo(1280,720,CGL_VIDEO_NONE);
//	if (gamescreens.aspectratio==1) CGL_InitVideo(1280,960,CGL_VIDEO_NONE); 				// CHECK ASPECT RATIO		
//	if (gamescreens.aspectratio==2) CGL_InitVideo(1280,800,CGL_VIDEO_NONE);
	
	
	if (gamescreens.aspectratio==0) CGL_InitVideo(1280,720,CGL_VIDEO_FULLSCREEN);
	if (gamescreens.aspectratio==1) CGL_InitVideo(1280,960,CGL_VIDEO_FULLSCREEN); 	
	if (gamescreens.aspectratio==2) CGL_InitVideo(1280,800,CGL_VIDEO_FULLSCREEN);
	
	
	Soundsystem_Init(KHZ_44,16,CORESOUND_STEREO);
	
    CGL_SetTitle("Starlord's Redemption");
    
    LoadData();
    
//	Soundsystem_PlaySound(&snd_titlesong,1);
	
	gameactive=1;
	level=0;
	templevel=0;
	player.point=0;
	debugactive=false;
}

// ======================================================================= INGAME FUNCTIONS =======================================================================

void DrawBackground()
{
	if(level==0)
	{
		CGL_DrawBitmap(-screenx,-screeny,bmp_junglelevelmask);
		CGL_DrawBitmap(-screenx,-screeny,bmp_junglelevel);
	}
	else if(level==1)
	{
		CGL_DrawBitmap(-screenx,-screeny,bmp_citylevelmask);
		CGL_DrawBitmap(-screenx,-screeny,bmp_citylevel);
	}
	
	screenx=player.x-608;
	screeny=player.y-328;
	
	if (screenx<0) screenx=0;
	if (screenx>5120) screenx=5120;
	if (screeny<0) screeny=0;
	if (gamescreens.aspectratio==0)	if (screeny>816) screeny=816;
	if (gamescreens.aspectratio==1)	if (screeny>576) screeny=576;
	if (gamescreens.aspectratio==2)	if (screeny>736) screeny=736;
}

void Init()
{
	srand(time(NULL));
	CGL_InitControllers();
	
	player.lives=3;
	player.Init();
	if(level==0)
	{
		for(int c1=0;c1<3;c1++)pickup[c1].Init(2830+(c1*50),150-(c1*40),COIN);
		for(int c2=2;c2<6;c2++)pickup[c2].Init(4050+((c2-2)*50),315-(c2*50),COIN);
		for(int c3=6;c3<11;c3++)pickup[c3].Init(4600+((c3-6)*50), 960, COIN);
		for(int c4=11;c4<16;c4++)pickup[c4].Init(4700+((c4-11)*50), 1400, COIN);
		pickup[16].Init(985,530,COIN);
		pickup[17].Init(1050,580,COIN);
		pickup[18].Init(1125,660,COIN);
		pickup[19].Init(3735,520,COIN);
		pickup[20].Init(5790,680,COIN);
		pickup[21].Init(5660,830,COIN);
		
		enemy[0].Init(900, 430, JUNGLE);
		enemy[1].Init(530, 580, JUNGLE);
		enemy[2].Init(4700, 950, JUNGLE);
		enemy[3].Init(5300, 950, JUNGLE);
		enemy[4].Init(4870, 1380, JUNGLE);
		enemy[5].Init(5400, 1380, JUNGLE);
		enemy[6].Init(3640, 570, JUNGLE);
		
	}
	else if(level==1)
	{
		for(int c1=1;c1<6;c1++)pickup[c1].Init(1400+(c1-1*50), 660, COIN);
		for(int c2=6;c2<12;c2++)pickup[c2].Init(2600+((c2-6)*50), 660, COIN);
		for(int c3=12;c3<18;c3++)pickup[c3].Init(3200+((c3-12)*50), 990, COIN);
		for(int c4=18;c4<24;c4++)pickup[c4].Init(4800+((c4-18)*50), 990, COIN);
		for(int c5=24;c5<30;c5++)pickup[c5].Init(3000+((c5-24)*50), 1300, COIN);
		
		pickup[30].Init(4500,480,ASSAULT);
		
		
		pickup[0].Init(3785, 1280,KEY);
		
		for(int e1=0;e1<6;e1++)enemy[e1].Init(1400+(e1*600), 630, CITY);
		for(int e2=6;e2<14;e2++)enemy[e2].Init(2500+((e2-6)*600), 960, CITY);
		
		enemy[14].Init(2450, 1300, CITY);
		enemy[15].Init(2800, 1300, CITY);
		enemy[16].Init(3400, 1300, CITY);
		
	}
}

void DrawHUD()
{
	CGL_DrawSprite(0,0,spr_hud);
	for (int t=0;t<player.health/2*3;t++) CGL_DrawSprite(21+t,16,spr_playerhealthbar);
	CGL_DrawSprite(15,10,spr_playerhealthbarborder);
	for (int t=0;t<player.lives;t++) CGL_DrawSprite(18+55*t,70,spr_life);
	if (player.key) CGL_DrawSprite(15,145,spr_key[pickup[0].animframe]);
	
	CGL_DrawText(80,20,gamefont,"%d",player.health);
	//CGL_DrawText(120,120,gamefont,"Ammo: %d",player.ammo);
	CGL_DrawText(15,120,gamefont,"Points: %d",player.point);
}

void Draw()
{
	player.Draw();
	
	for(int p=0;p<MAXPICKUPS;p++)pickup[p].Draw();
	for(int e=0;e<MAXENEMIES;e++)enemy[e].Draw(player.x,player.y);
	
	for (int t=0;t<MAXBULLETS;t++) 
	{
		if (pbullet[t].active) pbullet[t].Draw();
		if (ebullet[t].active) ebullet[t].Draw();
	}
	
	DrawHUD();
	
	CGL_DrawSprite(mx-screenx,my-screeny,spr_crosshair);
}

void HandleBullets()
{
	if (player.shoot) 
	{
		if (pbullet[player.bulletcount].active==0) 
		{
			pbullet[player.bulletcount].Init(player.x+20,player.y+32,mx+16,my+16,player.weapon);
			player.bulletcount++;
			player.ammo=MAXBULLETS-player.bulletcount;
			player.canshoot=0;
			player.shoot=0;
			if (player.weapon==WEAPON_PISTOL) Soundsystem_PlaySound(&snd_weapon_pistol,0);
			if (player.weapon==WEAPON_ASSAULT) Soundsystem_PlaySound(&snd_weapon_assault,0);
		}
	}
	
	if (player.bulletcount>MAXBULLETS-1)
	{
		//canshoot=0;
		player.bulletcount=0;
	}
	
	
	for (int t=0;t<MAXENEMIES;t++)
	{
		if (enemy[t].shoot)
		{
			if (ebullet[enemybulletcount].active==0) 
			{
				ebullet[enemybulletcount].Init(enemy[t].x+20,enemy[t].y+32,player.x+25,player.y+32,WEAPON_PISTOL);
				enemybulletcount++;
				enemy[t].canshoot=0;
				enemy[t].shoot=0;
				Soundsystem_PlaySound(&snd_weapon_pistol,0);
			}
		}
	}
	
	
	for (int t=0;t<MAXBULLETS;t++) 
	{
		pbullet[t].Handle();
		ebullet[t].Handle();
		
		for (int i=0;i<MAXENEMIES;i++)
		{
			if (enemy[i].active)
			{
				if (pbullet[t].active)
				{
					if (pbullet[t].weapon==WEAPON_PISTOL)
					{
						if (CGL_CheckBoxCollision(pbullet[t].x,pbullet[t].y,32,6,enemy[i].x,enemy[i].y,52,64)) 
						{
							enemy[i].health-=pbullet[t].pdamage;
							pbullet[t].active=false;
						}
					}
					if (pbullet[t].weapon==WEAPON_ASSAULT)
					{
						if (CGL_CheckBoxCollision(pbullet[t].x,pbullet[t].y,32,6,enemy[i].x,enemy[i].y,52,64)) 
						{
							enemy[i].health-=pbullet[t].pdamage;
							pbullet[t].active=false;
						}
					}
				}
				if (ebullet[t].active)
				{
					if (ebullet[t].weapon==WEAPON_PISTOL)
					{
						if (CGL_CheckBoxCollision(ebullet[t].x,ebullet[t].y,32,6,player.x,player.y,52,64)) 
						{
							player.health-=ebullet[t].edamage;
							ebullet[t].active=false;
						}
					}
					if (ebullet[t].weapon==WEAPON_ASSAULT)
					{
						if (CGL_CheckBoxCollision(ebullet[t].x,ebullet[t].y,214,6,player.x,player.y,52,64)) 
						{
							player.health-=ebullet[t].edamage;
							ebullet[t].active=false;
						}
					}
				}
			}
		}
	}
	if(enemybulletcount>49)enemybulletcount=0;
}

void Handle()
{
	CGL_GetMouse(&mx,&my,&mb);
	
	mx+=screenx; my+=screeny;
	
	player.HandleInteraction(&gamescreens);
	player.Handle(&gamescreens,mb);
	
	for(int e=0;e<MAXENEMIES;e++)
	{
		enemy[e].HandleInteraction();
		enemy[e].Handle(player.x);
	}
	for(int p=0;p<MAXPICKUPS;p++)pickup[p].Handle();
		
	if (player.respawn) player.Init();
	
	for (int t=0;t<MAXENEMIES;t++) if(enemy[t].type==JUNGLE) if(CGL_CheckBoxCollision(player.x, player.y, 50, 64, enemy[t].x, enemy[t].y, 50, 64)) player.health--;
	
	HandleBullets();	
}
void HandleLevel()
{
	if(level!=templevel)
	{
		Init();
		
		templevel=level;
	}
}

void Timer()
{
	currentframe++;
	
	if (currentframe==64) {currentframe=0; count[0]++;}
	if (count[0]==60) {count[0]=0; count[1]++;}
	if (count[1]==60) {count[1]=0; count[2]++;}
	
	CGL_DrawCenteredText(10,gamefont,"%d:%d:%d",count[2],count[1],count[0]);
}

void Debug()
{
	CGL_DrawText(10,10,gamefont,"Player X %d",player.x);
	CGL_DrawText(10,30,gamefont,"Player Y %d",player.y);
	CGL_DrawText(10,50,gamefont,"MX %d",mx);
	CGL_DrawText(10,70,gamefont,"MY %d",my);
	
	CGL_DrawText(10,110,gamefont,"Jump: %d",player.jump);
	CGL_DrawText(10,130,gamefont,"Gravity: %d",player.gravity);
	
	CGL_DrawText(100,200,gamefont,"%d %d",mx,my);
	
	for(int t=0;t<8;t++) CGL_DrawText(1000,10+(20*t),gamefont,"Collision [%d] %d",t,player.collision[t]);
	
	CGL_DrawText(10,700,gamefont,"%d",CGL_GetFPS());
}


// ============================================================================ MAIN ===============================================================================

void coremain()
{	
    InitGame();
   	Init();
	
	while (gameactive==1)
	{
    	CGL_WaitRefresh();
    	
		if (gamescreens.gamescreen==0) 											// SET GAMESCREEN TO THE MAIN MENU
		{
			gamescreens.Title();
			if (gameactive!=0)
			{
				Init();
				if (gamescreens.aspectratio!=tmpaspectratio)
				{
					CGL_CloseVideo();
					InitGame();
				}
				tmpaspectratio=gamescreens.aspectratio;
			}
		}
		if (gamescreens.gamescreen==1)											// SET GAMESCREEN TO THE GAME
		{
			HandleLevel();			
			DrawBackground();			// DRAW BACKGROUND
	    	
	    	if(debugactive)Debug();		// DRAW DEBUG
			
	    	Draw();						// DRAW CLASSES
	    	
	    	Handle();					// HANDLE CLASSES
			
			CGL_PollControllers();		// RESET CONTROLS
	    	
	    	Timer();					// HANDLE TIMER
		}
		if (gamescreens.gamescreen==2) 
		{
			Init();
			gamescreens.GameOver();												// SET GAMESCREEN TO GAMEOVER
		}
		if (gamescreens.gamescreen==3) gamescreens.Win();						// SET GAMESCREEN TO WIN
    	
    	CGL_SwapBuffers();
    }
    CGL_CloseVideo();
}   
