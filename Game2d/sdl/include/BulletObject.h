#ifndef BULLET_OBJECT_H_
#define BULLET_OBJECT_H_

#include "../include/BaseObject.h"

#define BULLET_WIDTH 36
#define BULLET_HEIGHT 5
#define BULLET_SPEED 3

class BulletObject : public BaseObject
{
public:
    BulletObject();
    ~BulletObject();

    void HandleMove(const int& x_border, const int& y_border);
    void SetIsMoving(bool is_moving) { is_moving_ = is_moving; }
    bool GetIsMoving() const { return is_moving_; }

    void SetDirection(int direction) { direction_ = direction; }
    int GetDirection() const { return direction_; }

    void SetXVal(const int& x_val) { x_val_ = x_val; }
    void SetYVal(const int& y_val) { y_val_ = y_val; }

    int GetXVal() const { return x_val_; }
    int GetYVal() const { return y_val_; }

private:
    int x_val_;
    int y_val_;
    bool is_moving_;
    int direction_; 
};

#endif 