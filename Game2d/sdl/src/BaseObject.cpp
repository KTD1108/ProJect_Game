#include "../include/BaseObject.h"

BaseObject::BaseObject() {
    rect_.x = 0; 
    rect_.y = 0; 
    rect_.w = 0; 
    rect_.h = 0; 
    p_object_ = NULL; 
}

BaseObject::~BaseObject() {
    if (p_object_ != nullptr) {
        SDL_DestroyTexture(p_object_); 
        p_object_ = nullptr; 
    }
}

bool BaseObject::LoadImg(const std::string& file_name, SDL_Renderer* renderer) {
    p_object_ = SDLCommonFunc::LoadImage(file_name, renderer);
    if (p_object_ == nullptr) {
        return false; 
    }
    
    
    SDL_QueryTexture(p_object_, nullptr, nullptr, &rect_.w, &rect_.h);
    return true; 
}

void BaseObject::Show(SDL_Renderer* renderer) {
    if (p_object_ != nullptr) {
        SDLCommonFunc::ApplyTexture(p_object_, renderer, rect_.x, rect_.y); 
    }
}
