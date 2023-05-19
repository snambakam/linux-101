#pragma once

#include <string>

namespace csgrpc
{
    class FileSystemUtils
    {
    public:
        static bool FileExists(const std::string& path);
        static bool DirectoryExists(const std::string& path);
        static uint32_t
        CreateDirectory(
            const std::string& path,
            mode_t mode
        );
    };
}
