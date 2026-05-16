#include "Util.h"
#include <filesystem>
#include <fstream>
#include <iostream>

namespace Util
{
    std::vector<std::string> GetFilePaths(const std::string& directory, const std::vector<std::string>& extensions)
    {
        std::vector<std::string> result;

        // Does directory exist?
        std::filesystem::path path(directory);
        if (!std::filesystem::exists(path)) return result;

        // If so, store every file path within it
        for (const auto& file : std::filesystem::directory_iterator(path))
        {
            if (!std::filesystem::is_regular_file(file))continue;

            // No extension supplied? Then just add it
            if (extensions.empty()) {
                result.push_back(file.path().string());
                std::cout << "Was empty\n";
            }
            // Otherwise, only add it if the extension is found in the list
            else
            {
                for (const std::string& extension : extensions)
                {
                    if ('.' + extension == file.path().extension().string())
                        result.push_back(file.path().string());
                }
            }
        }
        return result;
    }
}