#pragma once

#include <vector>

namespace logicario::engine
{
    using Byte = unsigned char;
    struct Image
    {
        std::vector<Byte> data;
        int width;
        int height;
        int channels;
    };
}
