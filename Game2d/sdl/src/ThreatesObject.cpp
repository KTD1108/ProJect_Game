#include "../include/ThreatesObject.h"

ThreatObject::ThreatObject()
{
    rect_.x = SCREEN_WIDTH ;
    rect_.y = SCREEN_HEIGHT * 0.5 ;
    rect_.w = WIDTH_THREAT ;
    rect_.h = HEIGHT_THREAT ;

    x_val_ = 0 ;
    y_val_ = 0 ;
}

ThreatObject::~ThreatObject()
{

}

void ThreatObject::InitBullet(BulletObject* p_bullet)
{
    if(p_bullet)
    {
        bool ret = p_bullet->LoadImg("sphere.png",g_renderer) ;
        if(ret)
        {
            p_bullet->SetIsMoving(true) ;
            p_bullet->SetRect(rect_.x,rect_.y + rect_.h * 0.5) ;
            p_bullet_list_.push_back(p_bullet) ;
        }
    }
}

void ThreatObject::HandleMove(const int& x_border,const int& y_border)
{   
    static Uint32 last_move_time = 0;  // Lưu thời gian lần di chuyển cuối cùng
    Uint32 current_time = SDL_GetTicks();  // Thời gian hiện tại tính bằng mili giây

    // Di chuyển sau mỗi 50ms
    if (current_time > last_move_time + 1)  
    {
        rect_.x -= x_val_;
        last_move_time = current_time;  // Cập nhật thời gian di chuyển
    }

    if (rect_.x < 0)  // Khi máy bay ra khỏi màn hình
    {
        rect_.x = SCREEN_WIDTH;  // Reset lại vị trí
        int rand_y = rand() % 400;
        if (rand_y > SCREEN_HEIGHT - 200)
        {
            rand_y = SCREEN_HEIGHT * 0.3;
        }
        rect_.y = rand_y;  // Đặt lại vị trí y ngẫu nhiên
    }
}

void ThreatObject::HandleInputAction(SDL_Event event,SDL_Renderer* renderer)
{

}