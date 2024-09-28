#pragma once

#include <engine/types.hpp>

#include <vector>

namespace logicario::engine
{
    struct Image
    {
        Binary data;
        int width;
        int height;
        int channels;
    };
}
