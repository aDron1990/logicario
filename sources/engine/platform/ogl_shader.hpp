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
        using ShaderModuleDeleter = void (*)(GLuint*);
        using ShaderModule = std::unique_ptr<GLuint, ShaderModuleDeleter>;
        ShaderModule compileShader(const Text& shaderCode, uint16_t shaderType);
        void linkProgram(ShaderModule vertex, ShaderModule fragment);

    private:
        using ProgramDeleter = void (*)(GLuint*);
        using Program = std::unique_ptr<GLuint, ProgramDeleter>;
        Program m_program;
    };
}