#ifndef LIBOPTIONS_PATHPLOTTER_H
#define LIBOPTIONS_PATHPLOTTER_H

#include <filesystem>
#include <vector>

namespace LibOptions {
namespace Utils {
int plotPath(std::vector<double>& x, std::vector<double>& y,
             const std::filesystem::path& name);
}
} // namespace LibOptions

#endif // LIBOPTIONS_PATHPLOTTER_H
