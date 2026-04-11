#include "Util.h"
#include <filesystem>
#include <fstream>

namespace Util
{
    std::vector<std::string> GetFilePaths(const std::string& directory)
    {
        std::vector<std::string> result;

        // Does directory exist?
        std::filesystem::path path(directory);
        if (!std::filesystem::exists(path)) return result;

        // If so, store every file path within it
        for (const auto& file : std::filesystem::directory_iterator(path))
        {
            if (!std::filesystem::is_regular_file(file))continue;

            result.push_back(file.path().string());
        }
        return result;
    }
}