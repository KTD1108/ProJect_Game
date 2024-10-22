#include "../include/BulletObject.h"

BulletObject::BulletObject() : BaseObject()
{
    rect_.x = 0 ;
    rect_.y = 0;
    x_val_ = 0;
    y_val_ = 0;
    is_moving_ = false;
    direction_ = 0;  // Default direction is right
}

BulletObject::~BulletObject()
{
    // Destructor logic (if needed)
}

void BulletObject::HandleMove(const int& x_border, const int& y_border)
{
    if (is_moving_)
    {
        if (direction_ == 0)  // Move right
        {
            rect_.x += BULLET_SPEED;
        }
        else if (direction_ == 1)  // Move left
        {
            rect_.x -= BULLET_SPEED;
        }

        // Check if bullet goes out of screen borders
        if (rect_.x > x_border || rect_.x < 0)
        {
            is_moving_ = false;
        }
    }
}