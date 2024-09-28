#pragma once

#include <engine/resource.hpp>

namespace logicario::engine
{
    class Texture : public virtual Resource
    {
    public:
        virtual void bind() = 0;

    protected:
        ~Texture() = default;
    };
}