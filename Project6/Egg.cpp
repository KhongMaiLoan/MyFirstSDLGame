
#include "Egg.h"

Egg::Egg()
{
  rect_.x = 0;
  rect_.y = 0;
  x_val_ = 0;
  y_val_ = 0;
  is_move_ = false;
  egg_type_ = NONE;
}
Egg::~Egg()
{

}

void Egg::AllFallDown()
{
  rect_.y += y_val_;
  if (rect_.y > SCREEN_HEIGHT-50)
  {
    is_move_ = false;
  }
}

void Egg::HandleInputAction(SDL_Event events)
{
  ;//Todo
}
