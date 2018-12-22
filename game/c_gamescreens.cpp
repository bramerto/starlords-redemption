
// ============================================================ INCLUDES =============================================================

#include "c_gamescreens.h"

// ============================================================== MAIN ==============================================================

void c_gamescreens::Title()
{
	int key,keytrig;
	
	CGL_DrawBitmap(0,0,bmp_titlebackground);
	
	CGL_DrawText(175,150,gametitlefont,"Starlord's");
	
	CGL_DrawText(625,150,gametitlefont,"Redemption");
	
	CGL_DrawText(10,10,menufont,"If the music does not sound right, please restart the game.");
	
	if (selected==0) if (textactive==1) CGL_DrawCenteredText(530,menufont,"Press [ENTER] to start");
	if (selected!=0) CGL_DrawCenteredText(530,menufont,"Press [ENTER] to start");
	
	if (godmode==0) CGL_DrawCenteredText(360,menufont,"God Mode is OFF");
	if (godmode==1) CGL_DrawCenteredText(360,menufont,"God Mode is ON");
	
	if (selected==1)
	{
		if (textactive==1)
		{
			CGL_DrawCenteredText(330,menufont,"Toggle God Mode with [ENTER]");
		}
	}
	else if (selected!=1)
	{
		CGL_DrawCenteredText(330,menufont,"Toggle God Mode with [ENTER]");
	}
	
	if (aspectratio==0) CGL_DrawCenteredText(430,menufont,"Aspect Ratio: 16:9");
	else if (aspectratio==1) CGL_DrawCenteredText(430,menufont,"Aspect Ratio: 16:10");
	else if (aspectratio==2) CGL_DrawCenteredText(430,menufont,"Aspect Ratio: 4:3");
	
	if (selected==2)
	{
		if (textactive==1)
		{
			CGL_DrawCenteredText(400,menufont,"Change the aspect ratio with [ENTER]");
		}
	}
	else if (selected!=2) 
	{
		CGL_DrawCenteredText(400,menufont,"Change the aspect ratio with [ENTER]");
	}
	
	CGL_DrawCenteredText(650,menufont,"Press [ESC] to exit the game");
	
    count++;
    if (count>24) textactive=1;
    if (count<24) textactive=0;
    if (count>40) count=0;
	
    CGL_GetKeys(&key,&keytrig);
	if (selected==0) 
	{
		if (keytrig & CGL_INPUT_KEYCODE_ENTER) gamescreen=1;
	}
	if (selected==1) 
	{
		if (keytrig & CGL_INPUT_KEYCODE_ENTER) godmode++;
	}
	if (selected==2) 
	{
		if (keytrig & CGL_INPUT_KEYCODE_ENTER) aspectratio++; 
	}
		if (keytrig & CGL_INPUT_KEY_EXIT) gameactive=0;
	
	if (keytrig & CGL_INPUT_KEY_UP) selected--;
	if (keytrig & CGL_INPUT_KEY_DOWN) selected++;
	
	if (selected>2) selected=0;
	if (selected<0) selected=2;
	
	if (godmode>1) godmode=0;
	if (aspectratio>2)  aspectratio=0;
}

void c_gamescreens::GameOver()
{
	int key,keytrig;
	
	CGL_DrawBitmap(0,0,bmp_titlebackground);
	
	CGL_DrawCenteredText(330,menufont,"Game Over. You lost!");
	if (textactive==1) CGL_DrawCenteredText(460,menufont,"Press [SPACE], [ENTER] or [BACKSPACE] to restart the game");
	CGL_DrawCenteredText(650,menufont,"Press [ESC] to exit the game");
	
	count++;
    if (count>48) textactive=1;
    if (count<48) textactive=0;
    
    if (count>80) count=0;
	
    CGL_GetKeys(&key,&keytrig);
	if (keytrig & CGL_INPUT_KEYCODE_ENTER) gamescreen=0;
	if (keytrig & CGL_INPUT_KEY_EXIT) gameactive=0;
}

void c_gamescreens::Win()
{
	int key,keytrig;
	
	CGL_DrawBitmap(0,0,bmp_titlebackground);
	
	CGL_DrawCenteredText(330,menufont,"Game Over. You win!");
	if (textactive==1) CGL_DrawCenteredText(460,menufont,"Press [SPACE], [ENTER], or [BACKSPACE] to restart the game");
	CGL_DrawCenteredText(650,menufont,"Press [ESC] to exit the game");
	
	count++;
    if (count>48) textactive=1;
    if (count<48) textactive=0;
    
    if (count>80) count=0; 
	
    CGL_GetKeys(&key,&keytrig);
	if (keytrig & CGL_INPUT_KEYCODE_ENTER) gamescreen=0;
	if (keytrig & CGL_INPUT_KEY_EXIT) gameactive=0;
}
