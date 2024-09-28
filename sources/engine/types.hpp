#pragma once

#include <string>
#include <vector>
#include <span>

namespace logicario::engine
{
	using Byte = unsigned char;
	using Binary = std::span<Byte>;
	using Text = std::vector<char>;
	using ID = std::string;
}
