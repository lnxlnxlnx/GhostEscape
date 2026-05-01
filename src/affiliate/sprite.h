#ifndef E2C96073_6F1C_4907_9EBC_0E1B90C86319
#define E2C96073_6F1C_4907_9EBC_0E1B90C86319
#include <string>
#include <SDL3/SDL.h>
#include "../core/object_affiliate.h"

// sprite.h
struct Texture
{
    SDL_Texture *texture = nullptr;
    SDL_FRect src_rect = {0, 0, 0, 0};
    float angle = 0;
    bool is_flip = false;
    Texture() = default;
    //Texture(const std::string& file_path); 
    Texture(std::string_view file_path); 
};

// sprite.h
class Sprite : public ObjectAffiliate
{
protected:
    Texture texture_;

public:
    Sprite() = default;
    virtual void render() override;

    // getters and setters
    Texture getTexture() const { return texture_; }
    void setTexture(const Texture &texture);
};



#endif /* E2C96073_6F1C_4907_9EBC_0E1B90C86319 */
