#ifndef THREATES_OBJECT_H_ 
#define THREATES_OBJECT_H_ 

#include "../include/Common_Function.h"
#include "../include/BaseObject.h"
#include "../include/BulletObject.h"
#include <vector>

#define WIDTH_THREAT 80
#define HEIGHT_THREAT 33

class ThreatObject : public BaseObject
{
    public:
        ThreatObject() ;
        ~ThreatObject() ;
        void HandleMove(const int& x_border,const int& y_border) ;
        void HandleInputAction(SDL_Event event,SDL_Renderer* renderer) ;
        void set_x_val(const int& val) {x_val_ = val ;}
        void set_y_val(const int& val) {y_val_ = val ;}
        int get_x_val()const { return x_val_ ;}
        int get_y_val()const { return y_val_ ;} 
        void SetBulletList(std::vector<BulletObject*> bullet_list) { p_bullet_list_ = bullet_list; }
        std::vector<BulletObject*> GetBulletList() const { return p_bullet_list_; }
        void InitBullet(BulletObject* p_bullet,SDL_Renderer* g_renderer) ;
        void MakeBullet(SDL_Renderer* des,const int& x_limit,const& y_limit) ;
    private:
        int x_val_ ;
        int y_val_ ;
        std::vector<BulletObject*> p_bullet_list_;
        
};

#endif