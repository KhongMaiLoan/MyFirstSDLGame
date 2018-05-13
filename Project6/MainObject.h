
#ifndef MAIN_OBJECT_H_
#define MAIN_OBJECT_H_

#include "Common_Function.h"
#include "BaseObject.h"
#include "Egg.h"
#include <vector>

#define WIDTH_MAIN_OBJECT 77
#define HEIGHT_MAIN_OBJECT 52

class MainObject : public BaseObject
{
public:
  MainObject();
  ~MainObject();

  void HandleInputAction(SDL_Event events, Mix_Chunk* egg_sound[2]);
  void HandleMove();

private:
  int x_val_;
  int y_val_;

};



#endif //MAIN_OBJECT_H_