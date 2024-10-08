#pragma once

#include <engine/action.hpp>
#include <engine/types.hpp>
#include <engine/types.hpp>
#include <engine/image.hpp>
#include <engine/sprite.hpp>
#include <engine/shader.hpp>
#include <engine/texture.hpp>
#include <engine/view.hpp>
#include <engine/view_impl.hpp>
#include <engine/transform.hpp>

namespace logicario::engine
{
    class Renderer
    {
    public:
        virtual void swap() = 0;
        virtual void clear(const glm::vec4& color) = 0;
        virtual void draw(View& view, Sprite& sprite, Shader& shader) = 0;
		virtual void draw(View& view, Rect& rect, Shader& shader, glm::vec4 color) = 0;
        virtual void drawBackground(View& view, Shader& shader, glm::vec4 color) = 0;

    public:
        virtual Shader& createShader(const Text& vertexCode, const Text& fragmentCode) = 0;
        virtual Texture& createTexture(const Image& image) = 0;
        virtual View& createView(View::ViewControllerPtr viewController) = 0;

    protected:
        ~Renderer() = default;
    };
}
