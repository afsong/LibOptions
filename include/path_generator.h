#ifndef __PATH_GENERATOR_H__
#define __PATH_GENERATOR_H__

#include <double_vector.h>

namespace LibOptions {

class PathGenerator {
public:
    virtual void generateStockPaths() = 0;
    virtual const StockPath& getStockPaths() const = 0;
    virtual StockPath & getStocksPaths() = 0;
    virtual void printPath() = 0;
};

} // namespace LibOptions

#endif
