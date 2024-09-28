#include <engine/platform/ogl_texture.hpp>

#include <stb_image.h>

namespace logicario::engine::platform
{
    OglTexture::OglTexture() : m_texture{nullptr, nullptr} {}

    OglTexture::OglTexture(const Image& image, const ID& resourceID) : Resource{resourceID}, m_texture{nullptr, nullptr}, m_image{image}
    {
        GLuint texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_image.width, m_image.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_image.data.data());
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        m_texture = GlTexture{new GLuint{texture}, [](GLuint* id) { glDeleteTextures(1, id); }};
    }

    void OglTexture::bind()
    {
        glBindTexture(GL_TEXTURE_2D, *m_texture);
    }

    OglTexture::OglTexture(OglTexture&& texture) noexcept : m_texture{std::move(texture.m_texture)}
    {
        setID(texture.getID());
    }

    OglTexture& OglTexture::operator=(OglTexture&& texture) noexcept
    {
        m_texture = std::move(texture.m_texture);
        setID(texture.getID());
        return *this;
    }

    bool OglTexture::operator==(const OglTexture& texture) const noexcept
    {
        return Resource::getID() == texture.getID();
    }
}