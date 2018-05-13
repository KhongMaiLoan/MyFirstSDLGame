



//PERFECT

#include "Common_Function.h"
#include "MainObject.h"
#include "Chicken.h"
#include "ExplosionObject.h"

bool load_files()
{

	font = TTF_OpenFont("Star.ttf", 48);
	if (font == NULL) return false;
	return true;
}

bool Init(int width, int height)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == GA_FAILED)
	{
		return false;
	}

	g_screen = SDL_SetVideoMode(width, height, SCREEN_BPP, SDL_SWSURFACE);

	if (g_screen == NULL)
		return false;

	if (TTF_Init() == -1)
	{
		return false;
	}

	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == GA_FAILED)
		return false;

	//Read file wav audio
	g_sound_egg[0] = Mix_LoadWAV(g_name_audio_egg_main);
	g_sound_egg[1] = Mix_LoadWAV(g_name_audio_egg_main2);
	g_sound_exp[0] = Mix_LoadWAV(g_name_audio_exp_threats);
	g_sound_exp[1] = Mix_LoadWAV(g_name_audio_exp_main);

	if (g_sound_exp[0] == NULL || g_sound_egg[0] == NULL || g_sound_egg[1] == NULL || g_sound_exp[1] == NULL)
	{
		return false;
	}

	return true;
}

#undef main
int main(int arc, char*argv[])
{
  bool is_run_screen = true;
  int bkgn_x = 0;
  bool is_quit = false;
  if (Init(801, 602) == false) return 0;
  if (load_files() == false) return 1;
  g_bkground = SDLCommonFunc::LoadImage("Menu.png");
  if (g_bkground == NULL)
  {
    return 0;
  }




  while (!is_quit)
  {
	  while (SDL_PollEvent(&g_even))
	  {
		  int x = 0, y = 0;
		  if (g_even.type == SDL_MOUSEBUTTONDOWN)
		  {
			  if (g_even.button.button == SDL_BUTTON_LEFT)
			  {
				  x = g_even.button.x;
				  y = g_even.button.y;
				  if ((x > 263) && (x < 525) && (y > 360) && (y < 410))
				  {
					  goto play_Game;
				  }
				  else if (((x > 263) && (x < 525) && (y > 420) && (y < 470)))
				  {

				  }
			  }
		  }
		  if (g_even.type == SDL_QUIT)
		  {
			  is_quit = true;
			  break;
		  }

	  }
	  SDLCommonFunc::ApplySurface(g_bkground, g_screen, 0, 0);
	  if (SDL_Flip(g_screen) == -1)
	  {
		  SDLCommonFunc::CleanUp();
		  SDL_Quit();
		  return 0;
	  }
  }

play_Game:srand(time(0));
  is_quit = false;
  if (Init(SCREEN_WIDTH, SCREEN_HEIGHT) == false)
	  return 0;
  if (load_files() == false) return 1;

  g_bkground = SDLCommonFunc::LoadImage(background);
  if (g_bkground == NULL)
  {
	  return 0;
  }
  //Make MainObject
  MainObject plane_object;
  plane_object.SetRect(POS_X_START_MAIN_OBJ, POS_Y_START_MAIN_OBJ);
  bool ret = plane_object.LoadImg(g_name_main_obj);
  if (!ret)
  {
    return 0;
  }

  //Init explosion object
  ExplosionObject exp_main;
  ExplosionObject exp_threats;
  ret = exp_main.LoadImg(g_name_exp_main);
  exp_main.set_clip();
  if (ret == false) return 0;

  ret = exp_threats.LoadImg(g_name_exp_threats );
  exp_threats.set_clip();
  if (!ret) return 0;


  int   numEgg = 0, requiredEgg = 10;
  static Uint32 start = 0;

  nextLv:
  //Make Chicken
  Chicken* p_threats = new Chicken[NUM_THREATS];

  for (int t = 0; t < NUM_THREATS; t++)
  {
    Chicken* p_threat = (p_threats + t);
    if (p_threat)
    {
      ret = p_threat->LoadImg(g_name_threats);
      if (ret == false)
      {
        delete [] p_threats;
        SDLCommonFunc::CleanUp();
        SDL_Quit();
        return 0;
      }

      int rand_y = SDLCommonFunc::MakeRandValue(400);
	  int rand_x = SDLCommonFunc::MakeRandValue(700) +SCREEN_WIDTH;
      p_threat->SetRect(SCREEN_WIDTH + t*VAL_OFFSET_START_POST_THREATS, rand_y);
      p_threat->set_x_val(SPEED_THREAT);

      Egg* p_egg = new Egg();
      p_threat->Initegg(p_egg);
    }
  }

  
  start = SDL_GetTicks();
  while (!is_quit) 
  {
    while (SDL_PollEvent(&g_even)) 
    {
      if (g_even.type == SDL_QUIT)
      {
        is_quit = true;
        break;
      }
      plane_object.HandleInputAction(g_even, g_sound_egg);
    }


    //Implement dynamic screen
    if (is_run_screen == true)
    {
      bkgn_x -= SPEED_SCREEN;
      if (bkgn_x <= -(WIDTH_BACKGROUND - SCREEN_WIDTH))
      {
        is_run_screen = false;
      }
      else
      {
        SDLCommonFunc::ApplySurface(g_bkground, g_screen, bkgn_x, 0);
      }
    }
    else
    {
      SDLCommonFunc::ApplySurface(g_bkground, g_screen, bkgn_x, 0);
    }
    

    //Implement main object
    plane_object.HandleMove();
    plane_object.Show(g_screen);

    //Implement Threats Object
	for (int tt = 0; tt < NUM_THREATS; tt++)
	{
		Chicken* p_threat = (p_threats + tt);
		if (p_threat)
		{
			p_threat->HandleMove(SCREEN_WIDTH, SCREEN_HEIGHT);
			p_threat->Show(g_screen);
			p_threat->Makeegg(g_screen);


			//COLLISION THREAT egg -> MAIN OBJECT
			bool is_col1 = false;
			std::vector<Egg*> egg_arr = p_threat->GeteggList();
			for (int am = 0; am < egg_arr.size(); am++)
			{
				Egg* p_egg = egg_arr.at(am);
				if (p_egg)
				{
					is_col1 = SDLCommonFunc::CheckCollision(p_egg->GetRect(), plane_object.GetRect());
					if (is_col1 == true)
					{
						numEgg++;
						p_threat->Resetegg(p_egg);
						break;
					}
				}
			}

			//Check collision main and threats
			bool is_col = SDLCommonFunc::CheckCollision(plane_object.GetRect(), p_threat->GetRect());
			if (is_col)
			{
				for (int ex = 0; ex < 4; ex++)
				{
					int x_pos = (plane_object.GetRect().x + plane_object.GetRect().w*0.5) - EXP_WIDTH * 0.5;
					int y_Pos = (plane_object.GetRect().y + plane_object.GetRect().h*0.5) - EXP_HEIGHT * 0.5;

					exp_main.set_frame(ex);
					exp_main.SetRect(x_pos, y_Pos);
					exp_main.ShowEx(g_screen);
					//Update screen
					if (SDL_Flip(g_screen) == -1)
					{
						delete[] p_threats;
						SDLCommonFunc::CleanUp();
						SDL_Quit();
						return 0;
					}
				}

				Mix_PlayChannel(-1, g_sound_exp[1], 0);

			}

			if (is_col1)
			{
				for (int ex = 0; ex < 4; ex++)
				{
					int x_pos = (plane_object.GetRect().x + plane_object.GetRect().w*0.5) - EXP_WIDTH * 0.5;
					int y_Pos = (plane_object.GetRect().y + plane_object.GetRect().h*0.5) - EXP_HEIGHT * 0.5;

					exp_main.set_frame(ex);
					exp_main.SetRect(x_pos, y_Pos);
					exp_main.ShowEx(g_screen);
					//Update screen
					if (SDL_Flip(g_screen) == -1)
					{
						delete[] p_threats;
						SDLCommonFunc::CleanUp();
						SDL_Quit();
						return 0;
					}
				}

				Mix_PlayChannel(-1, g_sound_exp[0], 0);

			}
		}

	}
	if ((int)SDL_GetTicks() - start >= 10000)
	{
		start = SDL_GetTicks();
		if (requiredEgg - numEgg <= 0)
		{
			requiredEgg += 10;
			NUM_THREATS+=5;
			SPEED_egg_THREATS++;
			goto nextLv;

		}
		else
		{
			std::stringstream ss;
			ss << "YOUR TOTAL EGG:"<< numEgg;
			std::string str = ss.str();
			message = TTF_RenderText_Solid(font, str.c_str(), textColor);
			if (message == NULL)
			{
				return 1;
			}
			Infor = TTF_RenderText_Solid(font, "GAME OVER: \n \n RUN OUT OF TIME \n \n ", textColor);
			while (!is_quit)
			{
				while (SDL_PollEvent(&event))
				{
					if (event.type == SDL_QUIT)
					{
						is_quit = true;
						break;
					}
				}
				SDLCommonFunc::ApplySurface(g_bkground, g_screen, 0, 0);
				SDLCommonFunc::ApplySurface(Infor, g_screen, SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4);
				SDLCommonFunc::ApplySurface(message, g_screen, SCREEN_WIDTH / 4 + 200, SCREEN_HEIGHT / 4 + 200);

				if (SDL_Flip(g_screen) == -1)
				{
					return 1;
				}
				//SDLCommonFunc::CleanUp();
				//SDL_Quit();
				//return 1;
			}
		}
	}
    //Update screen
    if ( SDL_Flip(g_screen) == -1)
    {
      delete [] p_threats;
      SDLCommonFunc::CleanUp();
      SDL_Quit();
      return 0;
    }
  }

  delete [] p_threats;
  SDLCommonFunc::CleanUp();
  SDL_Quit();

  return 1;
}
