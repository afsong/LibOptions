#ifndef __PATH_GENERATOR_H__
#define __PATH_GENERATOR_H__

namespace LibOptions {

class PathGenerator {
public:
    virtual std::vector<std::vector<double>> generateStockPaths() = 0;
    virtual void printPath() = 0;
};

} // namespace LibOptions

#endif
