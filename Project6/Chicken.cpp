
#include "Chicken.h"

Chicken::Chicken()
{
  rect_.x = SCREEN_WIDTH;
  rect_.y = SCREEN_HEIGHT*0.5;
  rect_.w = WIDTH_THREAT;
  rect_.h = HEIGHT_THREAT;

  x_val_ = 0;
  y_val_ = 0;
}



Chicken::~Chicken()
{
  if (p_egg_list_.size() > 0)
  {
    for (int i = 0; i < p_egg_list_.size(); i++)
    {
      Egg* p_egg = p_egg_list_.at(i);
      if (p_egg != NULL)
      {
        delete p_egg;
        p_egg = NULL;
      }
    }
    p_egg_list_.clear();
  }
}


void Chicken::Initegg(Egg* p_egg)
{
  if (p_egg)
  {
    bool ret = p_egg->LoadImg(g_name_egg_threats);
    if (ret)
    {
      p_egg->set_is_move(true);
      p_egg->SetWidthHeight(WIDTH_SPHERE, HEIGHT_SPHERE);
      p_egg->set_type(Egg::SPHERE);
      p_egg->SetRect(rect_.x + rect_.w/4 , rect_.y + rect_.h);
      p_egg->set_y_val(SPEED_egg_THREATS);
      p_egg_list_.push_back(p_egg);
    }
  }
}


void Chicken::Makeegg(SDL_Surface* des)
{
  for (int i = 0; i < p_egg_list_.size(); i++)
  {
    Egg* p_egg = p_egg_list_.at(i);
    if (p_egg)
    {
      if (p_egg->get_is_move())
      {
        p_egg->Show(des);
        p_egg->AllFallDown();
      }
      else
      {
        p_egg->set_is_move(true);
        p_egg->SetRect(rect_.x + rect_.w / 4, rect_.y + rect_.h);
      }
    }
  }
}

void Chicken::HandleMove(const int& x_bordr, const int& y_border)
{
  rect_.x -= x_val_;
  if (rect_.x < 0)
  {
    rect_.x  = SCREEN_WIDTH;
    rect_.y= SDLCommonFunc::MakeRandValue(400);
  }
}

void Chicken::HandleInputAction(SDL_Event events)
{
  //Todo
}


void Chicken::Reset(const int& xboder)
{
  rect_.x = xboder; 
  rect_.y = SDLCommonFunc::MakeRandValue(400);

  for (int i = 0; i < p_egg_list_.size(); i++)
  {
    Egg* p_egg = p_egg_list_.at(i);
    if (p_egg)
    {
      Resetegg(p_egg);
    }
  }
}

void Chicken::Resetegg(Egg* p_egg)
{
   p_egg->SetRect(rect_.x + rect_.w / 2, rect_.y + rect_.h);
}