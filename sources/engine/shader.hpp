#pragma once

#include <engine/types.hpp>
#include <engine/resource.hpp>

namespace logicario::engine
{
    class Shader : public virtual Resource
    {
    public:
        virtual void bind() = 0;

    protected:
        ~Shader() = default;
    };
}