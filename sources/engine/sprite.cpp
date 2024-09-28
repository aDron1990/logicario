#include <engine/sprite.hpp>

namespace logicario::engine
{
    Sprite::Sprite(Texture& texture) : m_texture{texture}
    {
        auto textureSize = texture.getSize();
        m_textureRegion = {0, textureSize.x, 0, textureSize.y};
    }

    Sprite::Sprite(Texture& texture, const Texture::Region& region) : m_texture{texture}, m_textureRegion{region} {}

	Texture& Sprite::getTexture()
	{
		return m_texture;
	}

    Texture::Region Sprite::getTextureRegion()
	{
		return m_textureRegion;
	}
}