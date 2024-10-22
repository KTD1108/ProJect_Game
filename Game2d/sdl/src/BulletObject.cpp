#include "../include/BulletObject.h"

BulletObject::BulletObject() : BaseObject()
{
    rect_.x = 0;
    rect_.y = 0;
    x_val_ = 0;
    y_val_ = 0;
    is_move_ = false;
    amo_type_ = NONE;
}

BulletObject::~BulletObject()
{
    // Destructor logic (if needed)
}

void BulletObject::HandleMove(const int& x_border, const int& y_border)
{
  if (is_move_ == true)
  {
    rect_.x += 5;
    if (rect_.x > x_border)
    {
      is_move_ = false;
    }
  }
}
void BulletObject::HandleMoveRightToLeft()
{
    rect_.x -= 1 ;
    if(rect_.x < 0)
    {
        is_move_ = false ;
    }
}