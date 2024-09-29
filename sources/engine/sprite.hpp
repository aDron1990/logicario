#pragma once

#include <engine/texture.hpp>
#include <engine/transform.hpp>

namespace logicario::engine
{
    class Sprite : public Transform
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
