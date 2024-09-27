#pragma once

#include <engine/image.hpp>

#include <vector>
#include <optional>
#include <cstdint>
#include <string>

namespace logicario::engine
{
    class Filesystem
    {
    public:
        using Path = std::string;
        virtual std::optional<std::string> loadText(const Path& path) = 0;
        virtual std::optional<Image> loadImage(const Path& path) = 0;

    protected:
        ~Filesystem() = default;
    };
}