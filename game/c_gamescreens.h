#ifndef _GAMESCREENS_H_
#define _GAMESCREENS_H_

// ============================================================ INCLUDES =============================================================

#include <cgl/cgl.h>
#include <core/corefile.h>
#include <cgl/core.h>
#include <coresound/coresound.h>

#include <stdlib.h>

// ============================================================== MAIN ==============================================================

extern s_bitmap bmp_titlebackground;
extern s_font menufont,gametitlefont;
extern int gameactive;

class c_gamescreens
{
	public:
	
	int gamescreen,textactive,aspectratio,godmode,count,selected;
	
	void Title();
	void Win();
	void GameOver();
};

#endif
