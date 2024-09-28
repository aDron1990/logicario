#pragma once

#include <engine/shader.hpp>

#include <GL/glew.h>

#include <memory>
#include <cstdint>

namespace logicario::engine::platform
{
    class OglShader : public Shader
    {
    public:
        OglShader();
        OglShader(const Text& vertexCode, const Text& fragmentCode, const ID& resourceID);
        void bind() override;
        bool operator==(const OglShader& shader) const noexcept;

    public:
        OglShader(OglShader&& shader) noexcept;
        OglShader& operator=(OglShader&& shader) noexcept;
        OglShader(const OglShader&) = delete;
        OglShader& operator=(const OglShader&) = delete;

    private:
        using GlShaderDeleter = void (*)(GLuint*);
        using GlShader = std::unique_ptr<GLuint, GlShaderDeleter>;
        GlShader compileShader(const Text& shaderCode, uint16_t shaderType);
        void linkProgram(GlShader vertex, GlShader fragment);

    private:
        using GlProgramDeleter = void (*)(GLuint*);
        using GlProgram = std::unique_ptr<GLuint, GlProgramDeleter>;
        GlProgram m_program;
    };
}