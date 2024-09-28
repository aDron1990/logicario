#pragma once

#include <engine/action.hpp>
#include <engine/image.hpp>
#include <engine/shader.hpp>
#include <engine/texture.hpp>

#include <glm/glm.hpp>

namespace logicario::engine
{
    class Renderer
    {
    public:
        virtual void swap() = 0;
        virtual void clear(const glm::vec4& color) = 0;
        virtual void drawTestTriangle(Shader& shader) = 0;

    public:
        virtual Shader& createShader(const Text& vertexCode, const Text& fragmentCode) = 0;
		virtual Texture& createTexture(const Image& image) = 0;

    protected:
        ~Renderer() = default;
    };
}
