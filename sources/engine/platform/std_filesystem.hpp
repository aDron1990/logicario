#pragma once

#include <engine/filesystem.hpp>

#include <spdlog/logger.h>
#include <spdlog/sinks/stdout_color_sinks.h>

#include <memory>

namespace logicario::engine::platform
{
    class StdFilesystem : public Filesystem
    {
    public:
        StdFilesystem(std::shared_ptr<spdlog::sinks::stdout_color_sink_mt> loggerSink);
        std::optional<std::string> loadText(const Path& path) override { return ""; };
        std::optional<Image> loadImage(const Path& path) override;

    private:
        spdlog::logger m_logger;
    };
}