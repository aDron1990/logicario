#pragma once

#include <engine/resource.hpp>

#include <glm/glm.hpp>

namespace logicario::engine
{
    class Texture : public virtual Resource
    {
    public:
        virtual void bind() = 0;
        virtual glm::ivec2 getSize() = 0;

    public:
        struct Region
        {
            int left;
            int right;
            int top;
            int bottom;
        };

    protected:
        ~Texture() = default;
    };
}