#include <FileSystemUtils.hpp>

#include <sstream>
#include <stdexcept>

#include <sys/stat.h>

using namespace csgrpc;

bool
FileSystemUtils::FileExists(
    const std::string& path
) {
    if (!path.empty()) {
        struct stat statbuf = {0};
        return (
            (0 == stat(path.c_str(), &statbuf)) &&
            ((statbuf.st_mode & S_IFREG) == S_IFREG)
        );
    }
    return false;
}

bool
FileSystemUtils::DirectoryExists(
    const std::string& path
) {
    if (!path.empty()) {
        struct stat statbuf = {0};
        return (
            (0 == stat(path.c_str(), &statbuf)) &&
            ((statbuf.st_mode & S_IFDIR) == S_IFDIR)
        );
    }
    return false;
}

uint32_t
FileSystemUtils::CreateDirectory(
    const std::string& path,
    mode_t mode
 ) {
    uint32_t err = 0;
    if (path.empty()) {
        throw std::invalid_argument("Error: directory path is invalid");
    }
    if (mkdir(path.c_str(), mode) < 0) {
        if (errno != EEXIST) {
            std::ostringstream ss;
            ss  << "Error: Failed to create directory ["
                << path
                << "]. Error: "
                << errno;
            throw std::logic_error(ss.str());
        }
    }
    return err;
}
