#include <engine/platform/std_filesystem.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <filesystem>
#include <fstream>

namespace logicario::engine::platform
{
    StdFilesystem::StdFilesystem(std::shared_ptr<spdlog::sinks::stdout_color_sink_mt> loggerSink) : m_logger{"filesystem", {loggerSink}}
    {
        m_logger.info("Filesystem initialized");
    }

    std::optional<Image> StdFilesystem::loadImage(const Path& path)
    {
		if (!std::filesystem::exists(path))
		{
			m_logger.error("File \"{}\" not exist", path);
			return std::nullopt;
		}
        Image image;
        auto data = stbi_load(path.c_str(), &image.width, &image.height, &image.channels, 0);
        image.data = {data, data + (image.width * image.height)};
        stbi_image_free(data);
        return image;
    }

    std::optional<Text> StdFilesystem::loadText(const Path& path)
    {
		if (!std::filesystem::exists(path))
		{
			m_logger.error("File \"{}\" not exist", path);
			return std::nullopt;
		}
        std::ifstream file(path, std::ios::ate | std::ios::binary);
        size_t fileSize = (size_t)file.tellg();
        Text buffer;
        buffer.resize(fileSize + 1);
        file.seekg(0);
        file.read(buffer.data(), fileSize);
		buffer.back() = '\0';
        return buffer;
    }
}