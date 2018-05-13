
#ifndef EGG_H_
#define EGG_H_
#include "BaseObject.h"

#define WIDTH_LASER 23
#define HEIGHT_LASER 28

#define WIDTH_SPHERE 25
#define HEIGHT_SPHERE 33

class Egg : public BaseObject
{
public:
  enum eggType
  {
    NONE = 0,
    LASER = 1,
    SPHERE = 2
  };

  Egg();
  ~Egg();
  void HandleInputAction(SDL_Event events);
  void AllFallDown();

  int get_type() const {return egg_type_;}
  void set_type(const int& type) {egg_type_ = type;}

  bool get_is_move() const {return is_move_;}
  void set_is_move(bool is_move) {is_move_ = is_move;}
  void SetWidthHeight(const int& widht, const int& height) {rect_.w = widht; rect_.h = height;};

  void set_x_val(const int& val) {x_val_ = val;}
  void set_y_val(const int& val) {y_val_ = val;}

  int get_x_val() const {return x_val_;}
  int get_y_val() const {return y_val_;}
private:
  int x_val_;
  int y_val_;
  int egg_type_;

  bool is_move_;
};


#endif