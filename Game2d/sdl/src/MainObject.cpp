#include "../include/MainObject.h"


MainObject::MainObject()
{
    rect_.x = 0 ;
    rect_.y = 0 ;
    rect_.w = WIDTH_MAIN_OBJECT_ ;
    rect_.h = HEIGHT_MAIN_OBJECT ;
    x_val_ = 0 ;
    y_val_ = 0 ;
    last_shoot_time_ = 0;
}

MainObject::~MainObject()
{
    
    for (int i = 0; i < p_bullet_list_.size(); i++)
    {
        BulletObject* p_bullet = p_bullet_list_[i];
        if (p_bullet != nullptr)
        {
            delete p_bullet;
            p_bullet = nullptr;
        }
    }
    p_bullet_list_.clear();
}

void MainObject::HandleBullet(SDL_Renderer* renderer)
{
    for (size_t i = 0; i < p_bullet_list_.size(); ++i)
    {
        BulletObject* p_bullet = p_bullet_list_[i];
        if (p_bullet != NULL)
        {
            if (p_bullet->GetIsMoving())
            {
                
                p_bullet->Show(renderer);
                p_bullet->HandleMove(SCREEN_WIDTH, SCREEN_HEIGHT);
            }
            else
            {
                
                delete p_bullet;
                p_bullet_list_.erase(p_bullet_list_.begin() + i);
                --i; 
            }
        }
    }
}


void MainObject::HandleInputAction(SDL_Event event,SDL_Renderer* renderer)
{
    BulletObject* p_bullet = nullptr;
    if(event.type == SDL_KEYDOWN)
    {
        switch (event.key.keysym.sym)
        {
        case SDLK_UP:
            y_val_ -= HEIGHT_MAIN_OBJECT / 2 ;
            break;
        case SDLK_DOWN:
            y_val_ += HEIGHT_MAIN_OBJECT / 2 ;
            break;
        case SDLK_RIGHT:
            x_val_ += WIDTH_MAIN_OBJECT_ / 2 ;
            break;
        case SDLK_LEFT:
            x_val_ -= WIDTH_MAIN_OBJECT_ / 2;
            break;
     
        default:
            break;
        }
    }
    else if(event.type == SDL_KEYUP)
    {
        switch (event.key.keysym.sym)
        {
        case SDLK_UP:
            
        case SDLK_DOWN:
            y_val_ = 0 ;
            break;
        case SDLK_RIGHT:
            
        case SDLK_LEFT:
            x_val_ = 0;
            break;
        default:
            break;
        }
    }
    else if (event.type == SDL_MOUSEBUTTONDOWN)
    {
        if(event.button.button == SDL_BUTTON_LEFT)
        {   
            Uint32 current_time = SDL_GetTicks();
            if (current_time - last_shoot_time_ > shoot_interval_){
            p_bullet = new BulletObject(); 
            p_bullet->LoadImg("sphere.png", renderer);
            p_bullet->SetRect(rect_.x + rect_.w - 40, rect_.y + rect_.h * 0.8);
            p_bullet->SetXVal(BULLET_SPEED);
            p_bullet->SetIsMoving(true);
            p_bullet_list_.push_back(p_bullet);

            last_shoot_time_ = current_time;
            } 
        }
        else if(event.button.button == SDL_BUTTON_RIGHT)
        {
        Uint32 current_time = SDL_GetTicks();
            if (current_time - last_shoot_time_ > shoot_interval_){
            p_bullet = new BulletObject(); 
            p_bullet->LoadImg("laser.png", renderer);
            p_bullet->SetRect(rect_.x + rect_.w - 40, rect_.y + rect_.h * 0.8);
            p_bullet->SetXVal(BULLET_SPEED);
            p_bullet->SetIsMoving(true);
            p_bullet_list_.push_back(p_bullet);

            last_shoot_time_ = current_time;
            } 
        }
        
    }

    else if(event.type == SDL_MOUSEBUTTONUP)
    {

    }
    else
    {

    }
    
}

void MainObject::HandleMove()
{
    rect_.x += x_val_ ;
    if(rect_.x < 0 || rect_.x + WIDTH_MAIN_OBJECT_ > SCREEN_WIDTH)
    {
        rect_.x -= x_val_ ;
    }
    rect_.y += y_val_ ;
    if(rect_.y < 0 || rect_.y + HEIGHT_MAIN_OBJECT > SCREEN_HEIGHT - 200)
    {
        rect_.y -= y_val_ ;
    }
    
}