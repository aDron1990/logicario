#pragma once

#include <engine/texture.hpp>
#include <engine/image.hpp>

#include <GL/glew.h>

#include <memory>

namespace logicario::engine::platform
{
    class OglTexture : public Texture
    {
    public:
        OglTexture();
        OglTexture(const Image& image, const ID& resourceID);
        void bind() override;
        glm::ivec2 getSize() override;
        bool operator==(const OglTexture& texture) const noexcept;

    public:
        OglTexture(OglTexture&& texture) noexcept;
        OglTexture& operator=(OglTexture&& texture) noexcept;
        OglTexture(const OglTexture&) = delete;
        OglTexture& operator=(const OglTexture&) = delete;

    private:
        using GlTextureDeleter = void (*)(GLuint*);
        using GlTexture = std::unique_ptr<GLuint, GlTextureDeleter>;
        GlTexture m_texture;
        Image m_image;
    };
}