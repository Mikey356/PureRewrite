#pragma once
#include <string>
#include <vector>

namespace Util
{
    std::vector<std::string> GetFilePaths(const std::string& directory, const std::vector<std::string>& extentions = std::vector<std::string>());
}