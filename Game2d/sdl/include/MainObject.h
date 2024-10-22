#ifndef MAIN_OBJECT_H_
#define MAIN_OBJECT_H_

#include "../include/Common_Function.h"
#include "../include/BaseObject.h"
#include "../include/BulletObject.h"
#include <vector>

#define WIDTH_MAIN_OBJECT_ 77
#define HEIGHT_MAIN_OBJECT 52 

class MainObject : public BaseObject
{
public:
    MainObject();
    ~MainObject();

    void HandleInputAction(SDL_Event event, SDL_Renderer* renderer);  
    void HandleMove();
    void HandleBullet(SDL_Renderer* renderer);  

    void SetBulletList(std::vector<BulletObject*> bullet_list) { p_bullet_list_ = bullet_list; }
    std::vector<BulletObject*> GetBulletList() const { return p_bullet_list_; }

private:
    int x_val_;
    int y_val_;
    std::vector<BulletObject*> p_bullet_list_; 
};

#endif  // MAIN_OBJECT_H_
