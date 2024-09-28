#pragma once

#include <engine/texture.hpp>

namespace logicario::engine
{
    class Sprite
    {
    public:
        Sprite(Texture& texture);
        Sprite(Texture& texture, const Texture::Region& region);
        Texture& getTexture();
        Texture::Region getTextureRegion();

    private:
        Texture& m_texture;
        Texture::Region m_textureRegion;
    };
}
