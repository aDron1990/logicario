#pragma once

#include <engine/types.hpp>
#include <engine/resource.hpp>

#include <glm/glm.hpp>

namespace logicario::engine
{
    class Shader : public virtual Resource
    {
    public:
        virtual void bind() const = 0;
        virtual void set(const glm::mat4& matrix, const std::string& name) const = 0;

    protected:
        ~Shader() = default;
    };
}