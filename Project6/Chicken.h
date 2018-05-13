

#ifndef CHICKEN_H_
#define CHICKEN_H_
#include "Common_Function.h"
#include "BaseObject.h"
#include "Egg.h"
#include <vector>

#define WIDTH_THREAT 64
#define HEIGHT_THREAT 57

class Chicken : public BaseObject
{
public:
  Chicken();
  ~Chicken();

  void HandleMove(const int& x_bordr, const int& y_border);
  void HandleInputAction(SDL_Event events);

  void set_x_val(const int& val) {x_val_ = val;}
  void set_y_val(const int& val) {y_val_ = val;}
  int get_x_val() const {return x_val_;}
  int get_y_val() const {return y_val_;}

  void SeteggList(std::vector<Egg*> egg_list) {p_egg_list_ = egg_list;}
  std::vector<Egg*> GeteggList() const {return p_egg_list_;}

  void Initegg(Egg* p_egg);
  void Makeegg(SDL_Surface* des);
  void Reset(const int& xboder);
  void Resetegg(Egg* p_egg);
private:
  int x_val_;
  int y_val_;

  std::vector<Egg*> p_egg_list_;
};

#endif