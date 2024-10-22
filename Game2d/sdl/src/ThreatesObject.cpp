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

void ThreatObject::InitBullet(BulletObject* p_bullet,SDL_Renderer* g_renderer)
{
    if(p_bullet)
    {
        bool ret = p_bullet->LoadImg("sphere.png",g_renderer) ;
        if(ret)
        {   
            
            
                p_bullet->set_is_move(true) ;
                p_bullet->SetRect(rect_.x,rect_.y + rect_.h * 0.5) ;
                p_bullet_list_.push_back(p_bullet) ;
                
            
            
        }
    }
}

void ThreatObject::MakeBullet(SDL_Renderer* des,const int& x_limit,const& y_limit)
{
    for(int i = 0; i < p_bullet_list_.size();i++)
    {
        BulletObject*  p_bullet = p_bullet_list_.at(i) ;
        if(p_bullet)
        {
            if(p_bullet->get_is_move())
            {
                p_bullet->Show(des) ;
                p_bullet->HandleMoveRightToLeft() ;
            }
            else
            {
                p_bullet->set_is_move(true) ;
                p_bullet->SetRect(rect_.x , rect_.y + rect_.h * 0.5) ;
            }
        }
    }
}

void ThreatObject::HandleMove(const int& x_border,const int& y_border)
{   
    static Uint32 last_move_time = 0;  
    Uint32 current_time = SDL_GetTicks();  

    
    if (current_time > last_move_time + 1)  
    {
        rect_.x -= x_val_;
        last_move_time = current_time;  
    }

    if (rect_.x < 0)  
    {
        rect_.x = SCREEN_WIDTH;  
        int rand_y = rand() % 400;
        if (rand_y > SCREEN_HEIGHT - 200)
        {
            rand_y = SCREEN_HEIGHT * 0.3;
        }
        rect_.y = rand_y;  
    }
}

void ThreatObject::HandleInputAction(SDL_Event event,SDL_Renderer* renderer)
{

}