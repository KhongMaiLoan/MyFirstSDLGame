
#ifndef COMMON_FUNCTION_H_
#define COMMON_FUNCTION_H_

#include <Windows.h>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <SDL_ttf.h>
#include<sstream>
#define GA_FAILED -1
#define GA_SUCCESS 0;

//Screen
const int WIDTH_BACKGROUND  = 4800;
const int HEIGHT_BACKGROUND = 600;
const int SCREEN_WIDTH      = 1200;
const int SCREEN_HEIGHT     = 560;
const int SCREEN_BPP        = 32;
const int SPEED_SCREEN      = 2;

//Main
const int POS_X_START_MAIN_OBJ  = SCREEN_WIDTH/2;
const int POS_Y_START_MAIN_OBJ  = SCREEN_HEIGHT-50;
const int SPEED_MAIN_OBJECT     = 10;
const int SPEED_egg_MAIN     = 20;

//Threats

const int SPEED_THREAT = 3;
static int NUM_THREATS = 2;
static int SPEED_egg_THREATS = 5;
const int VAL_OFFSET_START_POST_THREATS = 400;

static SDL_Surface* g_screen    = NULL;
static SDL_Surface* g_bkground  = NULL;
static SDL_Event g_even;
static SDL_Event event;
static SDL_Surface *startStop = NULL;
static SDL_Surface *seconds = NULL;

static TTF_Font *font = NULL;
static SDL_Color textColor = { 0, 0, 0 };
static SDL_Surface *message = NULL;
static SDL_Surface *Infor = NULL;
static Mix_Chunk* g_sound_egg[2];
static Mix_Chunk* g_sound_exp[2];


static char background[] = {"choosenbk.png"};
static char egg_popped[] = { "egg-popped.png" };
static char g_name_main_obj[]           = {"bowl.png"};
static char g_name_exp_main []          = {"exp_main.png"};
static char g_name_egg_main_fire[]   = {"sphere.png"};
static char g_name_audio_egg_main[]  = {"out.wav"};
static char g_name_audio_egg_main2[] = {"Fire1.wav"};
static char g_name_audio_exp_main[]     = {"gakeuchoosen.wav"};

static char g_name_exp_threats[]        = {"exp.png"};
static char g_name_threats[]            = {"choosen.png"};
static char g_name_egg_threats[]     = {"egg1.png"};
static char g_name_audio_exp_threats[]  = {"out.wav"};

namespace SDLCommonFunc
{
  SDL_Surface* LoadImage(std::string file_path);
  void CleanUp();
  void ApplySurface(SDL_Surface* src, SDL_Surface* des, int x, int y);
  void ApplySurfaceClip(SDL_Surface* src, SDL_Surface* des, SDL_Rect* clip, int x, int y);
  bool CheckCollision(const SDL_Rect& object1, const SDL_Rect& object2);
  int MakeRandValue(const int& div_val);
}


#endif
