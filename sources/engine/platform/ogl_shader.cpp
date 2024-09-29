#include <engine/platform/ogl_shader.hpp>

#include <glm/gtc/type_ptr.hpp>

#include <stdexcept>
#include <string_view>

namespace logicario::engine::platform
{
    OglShader::OglShader() : m_program{nullptr, nullptr} {}

    OglShader::OglShader(const Text& vertexCode, const Text& fragmentCode, const ID& resourceID) : Resource{resourceID}, m_program{nullptr, nullptr}
    {
        auto vertex = std::move(compileShader(vertexCode, GL_VERTEX_SHADER));
        auto fragment = std::move(compileShader(fragmentCode, GL_FRAGMENT_SHADER));
        linkProgram(std::move(vertex), std::move(fragment));
    }

    OglShader::GlShader OglShader::compileShader(const Text& shaderCode, uint16_t shaderType)
    {
        int success{};
        auto shader = glCreateShader(shaderType);
        auto* shaderCodePtr = shaderCode.data();
        glShaderSource(shader, 1, &shaderCodePtr, NULL);
        glCompileShader(shader);
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            std::string infoLog;
            GLint infoLogLength;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);
            infoLog.resize(infoLogLength);
            glGetShaderInfoLog(shader, infoLog.size(), nullptr, infoLog.data());
            std::string error = std::string{"Failed to compile shader:\n"} + infoLog;
            throw std::runtime_error{error};
        }
        auto shaderModule = GlShader{new GLuint{shader}, [](GLuint* id) { glDeleteShader(*id); }};
        return shaderModule;
    }

    void OglShader::linkProgram(GlShader vertex, GlShader fragment)
    {
        int success{};
        GLuint program = glCreateProgram();
        glAttachShader(program, *vertex);
        glAttachShader(program, *fragment);
        glLinkProgram(program);
        glGetProgramiv(program, GL_LINK_STATUS, &success);
        if (!success)
        {
            std::string infoLog;
            GLsizei infoLogLength;
            glGetProgramInfoLog(program, 0, &infoLogLength, nullptr);
            infoLog.resize(infoLogLength);
            glGetProgramInfoLog(program, infoLog.size(), nullptr, infoLog.data());
            std::string error = std::string{"Failed to link program:\n"} + infoLog;
            throw std::runtime_error{error};
        }
        m_program = GlProgram{new GLuint{program}, [](GLuint* id) { glDeleteProgram(*id); }};
    }

    void OglShader::bind() const
    {
        glUseProgram(*m_program);
    }

	void OglShader::set(const glm::mat4& matrix, const std::string& name) const
	{
		auto loc = glGetUniformLocation(*m_program, name.c_str());
		glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(matrix));
	}

	void OglShader::set(const glm::vec4& vector, const std::string& name) const 
	{
		auto loc = glGetUniformLocation(*m_program, name.c_str());
		glUniform4fv(loc, 1, glm::value_ptr(vector));
	}

    OglShader::OglShader(OglShader&& shader) noexcept : m_program{std::move(shader.m_program)}
    {
        setID(shader.getID());
    }

    OglShader& OglShader::operator=(OglShader&& shader) noexcept
    {
        m_program = std::move(shader.m_program);
        setID(shader.getID());
        return *this;
    }

    bool OglShader::operator==(const OglShader& shader) const noexcept
    {
        return Resource::operator==(shader);
    }
}