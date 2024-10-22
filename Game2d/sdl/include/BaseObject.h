#ifndef BASE_OBJECT_H_
#define BASE_OBJECT_H_

#include "../include/Common_Function.h"

class BaseObject
{
public:
    BaseObject();
    ~BaseObject();
    
    void Show(SDL_Renderer* renderer);

    bool LoadImg(const std::string& file_name, SDL_Renderer* renderer);

    void SetRect(const int& x,const int& y) {
        rect_.x = x;
        rect_.y = y;
    }

    SDL_Rect GetRect() const {
        return rect_;
    }

    SDL_Texture* GetObject() const {
        return p_object_;
    }

protected:
    SDL_Rect rect_;        
    SDL_Texture* p_object_;
};

#endif // BASE_OBJECT_H_
